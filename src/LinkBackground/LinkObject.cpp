
#include "LinkBackground/LinkObject.h"

jyLinkObject::jyLinkObject(QObject* parent /* = Q_NULLPTR */):
  QObject(parent)
{
  m_pAccessManager = new QNetworkAccessManager(this);
  m_pRequest = new QNetworkRequest();
  m_qtimeTimeOut = new QTimer(this);
  m_EventLoop = new QEventLoop(this);
  m_pShipData = new stdMapString();

  //ͨ��config.h��ȡURL
  char sURL[40] = "";
  sprintf(sURL, "%s:%d/%s", g_sURL.c_str(), g_iPort, g_sLinkViewName.c_str());
  m_urlAddress.setUrl(QString(sURL));
  //qDebug() << m_urlAddress;
  //����request����
  m_pRequest->setUrl(m_urlAddress);
  m_pRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  //���ü�ʱ����ʱ������һ����ѯֻ����һ��
  m_qtimeTimeOut->setInterval(m_iTimeOut);
  m_qtimeTimeOut->setSingleShot(true);
  connect(m_pAccessManager, &QNetworkAccessManager::finished, m_EventLoop, &QEventLoop::quit);
  connect(m_qtimeTimeOut, &QTimer::timeout, m_EventLoop, &QEventLoop::quit);
}

jyLinkObject::~jyLinkObject()
{
  disconnect(m_pAccessManager, &QNetworkAccessManager::finished, m_EventLoop, &QEventLoop::quit);
  disconnect(m_qtimeTimeOut, &QTimer::timeout, m_EventLoop, &QEventLoop::quit);
  delete m_pRequest;
  delete m_pShipData;
  if (m_pReply)
    m_pReply->deleteLater();
}

void jyLinkObject::setControl(jyShipControlPtr shipcontrol)
{
  m_pShipControl = shipcontrol;
}

void jyLinkObject::setShipID(const QString& shipid)
{
  m_strShipID = shipid;
  QJsonObject jsonSendMsg;
  jsonSendMsg.insert("BoatID", m_strShipID);
  m_byteSendData = QJsonDocument(jsonSendMsg).toJson();
}

void jyLinkObject::changeLoopFlag(bool loopflag)
{
  m_bLoopFlag = loopflag;
}

void jyLinkObject::pollingLink()
{
  while (m_bLoopFlag)
  {
    m_pReply = m_pAccessManager->post(*m_pRequest, m_byteSendData);
    m_qtimeTimeOut->start();
    m_EventLoop->exec();
    //�¼�ѭ����ֹ���������һ�����з��ط���finished�ź��˳��¼�ѭ������һ���Ƕ�ʱ����ʱ�˳��¼�ѭ��
    //�����ʱ���Լ����˵���������������¼�����
    if (m_qtimeTimeOut->isActive())
    {
      m_qtimeTimeOut->stop();
      //����
      if (m_pReply->error() != QNetworkReply::NoError)
      {
        qDebug() << "Error:" << m_pReply->errorString();
        m_strErrorMessage = m_pReply->errorString();
        emit sigHttpLinkErrorMsg(m_strErrorMessage);
      }
      //δ����
      else
      {
        
        QByteArray byteData = m_pReply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(byteData);
        QJsonObject jsonObject = jsonDocument.object();
        for (QJsonObject::iterator itr = jsonObject.begin(); itr != jsonObject.end(); ++itr)
        {
          std::string sJsonkey = itr.key().toStdString();
          std::string sJsonValue = itr.value().toString().toStdString();
          stdMapString::iterator mapItr = m_pShipData->find(sJsonkey);
          bool isExist = (mapItr != m_pShipData->end());
          if (isExist)
          {
            mapItr->second = sJsonValue;
          }
          else
          {
            m_pShipData->insert(std::pair<std::string, std::string>(sJsonkey, sJsonValue));
          }
        }
        //���������ź�
        emit sigShipData(m_pShipData);
        //�������
        for (stdMapString::iterator itr = m_pShipData->begin(); itr != m_pShipData->end(); ++itr)
        {
          //std::cout << itr->first<<" "<<itr->second<<std::endl;
        }
        //std::cout << "---------------------------------" << std::endl;
      }
    }
    //��ʱ��δ���˵����ʱ
    else
    {
      qDebug() << "time out";
      m_strErrorMessage = "Time Out";
      //����ErrorMessage֪ͨwidget��ʾ
      emit sigHttpLinkErrorMsg(m_strErrorMessage);
    }
    m_pReply->deleteLater();
    m_pReply = Q_NULLPTR;
    QThread::msleep(m_iTick);
  }
}

QString jyLinkObject::getErrorMessage()
{
  return m_strErrorMessage;
}

const stdMapString* jyLinkObject::getShipData()
{
  return m_pShipData;
}

void jyLinkObject::slotLinkStart()
{
  pollingLink();
}

void jyLinkObject::slotLinkClose()
{
  m_bLoopFlag = false;
}
