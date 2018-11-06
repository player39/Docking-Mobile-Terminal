
#include "Control/ShipControl.h"

jyShipControl::jyShipControl()
{

}

jyShipControl::~jyShipControl()
{
}

const stdMapString* jyShipControl::getShipData()
{
  return m_pShipData;
}

void jyShipControl::setShipData(const stdMapString* shipdata)
{
  
}

void jyShipControl::emitUpdateSig(const stdMapString* shipdata)
{
  if(m_pShipData!=shipdata)
    m_pShipData = shipdata;
  m_sigUpdateData();
}

