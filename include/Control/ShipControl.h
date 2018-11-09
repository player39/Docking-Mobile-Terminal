
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
  /*���嶥�㣬��ʱ�����������ά������Ϊ����ֵ��̫��ȡ��ʵ����Ӧ����ģ������*/
  int m_iSurface[6][4];
  jyPoint m_point[8];

private:
  jyShipData m_shipData;
  const stdMapString* m_pShipData = NULL;
  std::string m_sBackLinkState = "";
  //��������
  //���˶��Ļ�������
  jyPoint m_matrixTranslate = {0, 0, 0}; //= {1244198.838750, 1300793.477073};
                                                  //��ǰ����
  jyPoint m_pointLastCoordinate = { 0,0,0 };
};

typedef std::shared_ptr<jyShipControl> jyShipControlPtr;

#endif // _SHIPCONTROL_H