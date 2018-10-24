#ifndef _BOATDATA_H
#define _BOATDATA_H
#include <string>

struct Matrix_Translate
{
  double x;
  double y;
  double z;
  Matrix_Translate(double _x = 0.0, double _y = 0.0, double _z = 0.0) :x(_x), y(_y), z(_z) {};
    Matrix_Translate& operator = (Matrix_Translate &value) {
    x = value.x;
    y = value.y;
    z = value.z;
    return *this;
  }
};

//double转时间格式,不加上inline会报链接错误
inline std::string DoubleToTimeData(double timedata)
{
  int _hour = timedata / 10000;
  int _minute = (timedata - _hour * 10000) / 100;
  double _sec = (timedata - _hour * 10000 - _minute * 100);
  std::string _TimeData = std::to_string(_hour) + ":" + std::to_string(_minute) + ":" + std::to_string(_sec);
  return _TimeData;
}

struct Matrix_Rotate
{
  float Radio;
  float x;
  float y;
  float z;
  Matrix_Rotate(float _radio = 0.0, float _x = 0.0, float _y = 0.0, float _z = 0.0) :x(_x), y(_y), z(_z) {};
  Matrix_Rotate& operator = (Matrix_Rotate &value) {
    Radio = value.Radio;
    x = value.x;
    y = value.y;
    z = value.z;
    return *this;
  }
};

struct OceanXZpoint
{
  float x;
  float z;
  OceanXZpoint(float _x = 0.0, float _z = 0.0) :x(_x), z(_z) {};
};

struct TexPoint 
{
  double x;
  double y;
  TexPoint(double _x = 0, double _y = 0) :x(_x), y(_y) {};
  TexPoint& operator = (TexPoint &value) {
    x = value.x;
    y = value.y;
    return *this;
  }
};

struct point
{
  double x;
  double y;
  double z;
  point(double _x = 0.0, double _y = 0.0, double _z = 0.0) :x(_x), y(_y), z(_z) {};
  point& operator = (point &value) {
    x = value.x;
    y = value.y;
    z = value.z;
    return *this;
  }
};
#endif
