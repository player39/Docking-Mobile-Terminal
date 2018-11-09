
#ifndef _MATHMETHOD_H
#define _MATHMETHOD_H

#include <sstream>
#include <iostream>
#include <stdlib.h>

inline std::string DoubleToTimeData(double timedata)
{

  int _hour = timedata / 10000;
  int _minute = (timedata - _hour * 10000) / 100;
  double _sec = (timedata - _hour * 10000 - _minute * 100);
  char tem[15];
  sprintf(tem, "%.2f", _sec);
  std::string sSec = tem;
  std::string _TimeData = std::to_string(_hour) + ":" + std::to_string(_minute) + ":" + sSec;
  return _TimeData;
}
#endif // _MATHMETHOD_H