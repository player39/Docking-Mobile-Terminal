#ifndef _SEACONTROL_H
#define _SEACONTROL_H

#include <Control/ControlBase.h>
#include <Model/BoatData.h>
/*
// 80*80格
#define Sea_LineNum 81
#define Sea_Delta 80*80*2*3
//频率划分个数
#define Sea_n 3
//方向划分个数
#define Sea_m 2
*/
class jySeaControl :public jyControlBase
{

public:
  jySeaControl();
  double *getThetas();
  //double **getAmplitudes();
  double *getOmegas();
  double *getKs();
  TexPoint *getTexPoint();
  int *getIndexArray();
  ~jySeaControl();
  OceanXZpoint* getOceanPoint();
  double m_amplitudes[3][2] = { 0.2,0.2,0.3,0.50,0.2,0.6 };

private:
  OceanXZpoint m_pOceanPoint[81*81];
  int m_iOceanPointIndex[38400];
  TexPoint m_iOceanTexPoint[20 * 20 * 2 * 3];
  double m_dThetas[2] = { 0.38,1.42 };
  double m_omegas[3] = { 3.27,3.31,3.42 };
  double m_ks[3] = { 1.091,1.118,1.1935 };


};

#endif
