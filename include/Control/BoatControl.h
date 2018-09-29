#ifndef _BOATCONTROL_H
#define _BOATCONTROL_H

#include <Control/ControlBase.h>
#include <Control/QLinkThread.h>
#include <Model/BoatData.h>
#include <QtCore/QThread>
#include <QtCore/QMutex>

class jyBoatControl :public QObject, public jyControlBase
{
  Q_OBJECT

public:
  jyBoatControl();
  ~jyBoatControl();
  /*get set函数*/
  jyLinkThread *getLinkThread();
  point* getPoint();
  Matrix_Translate getTranslate();
  point getCoordinate();
  double getRotate();
  void setRotate(double rotate);
  double getLandAveDistance();
  double getDistance1();
  double getDistance2();
  bool* getGPSLinkFlag();
  QString getLandRadio();
  double getRate();
  QString getID();
  QString getTime();
  QString getMoveState();
  QString getHeadWarningX();
  QString getHeadWarningY();
  QString getSternWarningX();
  QString getSternWarningY();
  /*船体顶点，暂时定义在这里二维数组作为返回值不太好取，实际上应该是模型数据*/
  int m_iSurface[6][4];
  point m_point[8];

private:
  /*多线程部分*/
  jyLinkThread *m_pBoatLink = NULL;
  QThread *m_pLinkThread = NULL;
  /*锁*/
  QMutex m_Lock;
  //船运动的基本数据
  Matrix_Translate m_mTranslate = {0,0,0}; //= {1244198.838750, 1300793.477073};
  Matrix_Rotate m_mRotate = { 0,0,0,0 };
  //当前坐标
  point m_NowCoordinate = {0,0,0};
  //船速
  double m_dRate=0;
  //时间
  QString m_stime;
  double m_dRotate;
  //用来标记船上两个gps是否连通
  bool m_bGPSLinkFlag[2] = {false,false};
  /*三个距离，船中心点，船头船尾到岸基距离*/
  double m_dAveLandDistance;
  double m_dLandDistance1;
  double m_dLandDistance2;
  //与岸基夹角
  QString m_sLandRadio;
  //服务器端发回的船的ID
  QString m_sID="";
  //手持终端用户指定要连接船的ID
  QString m_sBoatID = "";
  //4个报警状态，分别是船头船尾 xy方向
  QString m_sHeadWarningX = "Danger";
  QString m_sHeadWarningY = "Danger";
  QString m_sSternWarningX = "Danger";
  QString m_sSternWarningY = "Danger";
  //船运动状态，加速减速匀速
  QString m_sMoveState = "Null";
  //船模型

public slots:
  void slotChangeBoatData();
  //打开连接获取船只运动数据
  void slotLink();
  //关闭TCP连接
  void slotLinkClose();
  //和Qt层发出的信号绑定，接收用户指定的船只ID
  void slotGetUrl(const QString boatid);
};

#endif //_BOATCONTROL_H
