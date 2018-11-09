
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
  //事件循环终止有两种情况一种是有返回发出finished信号退出事件循环，另一种是定时器超时退出事件循环
  //如果定时器仍激活，则说明返回正常进行事件处理
  if (m_qtimeTimeOut->isActive())
  {
    m_qtimeTimeOut->stop();
    //出错
    if (m_pReply->error() != QNetworkReply::NoError)
    {
      qDebug() << "Error:" << m_pReply->errorString();
      m_strErrorMsg = m_pReply->errorString();
      emit sigHttpLinkErrorMsg(m_strErrorMsg);
    }
    //未出错
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
      //发送数据信号
      emit sigSendData(m_pReceiveData);
    }
  }
  //定时器未激活，说明超时
  else
  {
    qDebug() << "time out";
    m_strErrorMsg = "Time Out";
    //发送ErrorMessage通知widget显示
    emit sigHttpLinkErrorMsg(m_strErrorMsg);
  }
  m_pReply->deleteLater();
}

 
