
#ifndef _OBJECTCONTROL_H
#define _OBJECTCONTROL_H

#include "BaseClass/ControlBase.h"
#include "Data/Config.h"
#include "Data/OSGData.h"
#include "LinkBackground/LinkObject.h"
#include "LinkBackground/InitSystem.h"
#include "Control/OSGControl.h"
#include "Control/SelectShipControl.h"
#include <QtCore/QObject>

class jyObjectControl : public QObject, public jyControlBase
{
  Q_OBJECT

public:
  jyObjectControl(QObject* parent = Q_NULLPTR);
  ~jyObjectControl();
  //轮询
  void ThreadStart(const QString& shipid);
  void ThreadClose();
  void slotUpdateData(const stdMapString* shipdata);
  //初始化
  void startInitSystem();

  jyOSGControlPtr getOSGControl();
  jySelectShipControlPtr getSelectShipControl();

private:
  //轮询
  jyLinkObject* m_pLinkObject = Q_NULLPTR;
  QThread* m_pThread = Q_NULLPTR;
  //初始化
  jyInitSystem* m_pInitSystem = Q_NULLPTR;

  jyOSGControlPtr m_pOSGControl;
  jySelectShipControlPtr m_pSelectShipControl;

public slots:
  void slotInitSystemEnd(const stdMapString* initdata);
};

typedef std::shared_ptr<jyObjectControl> jyObjectControlPtr;

#endif // _OBJECTCONTROL_H