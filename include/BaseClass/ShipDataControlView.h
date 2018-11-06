
#ifndef _SHIPDATACONTROLVIEW_H
#define _SHIPDATACONTROLVIEW_H

#include "BaseClass/ViewBase.h"
#include "Control/ShipControl.h"

class jyShipDataControlView : public jyViewBase<jyShipControl>
{
public:
  jyShipDataControlView();
  ~jyShipDataControlView();
  virtual void setMvcControl(jyShipControlPtr controller);
  virtual void updateData() {}

private:
  boost::signals2::connection m_conUpdateData;
};

#endif // _SHIPDATACONTROLVIEW_H