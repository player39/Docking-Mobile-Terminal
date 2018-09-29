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
  //������ͼ�ź�
  boostSig sig_updata;
  //�������꣬���Ǹ�Ϊ�ӷ������˻�ȡ�������꣬������ͬ��ǰ�˲���ÿ�ζ��ٱ��ر���һ��
  point m_pCenterPoint = {39420000.00000000, 4380000.00000000};
};

#endif
