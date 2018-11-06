
#ifndef _LINKOBJECT_H
#define _LINKOBJECT_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtCore/QByteArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QMutex>
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <iostream>
#include "Control/ShipControl.h"
#include "Data/Config.h"

class jyLinkObject : public QObject
{
  Q_OBJECT

public:
  jyLinkObject(QObject* parent = Q_NULLPTR);
  ~jyLinkObject();
  
  void setControl(jyShipControlPtr shipcontrol);
  
  void setShipID(QString shipid);
  void changeLoopFlag(bool loopflag);
  void pollingLink();

  QString getErrorMessage();
  //ȡָ�븳��ShipControl
  const stdMapString* getShipData();

private:
  std::weak_ptr<jyShipControl> m_pShipControl;

  QNetworkAccessManager* m_pAccessManager = Q_NULLPTR;
  QUrl m_urlAddress;
  QNetworkRequest* m_pRequest = Q_NULLPTR;
  QNetworkReply* m_pReply = Q_NULLPTR;
  QMutex m_Lock;

  QString m_strShipID = "-1";
  QByteArray m_byteSendData;
  //����ѭ���ı�־
  bool m_bLoopFlag = false;
  //Ϊʲôһ��Ҫָ��
  QEventLoop* m_EventLoop = Q_NULLPTR;
  QTimer* m_qtimeTimeOut = Q_NULLPTR;
  QString m_strErrorMessage = "NULL";
  //��ѯƵ�ʣ�Ĭ��0.2s
  int m_iTick = 200;
  //���ӳ�ʱ����
  int m_iTimeOut = 10000;
  //��ֻ����std::map����
  stdMapString* m_pShipData = NULL;
  
signals:
  void sigShipData(const stdMapString* mapShipData);
  void sigHttpLinkErrorMsg(const QString& strErrorMsg);

public slots :
  void slotLinkStart();
  void slotLinkClose();
};

#endif // _LINKOBJECT_H