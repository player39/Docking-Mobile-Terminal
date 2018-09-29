#include <Control/QtControl.h>

jyQtControl::jyQtControl()
{
  m_pParamControl = new jyParamControl();
  m_pOSGControl = new jyOSGControl();
 // m_pConnect = connectUpdataSignal(boost::bind(&jyQtControl::updataQtView,this));
}

jyParamControl *jyQtControl::getParamControl()
{
  return m_pParamControl;
}

jyOSGControl * jyQtControl::getOSGControl()
{
  return m_pOSGControl;
}
/*
boost::signals2::connection jyQtControl::connectUpdataSignal(const slotType& type)
{
  return m_pOSGControl->getBoatControl()->getUpdataSig().connect(type);
}*/
