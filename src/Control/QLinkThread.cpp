#include "..\..\include\Control\QLinkThread.h"

jyLinkThread::jyLinkThread()
{

}

jyLinkThread::~jyLinkThread()
{
  qDebug()<<disconnect(m_pAccessManager, &QNetworkAccessManager::finished, this, &jyLinkThread::slotFinished);
  qDebug()<<disconnect(m_pTime, &QTimer::timeout, this, &jyLinkThread::slotLink);
}
void jyLinkThread::setBoatID(QString boatid)
{
  m_sBoatID = boatid;
}
QMap<QString, QString> jyLinkThread::getDataMap()
{
  return m_sData;
}
void jyLinkThread::ClearDataMapRotate()
{
  m_sData.insert(QString("Boat_Rotate"), QString("0.0"));
}
/*
void jyLinkThread::run()
{
  QTimer *_time = new QTimer();
  _time->start(100);
  connect(_time, &QTimer::timeout, this, &jyLinkThread::slotLink);
  exec();
}
*/
void jyLinkThread::slotGetURL(const QString mboatid)
{
  m_sBoatID = mboatid;
  m_bSendData = m_sBoatID.toLatin1();
  qDebug() << m_sBoatID;
}
//http请求一次完成后，接收数据并且处理
void jyLinkThread::slotFinished(QNetworkReply * reply)
{
  QMutexLocker _lock(&m_lock);
  //QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  //QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
  QByteArray bytes = reply->readAll();
  /*处理json数据*/
  QJsonDocument _jsonD = QJsonDocument::fromJson(bytes);
  QJsonObject _jsonO = _jsonD.object();
  QStringList _temkey = _jsonO.keys();
  //取到数据存到对象中
  for (int i = 0; i < _temkey.length(); ++i)
  {
    QJsonValue _temData = _jsonO.value(QString(_temkey[i]));
    m_sData.insert(_temkey[i], _temData.toString());
  }
  //qDebug() <<"GetData:"<< m_sData;
  //发出取得数据的信号，通知BoatControl获取和处理数据
  emit sigGetData();
  //delete reply，同时delete其子对象
  reply->deleteLater();
}
//启动连接
void jyLinkThread::slotLink()
{
 // if (m_bSendFlag)
 // {
    m_pReply = m_pAccessManager->post(*m_pRequest, m_bSendData);
 //   m_bSendFlag = false;
 // }
 // else
 // {
 //   m_pReply = m_pAccessManager->post(*m_pRequest, m_bSendData);
 // }
}

void jyLinkThread::slotLinkStart()
{
  m_pAccessManager = new QNetworkAccessManager(this);
  //存放url信息，设置消息头，QNetworkRequest用来存放请求的一些参数信息，如url地址
  m_pRequest = new QNetworkRequest(m_sURL);
  m_pRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  //初始化要连接的船
  QJsonObject _sendmsg;
  _sendmsg.insert("BoatID", m_sBoatID);
  qDebug() << "BoatID" << m_sBoatID;
  /*将需要连接的船的id作为参数发送给服务器 以json形式*/
  m_bSendData = QJsonDocument(_sendmsg).toJson();
  //开启定时器0.2秒请求一次
  m_pTime = new QTimer(this);
  m_pTime->start(200);
  //绑定finished信号，直到一个network reply结束时这个信号被发出，绑定接收数据的函数
  connect(m_pAccessManager, &QNetworkAccessManager::finished, this, &jyLinkThread::slotFinished);
  //绑定定时器信号 0.2秒执行一次slotLink
  connect(m_pTime, &QTimer::timeout, this, &jyLinkThread::slotLink);
}
//线程结束的时候，释放Request对象,停止计时器
void jyLinkThread::slotLinkFinished()
{
  if (m_pRequest)
  {
    delete m_pRequest;
  }
  if (m_pTime->isActive())
  {
    m_pTime->stop();
  }
}

/*
jyLinkThread::jyLinkThread()
{
  m_pManager = new QNetworkAccessManager();
  m_pRequest = new QNetworkRequest(m_url);
  m_pRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  connect(m_pManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReceiveData(QNetworkReply*)),Qt::DirectConnection);

}

void jyLinkThread::slotReceiveData(QNetworkReply* reply)
{
  QByteArray bytes = reply->readAll();
  QString string = QString::fromUtf8(bytes);
  qDebug() << string;
  reply->deleteLater();
}

void jyLinkThread::slotLinkStart()
{
  QByteArray test = "test";
   for(;;)
   m_pReply=m_pManager->post(*m_pRequest, test);
   QThread::sleep(2);
  
}*/
