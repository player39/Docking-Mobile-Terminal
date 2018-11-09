#include "Control\SelectShipControl.h"

jySelectShipControl::jySelectShipControl()
{
}

jySelectShipControl::~jySelectShipControl()
{
}

QStringList jySelectShipControl::getShipList()
{
  return m_strlShipList;
}

void jySelectShipControl::initControlParam(const stdMapString * initdatagroup)
{
  QString strTemShipID = QString::fromStdString(initdatagroup->find("ShipID")->second);
  strTemShipID.remove('\'');
  m_strlShipList = strTemShipID.mid(1, strTemShipID.length() - 2).split(',');
  //发送信号通知view是否弹窗
  m_sigUpdateData();
}
