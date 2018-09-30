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
  m_initCoordinateRequest = new QNetworkRequest();
  m_initCoordinateRequest->setUrl(QUrl(QString::fromStdString(this->getBackgroundUrl())+"initRender"));
  m_initCoordinateRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  //做自动连接如果有船只在范围内可以自动连接，复数船只跳出选择框选择
  m_autoLink.setUrl(QUrl(QString::fromStdString(this->getBackgroundUrl() + "getShipID")));
  m_autoLink.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  //绑定接收数据函数
  m_AccessManager = new QNetworkAccessManager(this);
 // connect(m_AccessManager, &QNetworkAccessManager::finished, this, &jyOSGControl::slotFinished);
  //进行初始化
  this->initRender();
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
  QString _sendData = " ";
  //发送post请求，返回数据存放到m_pReply
  //进行事件循环，接到请求前阻塞程序，实现同步操作
  //connect(m_AccessManager, &QNetworkAccessManager::finished, this, &jyOSGControl::slotHttpSuccessQuit);
  connect(m_AccessManager, &QNetworkAccessManager::finished, this, &jyOSGControl::slotLink);
  m_pReply = m_AccessManager->post(*m_initCoordinateRequest, _sendData.toLatin1());
  //定时器启动
 // m_HttpTimer.start(5000);
  //绑定超时，传输超时的目的是在tcp连接通了的情况下由于网络因素数据没有传输到客户端，猜想如果是tcp阶段连接失败会直接发出finished信号
  //connect(&m_HttpTimer, &QTimer::timeout, this, &jyOSGControl::slotHttpFailedQuit);
  //事件循环等待服务器响应
  //m_HttpLoop.exec();
  QString test = "";
  qDebug() << test.prepend(m_pReply->readAll());
}

void jyOSGControl::slotFinished(QNetworkReply *reply)
{
  qDebug() << "test";
  //解析json数据
  QByteArray _bData = reply->readAll();
  QJsonDocument _jsonD = QJsonDocument::fromJson(_bData);
  QJsonObject _jsonO = _jsonD.object();
  for (QJsonObject::iterator i = _jsonO.begin(); i != _jsonO.end(); ++i)
  {
    qDebug() << i.value();
    qDebug() << i.key();
  }
}

void jyOSGControl::slotLink()
{
  qDebug() << "test";
}

void jyOSGControl::slotEmitInitSig()
{
  emit sigInitFlag(m_bInitFlag);
}

void jyOSGControl::slotHttpSuccessQuit()
{
  //退出循环
  m_HttpLoop.quit();
  m_bInitFlag = true;
  //关闭计时器
  m_HttpTimer.stop();
  slotEmitInitSig();
}

void jyOSGControl::slotHttpFailedQuit()
{
  m_HttpLoop.quit();
  m_bInitFlag = false;
  m_HttpTimer.stop();
  slotEmitInitSig();
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
/*
void jyOSGControl::slotLink()
{
  m_pLink->moveToThread(m_pLinkThread);
  connect(m_pLinkThread, &QThread::started, m_pLink, &jyLinkThread::slotLinkStart);
  m_pLinkThread->start();
}*/
