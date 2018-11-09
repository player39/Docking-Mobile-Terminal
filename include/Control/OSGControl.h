
#ifndef _OSGCONTROL_H
#define _OSGCONTROL_H

#include "BaseClass/ControlBase.h"
#include "Control/LandControl.h"
#include "Control/ShipControl.h"
#include "Control/OSGControl.h"
#include "Data/OSGData.h"

class jyOSGControl : public jyControlBase
{

public:
  jyOSGControl();
  ~jyOSGControl();
  jyShipControlPtr getShipControl();
  jyLandControlPtr getLandControl();
  void emitUpdateData(const stdMapString* initData);
  virtual void initControlParam(const stdMapString* initdatagroup);
  jyOSGParam getOSGData();

private:
  jyShipControlPtr m_pShipControl;
  jyLandControlPtr m_pLandControl;

  jyOSGParam m_OSGParam;
};

typedef std::shared_ptr<jyOSGControl> jyOSGControlPtr;

#endif // _OSGCONTROL_H