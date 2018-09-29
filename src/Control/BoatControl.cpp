#include "..\..\include\Control\BoatControl.h"

jyBoatControl::jyBoatControl()
{
  m_pBoatLink = new jyLinkThread();
  m_pLinkThread = new QThread();
  m_NowCoordinate.x = 0;
  m_NowCoordinate.y = 0;
  m_NowCoordinate.z = 0;
  /*暂时的船只顶点数据*/
  float _tem[8][3] = { {50,-20,0}, {-50,-20,0}, {-50,-20,2}, {50,-20,2},
                       {50,20,0}, {-50,20,0}, {-50,20,2}, {50,20,2} };
  
  for (int i = 0; i < 8; ++i)
  {
    m_point[i].x = _tem[i][0];
    m_point[i].y = _tem[i][1];
    m_point[i].z = _tem[i][2];
  }
  int _iSurface[6][4] = { {3,2,1,0}, {2,6,5,1}, {6,7,4,5},
                 {7,3,0,4}, {7,6,2,3}, {4,0,1,5} };
  for (int i = 0; i < 6; ++i)
  {
    for (int k = 0; k < 4; ++k)
    {
      m_iSurface[i][k] = _iSurface[i][k];
    }
  }



}

jyBoatControl::~jyBoatControl()
{
}

jyLinkThread * jyBoatControl::getLinkThread()
{
  return m_pBoatLink;
}

point * jyBoatControl::getPoint()
{
  return m_point;
}

Matrix_Translate jyBoatControl::getTranslate()
{
  return m_mTranslate;
}

point jyBoatControl::getCoordinate()
{
  return m_NowCoordinate;
}

double jyBoatControl::getRotate()
{
  return m_dRotate;
}

void jyBoatControl::setRotate(double rotate)
{
  m_dRotate = rotate;
}

double jyBoatControl::getLandAveDistance()
{
  return m_dAveLandDistance;
}

double jyBoatControl::getDistance1()
{
  return m_dLandDistance1;
}

double jyBoatControl::getDistance2()
{
  return m_dLandDistance2;
}

bool * jyBoatControl::getGPSLinkFlag()
{
  return m_bGPSLinkFlag;
}

QString jyBoatControl::getLandRadio()
{
  return m_sLandRadio;
}

double jyBoatControl::getRate()
{
  return m_dRate;
}

QString jyBoatControl::getID()
{
  return m_sID;
}

QString jyBoatControl::getTime()
{
  return m_stime;
}

QString jyBoatControl::getMoveState()
{
  return m_sMoveState;
}

QString jyBoatControl::getHeadWarningX()
{
  return m_sHeadWarningX;
}

QString jyBoatControl::getHeadWarningY()
{
  return m_sHeadWarningY;
}

QString jyBoatControl::getSternWarningX()
{
  return m_sSternWarningX;
}

QString jyBoatControl::getSternWarningY()
{
  return m_sSternWarningY;
}

void jyBoatControl::slotGetUrl(const QString boatid)
{
  m_sBoatID = boatid;
}

