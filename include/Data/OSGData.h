#ifndef _OSGDATA_H
#define _OSGDATA_H

class jyPoint
{
public:
  jyPoint() {}
  jyPoint(double x, double y, double z) :x(x), y(y), z(z) {}
  jyPoint(const jyPoint& pointdata)
  {
    x = pointdata.x;
    y = pointdata.y;
    z = pointdata.z;
  }
  jyPoint& operator = (const jyPoint& pointdata) {
    x = pointdata.x;
    y = pointdata.y;
    z = pointdata.z;
    return *this;
  }
  double x;
  double y;
  double z;
};

class jyCameraParam
{
public:
  jyCameraParam() {}
  jyCameraParam(const jyPoint& eye, const jyPoint& center, const jyPoint& up) : eye(eye), center(center), up(up) {}
  jyCameraParam(const jyCameraParam& cameraparam)
  {
    eye = cameraparam.eye;
    center = cameraparam.center;
    up = cameraparam.up;
  }
  jyPoint eye;
  jyPoint center;
  jyPoint up;
};

class jyOSGParam
{
public:
  jyOSGParam() {}
  jyOSGParam(jyCameraParam cameraparam) : cameraParam(cameraparam) {}
  jyCameraParam cameraParam;
};

class jyLandParam
{
public:
  jyLandParam() {}
  jyLandParam(jyPoint landcoor) : landcoor(landcoor) {}
  jyPoint landcoor;
};

class jyShipData
{
public:
  jyShipData() {}
  jyPoint m_pointNowCoordinate = { 0,0,0 };
  //船速
  double m_dRate = 0;
  //时间
  QString m_strTime = "111";
  double m_dRotate = 0.0;
  //用来标记船上两个gps是否连通
  bool m_bGPSLinkFlag[2] = { false,false };
  /*三个距离，船中心点，船头船尾到岸基距离*/
  double m_dAveLandDistance = 0.0;
  double m_dLandDistance1 = 0.0;
  double m_dLandDistance2 = 0.0;
  //与岸基夹角
  double m_strLandRadio = 0.0;
  //服务器端发回的船的ID
  QString m_strID = "";
  //手持终端用户指定要连接船的ID
  QString m_strBoatID = "";
  //4个报警状态，分别是船头船尾 xy方向
  QString m_strHeadWarningX = "Danger";
  QString m_strHeadWarningY = "Danger";
  QString m_strSternWarningX = "Danger";
  QString m_strSternWarningY = "Danger";
  //船运动状态，加速减速匀速
  QString m_strMoveState = "Null";
};

#endif // _OSGDATA_H