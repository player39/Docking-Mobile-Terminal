
#include "LinkBackground/InitSystem.h"

#define TIMEOUT 200

jyInitSystem::jyInitSystem(QObject* parent /* = Q_NULLPTR */):
  jyLinkBase(parent)
{
  /*读取初始化参数，例如超时时间*/
  g_Settings.beginGroup("InitParam");
  QString strTimeout = "Timeout";
  if (g_Settings.value(strTimeout).isNull())
    g_Settings.setValue(strTimeout, TIMEOUT);
  this->setTimeout(g_Settings.value(strTimeout).toInt());
  g_Settings.endGroup();
  //拼接url地址
  char sURL[40] = "";
  sprintf(sURL, "%s:%d/%s", g_sURL.c_str(), g_iPort, g_sInitViewName.c_str());
  this->initNetworkParam(QString(sURL), QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
}

jyInitSystem::~jyInitSystem()
{
}

void jyInitSystem::InitSystem()
{
  QString strSendData = "";
  this->HttpLink(strSendData.toLatin1());
}
