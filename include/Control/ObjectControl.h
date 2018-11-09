
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
  //��ѯ
  void ThreadStart(const QString& shipid);
  void ThreadClose();
  void slotUpdateData(const stdMapString* shipdata);
  //��ʼ��
  void startInitSystem();

  jyOSGControlPtr getOSGControl();
  jySelectShipControlPtr getSelectShipControl();

private:
  //��ѯ
  jyLinkObject* m_pLinkObject = Q_NULLPTR;
  QThread* m_pThread = Q_NULLPTR;
  //��ʼ��
  jyInitSystem* m_pInitSystem = Q_NULLPTR;

  jyOSGControlPtr m_pOSGControl;
  jySelectShipControlPtr m_pSelectShipControl;

public slots:
  void slotInitSystemEnd(const stdMapString* initdata);
};

typedef std::shared_ptr<jyObjectControl> jyObjectControlPtr;

#endif // _OBJECTCONTROL_H