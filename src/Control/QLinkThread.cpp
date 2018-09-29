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
//http����һ����ɺ󣬽������ݲ��Ҵ���
void jyLinkThread::slotFinished(QNetworkReply * reply)
{
  QMutexLocker _lock(&m_lock);
  //QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  //QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
  QByteArray bytes = reply->readAll();
  /*����json����*/
  QJsonDocument _jsonD = QJsonDocument::fromJson(bytes);
  QJsonObject _jsonO = _jsonD.object();
  QStringList _temkey = _jsonO.keys();
  //ȡ�����ݴ浽������
  for (int i = 0; i < _temkey.length(); ++i)
  {
    QJsonValue _temData = _jsonO.value(QString(_temkey[i]));
    m_sData.insert(_temkey[i], _temData.toString());
  }
  //qDebug() <<"GetData:"<< m_sData;
  //����ȡ�����ݵ��źţ�֪ͨBoatControl��ȡ�ʹ�������
  emit sigGetData();
  //delete reply��ͬʱdelete���Ӷ���
  reply->deleteLater();
}
//��������
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
  //���url��Ϣ��������Ϣͷ��QNetworkRequest������������һЩ������Ϣ����url��ַ
  m_pRequest = new QNetworkRequest(m_sURL);
  m_pRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  //��ʼ��Ҫ���ӵĴ�
  QJsonObject _sendmsg;
  _sendmsg.insert("BoatID", m_sBoatID);
  qDebug() << "BoatID" << m_sBoatID;
  /*����Ҫ���ӵĴ���id��Ϊ�������͸������� ��json��ʽ*/
  m_bSendData = QJsonDocument(_sendmsg).toJson();
  //������ʱ��0.2������һ��
  m_pTime = new QTimer(this);
  m_pTime->start(200);
  //��finished�źţ�ֱ��һ��network reply����ʱ����źű��������󶨽������ݵĺ���
  connect(m_pAccessManager, &QNetworkAccessManager::finished, this, &jyLinkThread::slotFinished);
  //�󶨶�ʱ���ź� 0.2��ִ��һ��slotLink
  connect(m_pTime, &QTimer::timeout, this, &jyLinkThread::slotLink);
}
//�߳̽�����ʱ���ͷ�Request����,ֹͣ��ʱ��
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
