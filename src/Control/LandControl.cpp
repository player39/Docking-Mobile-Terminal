#include "..\..\include\Control\LandControl.h"

jyLandControl::jyLandControl()
{
}

point * jyLandControl::getPoint()
{
  return m_point;
}

Matrix_Translate jyLandControl::getTranslate()
{
  return m_translate;
}
