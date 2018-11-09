
#include "Control/OSGControl.h"

#define CAMERAYCOOR 900.0f

jyOSGControl::jyOSGControl()
{
  m_pLandControl.reset(new jyLandControl);
  m_pShipControl.reset(new jyShipControl);
}

jyOSGControl::~jyOSGControl()
{
}

jyShipControlPtr jyOSGControl::getShipControl()
{
  return m_pShipControl;
}

jyLandControlPtr jyOSGControl::getLandControl()
{
  return m_pLandControl;
}

void jyOSGControl::emitUpdateData(const stdMapString* initData)
{
  m_sigUpdateData();
}

void jyOSGControl::initControlParam(const stdMapString * initdatagroup)
{
  QString strTemLandCoor = QString::fromStdString(initdatagroup->find("LandCoordinate")->second);
  QStringList strTemLandPoint = strTemLandCoor.mid(1, strTemLandCoor.length() - 2).split(',');
  double dTemCameraX = (strTemLandPoint[0].toDouble() + strTemLandPoint[2].toDouble()) / 2;
  double dTemCameraY = (strTemLandPoint[1].toDouble() + strTemLandPoint[3].toDouble()) / 2 + CAMERAYCOOR;
  double dTemCameraZ = 400.0f;

  jyPoint eye = jyPoint(dTemCameraX, dTemCameraY, dTemCameraZ);
  jyPoint center = jyPoint(dTemCameraX, dTemCameraY, 0);
  jyPoint up = jyPoint(-1, 0, 0);
  m_OSGParam.cameraParam = jyCameraParam(eye, center, up);
  //发信号通知view更新视图
  m_sigUpdateData();
}

jyOSGParam jyOSGControl::getOSGData()
{
  return m_OSGParam;
}
