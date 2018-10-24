#ifndef _LANDCONTROL_H
#define _LANDCONTROL_H

#include <Control/ControlBase.h>
#include <Model/BoatData.h>
#include <QtCore/QDebug>
//岸基，需要更改，数据应从服务器端获取（改完了）
class jyLandControl :public jyControlBase
{

public:
  jyLandControl();
  //从服务器端获取数据初始化Land
  void setLandCoordinate(double x, double y);
  point *getPoint();
  int m_fSurface[6][4] = { { 0, 1, 3, 2 } ,{ 2, 3, 7, 6 },{ 6, 7, 5, 4 },{ 4, 5, 1, 0 },{ 4, 6, 2, 0 },{ 5, 1, 3, 7 } };
  Matrix_Translate getTranslate();

private:
  point m_point[8] = { { 1000,-150,5 },{ 1000,-150,0 },{ -1000,-150,5 },{ -1000,-150,0 },{ 1000,150,5 },{ 1000,150,0 },{ -1000,150,5 },{ -1000,150,0 } };
  Matrix_Translate m_matrixTranslate = {0,0/* 39429295.12326589, 4385200.12379118 */};
};

#endif
