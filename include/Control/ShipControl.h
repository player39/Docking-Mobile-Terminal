
#ifndef _SHIPCONTROL_H
#define _SHIPCONTROL_H

#include "BaseClass/ControlBase.h"
#include "Data/OSGData.h"
#include "Data/Config.h"

class jyShipControl : public jyControlBase
{
public:
  jyShipControl();
  ~jyShipControl();
  void emitUpdateSig(const stdMapString* shipdata);
  void setLinkState(const QString & linkstate);
  std::string getLinkState();
  const jyShipData& getShipData();
  void handleShipData();
  jyPoint getMatrixTranslate();
  /*船体顶点，暂时定义在这里二维数组作为返回值不太好取，实际上应该是模型数据*/
  int m_iSurface[6][4];
  jyPoint m_point[8];

private:
  jyShipData m_shipData;
  const stdMapString* m_pShipData = NULL;
  std::string m_sBackLinkState = "";
  //顶点数据
  //船运动的基本数据
  jyPoint m_matrixTranslate = {0, 0, 0}; //= {1244198.838750, 1300793.477073};
                                                  //当前坐标
  jyPoint m_pointLastCoordinate = { 0,0,0 };
};

typedef std::shared_ptr<jyShipControl> jyShipControlPtr;

#endif // _SHIPCONTROL_H