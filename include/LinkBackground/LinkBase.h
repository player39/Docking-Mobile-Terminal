
#ifndef _LINKBASE_H
#define _LINKBASE_H

#include <QtCore/QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtCore/QByteArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QMutex>
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtCore/QVariant>
#include <QtCore/QJsonArray>
#include <iostream>
#include "Data/Config.h"

class jyLinkBase : public QObject
{
  Q_OBJECT

public:
  jyLinkBase(QObject* parent = Q_NULLPTR);
  ~jyLinkBase();
 // void initNetworkParam();
  void setTimeout(int iTimeoutMsec = 200);
  void initNetworkParam(QString linkurl, QNetworkRequest::KnownHeaders header, const QVariant& value);
  void HttpLink(const QByteArray& senddata);

private:
  QNetworkAccessManager* m_pAccessManager = Q_NULLPTR;
  QUrl m_urlAddress;
  QNetworkRequest* m_pRequest = Q_NULLPTR;
  QNetworkReply* m_pReply = Q_NULLPTR;
  QMutex m_Lock;
  QEventLoop* m_EventLoop = Q_NULLPTR;

  QTimer* m_qtimeTimeOut = Q_NULLPTR;

  stdMapString* m_pReceiveData = NULL;
  QString m_strErrorMsg = "";

signals:
  void sigHttpLinkErrorMsg(QString errormsg);
  void sigSendData(const stdMapString* receivedata);
};

#endif // _LINKBASE_H