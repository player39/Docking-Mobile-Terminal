
#include "LinkBackground/LinkBase.h"

jyLinkBase::jyLinkBase(QObject* parent /* = Q_NULLPTR */):
  QObject(parent)
{
  m_pAccessManager = new QNetworkAccessManager(this);
  m_pRequest = new QNetworkRequest();
  m_qtimeTimeOut = new QTimer(this);
  m_EventLoop = new QEventLoop(this);
  m_pReceiveData = new stdMapString();

  connect(m_pAccessManager, &QNetworkAccessManager::finished, m_EventLoop, &QEventLoop::quit);
  connect(m_qtimeTimeOut, &QTimer::timeout, m_EventLoop, &QEventLoop::quit);
}

jyLinkBase::~jyLinkBase()
{
  disconnect(m_pAccessManager, &QNetworkAccessManager::finished, m_EventLoop, &QEventLoop::quit);
  disconnect(m_qtimeTimeOut, &QTimer::timeout, m_EventLoop, &QEventLoop::quit);
  delete m_pRequest;
  delete m_pReceiveData;
}

void jyLinkBase::setTimeout(int iTimeoutMsec /* = 200 */)
{
  m_qtimeTimeOut->setInterval(iTimeoutMsec);
  m_qtimeTimeOut->setSingleShot(true);
}

void jyLinkBase::initNetworkParam(QString linkurl, QNetworkRequest::KnownHeaders header, const QVariant& value)
{
  m_urlAddress.setUrl(linkurl);
  m_pRequest->setUrl(m_urlAddress);
  m_pRequest->setHeader(header, value);
}

void jyLinkBase::HttpLink(const QByteArray& senddata)
{
  m_pReply = m_pAccessManager->post(*m_pRequest, senddata);
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
      m_strErrorMsg = m_pReply->errorString();
      emit sigHttpLinkErrorMsg(m_strErrorMsg);
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
        stdMapString::iterator mapItr = m_pReceiveData->find(sJsonkey);
        bool isExist = (mapItr != m_pReceiveData->end());
        if (isExist)
        {
          mapItr->second = sJsonValue;
        }
        else
        {
          m_pReceiveData->insert(std::pair<std::string, std::string>(sJsonkey, sJsonValue));
        }
      }
      //���������ź�
      emit sigSendData(m_pReceiveData);
    }
  }
  //��ʱ��δ���˵����ʱ
  else
  {
    qDebug() << "time out";
    m_strErrorMsg = "Time Out";
    //����ErrorMessage֪ͨwidget��ʾ
    emit sigHttpLinkErrorMsg(m_strErrorMsg);
  }
  m_pReply->deleteLater();
}

 
