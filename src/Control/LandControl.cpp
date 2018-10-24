#include "..\..\include\Control\LandControl.h"

jyLandControl::jyLandControl()
{
}

void jyLandControl::setLandCoordinate(double x, double y)
{
  m_matrixTranslate.x = x;
  m_matrixTranslate.y = y;
}

point * jyLandControl::getPoint()
{
  return m_point;
}

Matrix_Translate jyLandControl::getTranslate()
{
  return m_matrixTranslate;
}
