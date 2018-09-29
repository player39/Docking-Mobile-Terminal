#ifndef _QTCONTROL_H
#define _QTCONTROL_H

#include <Control/ControlBase.h>
#include <Control/QtParamControl.h>
#include <Control/OSGControl.h>
#include <boost/signals2.hpp>

//typedef boost::signals2::signal<void()>::slot_type slotType;
//Qt�����ڵ�control
class jyQtControl :public jyControlBase
{

public:
  jyQtControl();
  jyParamControl *getParamControl();
  jyOSGControl *getOSGControl();
//  void updataQtView();
//  boost::signals2::connection connectUpdataSignal(const slotType& type);

private:
  //ά��osg��control�����봰�ڵ�control
  jyParamControl *m_pParamControl = NULL;
  jyOSGControl *m_pOSGControl = NULL;
//  boost::signals2::connection m_pConnect;
};

#endif
