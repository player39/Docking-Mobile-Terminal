#ifndef _OSGCONTROL_H
#define _OSGCONTROL_H

#include <Control/ControlBase.h>
#include <Control/QLinkThread.h>
#include <Control/BoatControl.h>
#include <Control/OSGControl.h>
#include <Control/LandControl.h>
#include <Control/SkyBoxControl.h>
#include <Control/SeaControl.h>
#include <QtCore/QThread>

class jyOSGControl :public QObject,public jyControlBase
{
  Q_OBJECT
public:
  jyOSGControl();
 // jyLinkThread *getLinkThread();
  jyBoatControl *getBoatControl();
  jyLandControl *getLandControl();
  jySkyBoxControl *getSkyBoxControl();
  jySeaControl *getSeaControl();

private:
  //在这里维护每个视图的control
  jyBoatControl *m_pBoatControl = NULL;
  jyLandControl *m_pLandControl = NULL;
  jySkyBoxControl *m_pSkyBoxControl = NULL;
  jySeaControl *m_pSeaControl = NULL;
 // jyOSGControl *m_pOSGControl = NULL;

public slots:
 // void slotLink();
};

#endif
