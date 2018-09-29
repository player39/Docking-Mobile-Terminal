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

point jyControlBase::getCenterPoint()
{
  return m_pCenterPoint;
}
