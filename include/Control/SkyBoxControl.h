
#ifndef _SKYBOXCONTROL_H
#define _SKYBOXCONTROL_H

#include <Control/ControlBase.h>

class jySkyBoxControl :public jyControlBase
{
public:
  jySkyBoxControl();
  ~jySkyBoxControl();
  float getRadius();
  float *getTexCoordinate();
  int getTexCoorLength();


private:
  //ÇÐ·Ö¼ä¸ô
  float m_fAngleSpan = 18;
  float m_fAngleV = 90;
  float *m_fTexCoordinate;
  int m_iTexCoorLength = 0;
  float m_fSkyBoxRadius=6000000.0f;
};

#endif //_SKYBOXCONTROL_H
