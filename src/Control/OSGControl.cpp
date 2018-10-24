#include <Control/OSGControl.h>

jyOSGControl::jyOSGControl()
{
//  m_pLink = new jyLinkThread();
 // m_pLinkThread = new QThread();
  m_pBoatControl = new jyBoatControl();
  m_pLandControl = new jyLandControl();
  m_pSkyBoxControl = new jySkyBoxControl();
  m_pSeaControl = new jySeaControl();
  qDebug() << "URL:" << QString::fromStdString(this->getBackgroundUrl()+"initRender");
  //初始化岸基坐标和中心坐标
  m_pInitCoordinateRequest = new QNetworkRequest();
  m_pInitCoordinateRequest->setUrl(QUrl(QString::fromStdString(this->getBackgroundUrl())+"initRender"));
  m_pInitCoordinateRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  //做自动连接如果有船只在范围内可以自动连接，复数船只跳出选择框选择
  //m_autoLink.setUrl(QUrl(QString::fromStdString(this->getBackgroundUrl() + "getShipID")));
  //m_autoLink.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  //绑定接收数据函数
  m_pAccessManager = new QNetworkAccessManager(this);
 // connect(m_AccessManager, &QNetworkAccessManager::finished, this, &jyOSGControl::slotFinished);
  //进行初始化
//  this->initRender();
//  m_pOSGControl = new jyOSGControl();
}
/*
jyLinkThread * jyOSGControl::getLinkThread()
{
  return m_pLink;
}
*/
//初始化的函数获取中心坐标和岸基坐标，关于QNetworkAccessManager，测试下来发现，发送http请求的过程应该是一个异步的过程，当服务器开启时，和服务器建立tcp连接，之后的过程属于http的范围，
//是一个异步的过程，此时单纯使用信号槽，根据官方文档的描述QNetworkAccessManager会在一个pending network reply结束时发送finished信号，这个信号和绑定的槽函数无法触发，
//需要使用事件循环阻塞线程，等待服务器返回才能发送信号，同时如果服务器端关闭tcp连接失败则会直接返回结果发送finish信号。

void jyOSGControl::initRender()
{
  //发送一个空数据
  QString strSendData = " ";
  //清空错误信息
  m_strInitFlag = "";
  //发送post请求，返回数据存放到m_pReply
  //进行事件循环，接到请求前阻塞程序，实现同步操作
  //connect(m_AccessManager, &QNetworkAccessManager::finished, this, &jyOSGControl::slotHttpSuccessQuit);
  connect(m_pAccessManager, &QNetworkAccessManager::finished, &m_HttpLoop, &QEventLoop::quit);
  m_pReply = m_pAccessManager->post(*m_pInitCoordinateRequest, strSendData.toLatin1());
  //定时器启动,10秒超时
  m_HttpTimer.setInterval(10000);
  m_HttpTimer.setSingleShot(true);
  //绑定超时，传输超时的目的是在tcp连接通了的情况下由于网络因素数据没有传输到客户端，猜想如果是tcp阶段连接失败会直接发出finished信号
  connect(&m_HttpTimer, &QTimer::timeout, &m_HttpLoop, &QEventLoop::quit);
  //事件循环等待服务器响应
  m_HttpTimer.start();
  m_HttpLoop.exec();
  //QString test = "";
  //qDebug() << test.prepend(m_pReply->readAll());
  //事件循环终止有两种情况一种是有返回发出finished信号退出事件循环，另一种是定时器超时退出事件循环
  //如果定时器仍激活，则说明返回正常进行事件处理
  if (m_HttpTimer.isActive())
  {
    m_HttpTimer.stop();
    //出错
    if (m_pReply->error() != QNetworkReply::NoError)
    {
      qDebug() << "Error:" << m_pReply->errorString();
      m_strInitFlag = "001";
      m_strErrorMessage = "Error:" + m_pReply->errorString();
    }
    //未出错
    else
    {
      QByteArray byteData = m_pReply->readAll();
      QJsonDocument jsonDocument = QJsonDocument::fromJson(byteData);
      QJsonObject jsonObject = jsonDocument.object();
      for (QJsonObject::iterator i = jsonObject.begin(); i != jsonObject.end(); ++i)
      {
        //获取岸基坐标
        if (i.key() == QString("LandCoordinate"))
        {
        //  qDebug() << i.value().toString();
          QString _temLandCoor = i.value().toString();
          //如果数据为空，初始化失败
          if (_temLandCoor == "")
          {
            m_strInitFlag = "002";
            m_strErrorMessage += "Error: LandDataError Server return empty ";
            continue;
          }
          QStringList _temLandPoint = _temLandCoor.mid(1, _temLandCoor.length() - 2).split(',');
          double _temLandX = (_temLandPoint[0].toDouble() + _temLandPoint[2].toDouble()) / 2;
          double _temLandY = (_temLandPoint[1].toDouble() + _temLandPoint[3].toDouble()) / 2;
          m_pLandControl->setLandCoordinate(_temLandX, _temLandY);
       //   qDebug() << m_pLandControl->getTranslate().x<<m_pLandControl->getTranslate().y;
          //计算相机坐标，思路是相机坐标在与岸基垂直的直线上并且距离岸基直线有900米通过联立方程组求出相机坐标
          m_CameraCoor.x = _temLandX;
          m_CameraCoor.y = _temLandY + 900.0;
          m_CameraCoor.z = 400.0;
          //将initflag设为000 表示成功
          m_strInitFlag = "000";
          continue;
        }
        //获取Server端连接中的船只，进行自动连接
        if (i.key() == "ShipID")
        {
          QJsonArray _ShipID = i.value().toArray();
          for (QJsonArray::iterator k = _ShipID.begin(); k != _ShipID.end(); ++k)
          {
            m_strlShipList.append(k->toString());
          }
        }
        //如果所有key值都不符合则初始化失败，目前还发送了一个中心坐标 确认完web端以后不发送中心坐标再把注释去掉
        //m_strInitFlag = false;
      }
      //出循环以后发送init信号通知qt弹窗
     // slotEmitInitSig();
    }
  }
  //定时器未激活，说明超时
  else
  {
    qDebug() << "time out";
    m_strInitFlag = "003";
    m_strErrorMessage = "Error: Time Out";
   // slotEmitInitSig();
  }
}

void jyOSGControl::slotEmitInitSig()
{
  emit sigInitFlag(m_strInitFlag);
}

jyBoatControl * jyOSGControl::getBoatControl()
{
  return m_pBoatControl;
}

jyLandControl * jyOSGControl::getLandControl()
{
  return m_pLandControl;
}
jySkyBoxControl * jyOSGControl::getSkyBoxControl()
{
  return m_pSkyBoxControl;
}

jySeaControl * jyOSGControl::getSeaControl()
{
  return m_pSeaControl;
}
point jyOSGControl::getCameraCoor()
{
  return m_CameraCoor;
}
QString jyOSGControl::getInitResult()
{
  return m_strInitFlag;
}
QString jyOSGControl::getErrorMessage()
{
  return m_strErrorMessage;
}
QStringList jyOSGControl::getShipList()
{
  return m_strlShipList;
}
/*
void jyOSGControl::slotLink()
{
  m_pLink->moveToThread(m_pLinkThread);
  connect(m_pLinkThread, &QThread::started, m_pLink, &jyLinkThread::slotLinkStart);
  m_pLinkThread->start();
}*/
