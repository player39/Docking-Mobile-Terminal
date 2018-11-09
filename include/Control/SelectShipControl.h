
#ifndef _SELECTSHIPCONTROL_H
#define _SELECTSHIPCONTROL_H

#include "BaseClass/ControlBase.h"
#include <QtCore/QStringList>
#include <QtCore/QJsonArray>

class jySelectShipControl : public jyControlBase
{
public:
  jySelectShipControl();
  ~jySelectShipControl();
  QStringList getShipList();
  virtual void initControlParam(const stdMapString* initdatagroup);

private:
  QStringList m_strlShipList;
};

typedef std::shared_ptr<jySelectShipControl> jySelectShipControlPtr;

#endif // _SELECTSHIPCONTROL_H