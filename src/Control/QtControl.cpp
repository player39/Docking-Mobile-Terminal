#include <Control/QtControl.h>

jyQtControl::jyQtControl()
{
  m_pParamControl = new jyParamControl();
  m_pOSGControl = new jyOSGControl();
  m_pAutoLinkControl = new jyShipListControl();
  //初始化岸基等数据
  m_pOSGControl->initRender();
 // m_pConnect = connectUpdataSignal(boost::bind(&jyQtControl::updataQtView,this));
}

jyParamControl* jyQtControl::getParamControl()
{
  return m_pParamControl;
}

jyOSGControl* jyQtControl::getOSGControl()
{
  return m_pOSGControl;
}
jyShipListControl* jyQtControl::getShipListControl()
{
  return m_pAutoLinkControl;
}
/*
boost::signals2::connection jyQtControl::connectUpdataSignal(const slotType& type)
{
  return m_pOSGControl->getBoatControl()->getUpdataSig().connect(type);
}*/
