
#ifndef _SHIPCONTROL_H
#define _SHIPCONTROL_H

#include "BaseClass/ControlBase.h"
#include <string>

typedef std::map<std::string, std::string> stdMapString;

class jyShipControl :public jyControlBase
{
public:
  jyShipControl();
  ~jyShipControl();
  const stdMapString* getShipData();
  void setShipData(const stdMapString* shipdata);
  void emitUpdateSig(const stdMapString* shipdata);

private:
  const stdMapString* m_pShipData;
};

typedef std::shared_ptr<jyShipControl> jyShipControlPtr;

#endif // _SHIPCONTROL_H