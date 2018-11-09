
#ifndef _INITSYSTEM_H
#define _INITSYSTEM_H

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
#include <iostream>
#include "Control/ShipControl.h"
#include "Data/Config.h"
#include "LinkBackground/LinkBase.h"

class jyInitSystem : public jyLinkBase
{
  Q_OBJECT

public:
  jyInitSystem(QObject* parent = Q_NULLPTR);
  ~jyInitSystem();
  void InitSystem();

private:
};

#endif // _INITSYSTEM_H