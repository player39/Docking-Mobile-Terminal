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
  //�����ź�֪ͨview�Ƿ񵯴�
  m_sigUpdateData();
}
