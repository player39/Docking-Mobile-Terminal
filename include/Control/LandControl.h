
#ifndef _LANDCONTROL_H
#define _LANDCONTROL_H

#include "BaseClass/ControlBase.h"
#include "Data/OSGData.h"

class jyLandControl : public jyControlBase
{
public:
  jyLandControl();
  ~jyLandControl();
  jyPoint getCenterCoor();
  virtual void initControlParam(const stdMapString* initdatagroup);
  jyPoint* getPoint();
  int m_fSurface[6][4] = { { 0, 1, 3, 2 } ,{ 2, 3, 7, 6 },{ 6, 7, 5, 4 },{ 4, 5, 1, 0 },{ 4, 6, 2, 0 },{ 5, 1, 3, 7 } };

private:
  jyPoint m_point[8] = { { 1000,-150,5 },{ 1000,-150,0 },{ -1000,-150,5 },{ -1000,-150,0 },{ 1000,150,5 },{ 1000,150,0 },{ -1000,150,5 },{ -1000,150,0 } };
  jyPoint m_pointCenterCoor = { 0,0,0 };

};

typedef std::shared_ptr<jyLandControl> jyLandControlPtr;

#endif // _LANDCONTROL_H