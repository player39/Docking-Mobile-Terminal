
#ifndef _QTCONTROL_H
#define _QTCONTROL_H

#include <Control/ControlBase.h>
#include <Control/QtParamControl.h>
#include <Control/OSGControl.h>
#include <boost/signals2.hpp>
#include <QtCore/QObject>
#include <Control/ShipListControl.h>

//Qt�����ڵ�control
class jyQtControl :public jyControlBase
{

public:
  jyQtControl();
  jyParamControl* getParamControl();
  jyOSGControl* getOSGControl();
  jyShipListControl* getShipListControl();
//  void updataQtView();
//  boost::signals2::connection connectUpdataSignal(const slotType& type);

private:
  //ά��osg��control�����봰�ڵ�control
  jyParamControl* m_pParamControl = NULL;
  jyOSGControl* m_pOSGControl = NULL;
  jyShipListControl* m_pAutoLinkControl = NULL;
//  boost::signals2::connection m_pConnect;

};

#endif // _QTCONTROL_H
