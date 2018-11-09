
#include "Control/LandControl.h"

jyLandControl::jyLandControl()
{
}

jyLandControl::~jyLandControl()
{
}

jyPoint jyLandControl::getCenterCoor()
{
  return m_pointCenterCoor;
}

void jyLandControl::initControlParam(const stdMapString * initdatagroup)
{
  const stdMapString::const_iterator itr = initdatagroup->find("LandCoordinate");
  if (itr == initdatagroup->cend())
    return;
  QString strTemLandCoor = QString::fromStdString(itr->second);
  QStringList strTemLandPoint = strTemLandCoor.mid(1, strTemLandCoor.length() - 2).split(',');
  double dTemLandX = (strTemLandPoint[0].toDouble() + strTemLandPoint[2].toDouble()) / 2;
  double dTemLandY = (strTemLandPoint[1].toDouble() + strTemLandPoint[3].toDouble()) / 2;
  m_pointCenterCoor = jyPoint(dTemLandX, dTemLandY, 0.0f);
  m_sigUpdateData();
}

jyPoint * jyLandControl::getPoint()
{
  return m_point;
}
