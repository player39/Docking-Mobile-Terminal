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
  //��ʼ�������������������
  m_initCoordinateRequest = new QNetworkRequest();
  m_initCoordinateRequest->setUrl(QUrl(QString::fromStdString(this->getBackgroundUrl())+"initRender"));
  m_initCoordinateRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  //���Զ���������д�ֻ�ڷ�Χ�ڿ����Զ����ӣ�������ֻ����ѡ���ѡ��
  m_autoLink.setUrl(QUrl(QString::fromStdString(this->getBackgroundUrl() + "getShipID")));
  m_autoLink.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  //�󶨽������ݺ���
  m_AccessManager = new QNetworkAccessManager(this);
 // connect(m_AccessManager, &QNetworkAccessManager::finished, this, &jyOSGControl::slotFinished);
  //���г�ʼ��
  this->initRender();
//  m_pOSGControl = new jyOSGControl();
}
/*
jyLinkThread * jyOSGControl::getLinkThread()
{
  return m_pLink;
}
*/
//��ʼ���ĺ�����ȡ��������Ͱ������꣬����QNetworkAccessManager�������������֣�����http����Ĺ���Ӧ����һ���첽�Ĺ��̣�������������ʱ���ͷ���������tcp���ӣ�֮��Ĺ�������http�ķ�Χ��
//��һ���첽�Ĺ��̣���ʱ����ʹ���źŲۣ����ݹٷ��ĵ�������QNetworkAccessManager����һ��pending network reply����ʱ����finished�źţ�����źźͰ󶨵Ĳۺ����޷�������
//��Ҫʹ���¼�ѭ�������̣߳��ȴ����������ز��ܷ����źţ�ͬʱ����������˹ر�tcp����ʧ�����ֱ�ӷ��ؽ������finish�źš�

void jyOSGControl::initRender()
{
  //����һ��������
  QString _sendData = " ";
  //����post���󣬷������ݴ�ŵ�m_pReply
  //�����¼�ѭ�����ӵ�����ǰ��������ʵ��ͬ������
  //connect(m_AccessManager, &QNetworkAccessManager::finished, this, &jyOSGControl::slotHttpSuccessQuit);
  connect(m_AccessManager, &QNetworkAccessManager::finished, this, &jyOSGControl::slotLink);
  m_pReply = m_AccessManager->post(*m_initCoordinateRequest, _sendData.toLatin1());
  //��ʱ������
 // m_HttpTimer.start(5000);
  //�󶨳�ʱ�����䳬ʱ��Ŀ������tcp����ͨ�˵����������������������û�д��䵽�ͻ��ˣ����������tcp�׶�����ʧ�ܻ�ֱ�ӷ���finished�ź�
  //connect(&m_HttpTimer, &QTimer::timeout, this, &jyOSGControl::slotHttpFailedQuit);
  //�¼�ѭ���ȴ���������Ӧ
  //m_HttpLoop.exec();
  QString test = "";
  qDebug() << test.prepend(m_pReply->readAll());
}

void jyOSGControl::slotFinished(QNetworkReply *reply)
{
  qDebug() << "test";
  //����json����
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
  //�˳�ѭ��
  m_HttpLoop.quit();
  m_bInitFlag = true;
  //�رռ�ʱ��
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
