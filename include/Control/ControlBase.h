#ifndef _CONTROLBASE_H
#define _CONTROLBASE_H
#include <boost/signals2.hpp>
#include <Model/BoatData.h>

typedef boost::signals2::signal<void()> boostSig;

class jyControlBase
{

public:
  jyControlBase();
  ~jyControlBase();
  boostSig& getUpdataSig();
  void emitSigUpdata();
  point getCenterPoint();

private:
  //更新视图信号
  boostSig sig_updata;
  //中心坐标，考虑改为从服务器端获取中心坐标，这样不同的前端不用每次都再本地保存一次
  point m_pCenterPoint = {39420000.00000000, 4380000.00000000};
};

#endif
