#include "..\..\include\Control\QLinkThread.h"

jyLinkThread::jyLinkThread()
{

}

jyLinkThread::~jyLinkThread()
{
  disconnect(m_pAccessManager, &QNetworkAccessManager::finished, this, &jyLinkThread::slotFinished);
  disconnect(m_pTime, &QTimer::timeout, this, &jyLinkThread::slotLink);
}
void jyLinkThread::setBoatID(QString boatid)
{
  m_strBoatID = boatid;
}
QMap<QString, QString>& jyLinkThread::getDataMap()
{
  return m_qmapData;
}
void jyLinkThread::clearDataMapRotate()
{
  m_qmapData.insert("Boat_Rotate", "0.0");
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
void jyLinkThread::slotGetURL(const QString& mboatid)
{
  m_strBoatID = mboatid;
  m_byteSendData = m_strBoatID.toLatin1();
  qDebug() << m_strBoatID;
}
//http����һ����ɺ󣬽������ݲ��Ҵ���
void jyLinkThread::slotFinished(QNetworkReply* reply)
{
  QMutexLocker Lock(&m_qmutexLock);
  //QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  //QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
  QByteArray bytes = reply->readAll();
  /*����json����*/
  QJsonDocument jsonDocument = QJsonDocument::fromJson(bytes);
  QJsonObject jsonObject = jsonDocument.object();
  QStringList strlTemkey = jsonObject.keys();
  //ȡ�����ݴ浽������
  for (int i = 0; i < strlTemkey.length(); ++i)
  {
    QJsonValue jsonTemData = jsonObject.value(strlTemkey[i]);
    m_qmapData.insert(strlTemkey[i], jsonTemData.toString());
  }
  qDebug() <<"GetData:"<< m_qmapData;
  //delete reply��ͬʱdelete���Ӷ���
  reply->deleteLater();
  //����ȡ�����ݵ��źţ�֪ͨBoatControl��ȡ�ʹ�������
  emit sigGetData();
}
//��������
void jyLinkThread::slotLink()
{
    m_pAccessManager->post(*m_pRequest, m_byteSendData);
}

void jyLinkThread::slotLinkStart()
{
  m_pAccessManager = new QNetworkAccessManager(this);
  //���url��Ϣ��������Ϣͷ��QNetworkRequest������������һЩ������Ϣ����url��ַ
  m_pRequest = new QNetworkRequest(m_sURL);
  m_pRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  //��ʼ��Ҫ���ӵĴ�
  QJsonObject jsonSendmsg;
  jsonSendmsg.insert("BoatID", m_strBoatID);
  qDebug() << "BoatID" << m_strBoatID;
  /*����Ҫ���ӵĴ���id��Ϊ�������͸������� ��json��ʽ*/
  m_byteSendData = QJsonDocument(jsonSendmsg).toJson();
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
    delete m_pRequest;
  if (m_pTime->isActive())
    m_pTime->stop();
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