void jyBoatControl::slotLink()
{
  /*避免重复启动*/
  if(!m_pBoatLink)
  {
    m_pBoatLink = new jyLinkThread();
  }
  
  if (!m_pLinkThread)
  {
    m_pLinkThread = new QThread();
  }
  //设置要连接的船只id
  m_pBoatLink->setBoatID(m_sBoatID);
  /*开启线程接收船只数据，QThread 启动后默认调用exec()事件循环，采取这种写法是为了使在QLinkThread类中定义的函数均在QThread中运行*/
  m_pBoatLink->moveToThread(m_pLinkThread);
  m_pLinkThread->start();
  /*线程启动和结束时绑定相应的槽函数*/
  connect(m_pLinkThread, &QThread::started, m_pBoatLink, &jyLinkThread::slotLinkStart);
  connect(m_pLinkThread, &QThread::finished, m_pBoatLink, &jyLinkThread::slotLinkFinished);
  //绑定QLinkThread中的sigGetData，接收到数据的时候发出这个信号通知，BoatControl处理
  connect(m_pBoatLink, &jyLinkThread::sigGetData, this, &jyBoatControl::slotChangeBoatData);
}
//断开连接时进行的操作，释放对象断开槽函数连接，指针赋值为null，由于调用deleteLater因此释放时会自动释放子对象
void jyBoatControl::slotLinkClose()
{
  /*判断线程是否在运行*/
  if (m_pLinkThread)
  {
    if (m_pLinkThread->isRunning())
    {
      //向事件循环发送结束信号
      m_pLinkThread->quit();
      //等待线程执行完毕（从run中返回），或者超时，这里没有设置时间 默认值永远不会超时
      m_pLinkThread->wait();
      //断开槽函数连接
      disconnect(m_pLinkThread, &QThread::started, m_pBoatLink, &jyLinkThread::slotLinkStart);
      disconnect(m_pLinkThread, &QThread::finished, m_pBoatLink, &jyLinkThread::slotLinkFinished);
      disconnect(m_pBoatLink, &jyLinkThread::sigGetData, this, &jyBoatControl::slotChangeBoatData);
      m_pLinkThread->deleteLater();
      m_pBoatLink->deleteLater();
      m_pLinkThread = NULL;
      m_pBoatLink = NULL;
    }
  }
  
}
/*接收和处理数据的函数，这里有一个问题，在用户选择断开和船连接时，调用slotLinkclose，
其中解除 m_pLinkThread和slotLinkFinished绑定，但是有概率在解除绑定之后仍旧执行一次slotChangeBoatData，
此时由于m_pBoatLink已经释放变成null因此会出指针错，所以在执行这个函数时先进行一次判断，如果m_pBoatLink为null则直接return，
但是为什么会再执行一次slotChangeBoatData的原因还不清楚，disconnect返回值均为true
*/
void jyBoatControl::slotChangeBoatData()
{
  //多线程访问一个资源，加锁
  QMutexLocker _lock(&m_Lock);
  //迭代器访问QMap
  QMap<QString, QString>::const_iterator i;
  //原因如上
  if (!m_pBoatLink)
  {
    return;
  }
  //开始读取和处理数据
  for (i = m_pBoatLink->getDataMap().constBegin(); i != m_pBoatLink->getDataMap().constEnd(); ++i)
  {
    //qDebug() << i.key() << ":" << i.value()<<"this is boat control";
    //读船只坐标，这里是原始坐标没有减去中心坐标，并且通过前一次减去这次读到的数据计算出平移坐标
    if (i.key() == QString("Boat_Coordinate"))
    {    
      QStringList _tem = i.value().split(',');//会不会存在value中没有值的情况
      //计算平移坐标
      m_mTranslate.x = _tem[0].toDouble() - m_NowCoordinate.x ;
      m_mTranslate.y = _tem[1].toDouble() - m_NowCoordinate.y ;
      m_mTranslate.z = 0;
      qDebug() << m_mTranslate.x << m_mTranslate.y;
      //保存最新的坐标
      m_NowCoordinate.x = _tem[0].toDouble();
      m_NowCoordinate.y = _tem[1].toDouble();
      m_NowCoordinate.z = 0;
    }
    //船只速度
    if (i.key() == QString("Boat_Rate"))
    {
      m_dRate = i.value().toFloat();
    }
    //GPS发送数据的时间
    if (i.key() == QString("Boat_Time"))
    {
      m_stime = i.value();
    }
    //船只旋转角度
    if (i.key() == QString("Boat_Rotate"))
    {
      qDebug() << "RotateGET"<<i.value();
      m_dRotate = i.value().toDouble();
    }
    //船只id
    if (i.key() == QString("Boat_ID"))
    {
      m_sID = i.value();
    }
    //船只中心点离岸基距离
    if (i.key() == QString("Boat_AveLandDistance"))
    {
      m_dAveLandDistance = i.value().toDouble();
    }
    //船头离岸基距离
    if (i.key() == QString("Boat_LandDistance1"))
    {
      m_dLandDistance1 = i.value().toDouble();
    }
    //船尾离岸基距离
    if (i.key() == QString("Boat_LandDistance2"))
    {
      m_dLandDistance2 = i.value().toDouble();
    }
    //船只与岸基夹角，需要修改实际上是靠这个确认船体姿态
    if (i.key() == QString("Boat_LandRadio"))
    {
      m_sLandRadio = i.value();
    }
    //船只和船头GPS连接状态
    if (i.key() == QString("Boat_ConnectionFlag1"))
    {
      if (QString(i.value()) == "True")
      {
        m_bGPSLinkFlag[0] = true;
      }
      else
      {
        m_bGPSLinkFlag[0] = false;
      }
    }
    //船只和船尾GPS连接状态
    if (i.key() == QString("Boat_ConnectionFlag2"))
    {
      if (QString(i.value()) == "True")
      {
        m_bGPSLinkFlag[1] = true;
      }
      else
      {
        m_bGPSLinkFlag[1] = false;
      }
    }
    //船运动状态，加速减速匀速
    if (i.key() == QString("Boat_MoveState"))
    {
      if (QString(i.value()) == "0")
      {
        m_sMoveState = "Decelerate";
      }
      if (QString(i.value()) == "1")
      {
        m_sMoveState = "Uniform Speed";
      }
      if (QString(i.value()) == "2")
      {
        m_sMoveState = "Accelerate";
      }
    }
    //报警flag 船头X方向报警
    if (i.key() == QString("Boat_HeadWarningX"))
    {
      if (QString(i.value()) == "False")
      {
        m_sHeadWarningX = "Safe";
      }
      else
      {
        m_sHeadWarningX = "Danger";
      }
    }
    //报警flag 船头Y方向报警
    if (i.key() == QString("Boat_HeadWarningY"))
    {
      if (QString(i.value()) == "False")
      {
        m_sHeadWarningY = "Safe";
      }
      else
      {
        m_sHeadWarningY = "Danger";
      }
    }
    //报警flag 船尾X方向报警
    if (i.key() == QString("Boat_SternWarningX"))
    {
      if (QString(i.value()) == "False")
      {
        m_sSternWarningX = "Safe";
      }
      else
      {
        m_sSternWarningX = "Danger";
      }
    }
    //报警flag 船尾Y方向报警
    if (i.key() == QString("Boat_SternWarningY"))
    {
      if (QString(i.value()) == "False")
      {
        m_sSternWarningY = "Safe";
      }
      else
      {
        m_sSternWarningY = "Danger";
      }
    }
  }
  //发送数据更新完毕的信号，通知视图层进行重新渲染
   emitSigUpdata();
  
}
