#include "..\..\include\Control\ControlBase.h"

jyControlBase::jyControlBase()
{
}

jyControlBase::~jyControlBase()
{
}

boostSig & jyControlBase::getUpdataSig()
{
  // TODO: insert return statement here
  return sig_updata;
}

void jyControlBase::emitSigUpdata()
{
  sig_updata();
}
/*
point jyControlBase::getCenterPoint()
{
  return m_pCenterPoint;
}
*/
std::string jyControlBase::getBackgroundUrl()
{
  return m_sUrl;
}
/*
void jyControlBase::setCenterPoint(double x, double y)
{
  m_pCenterPoint.x = x;
  m_pCenterPoint.y = y;
}
*/