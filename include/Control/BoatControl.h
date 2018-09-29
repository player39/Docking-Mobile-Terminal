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
  /*get set����*/
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
  /*���嶥�㣬��ʱ�����������ά������Ϊ����ֵ��̫��ȡ��ʵ����Ӧ����ģ������*/
  int m_iSurface[6][4];
  point m_point[8];

private:
  /*���̲߳���*/
  jyLinkThread *m_pBoatLink = NULL;
  QThread *m_pLinkThread = NULL;
  /*��*/
  QMutex m_Lock;
  //���˶��Ļ�������
  Matrix_Translate m_mTranslate = {0,0,0}; //= {1244198.838750, 1300793.477073};
  Matrix_Rotate m_mRotate = { 0,0,0,0 };
  //��ǰ����
  point m_NowCoordinate = {0,0,0};
  //����
  double m_dRate=0;
  //ʱ��
  QString m_stime;
  double m_dRotate;
  //������Ǵ�������gps�Ƿ���ͨ
  bool m_bGPSLinkFlag[2] = {false,false};
  /*�������룬�����ĵ㣬��ͷ��β����������*/
  double m_dAveLandDistance;
  double m_dLandDistance1;
  double m_dLandDistance2;
  //�밶���н�
  QString m_sLandRadio;
  //�������˷��صĴ���ID
  QString m_sID="";
  //�ֳ��ն��û�ָ��Ҫ���Ӵ���ID
  QString m_sBoatID = "";
  //4������״̬���ֱ��Ǵ�ͷ��β xy����
  QString m_sHeadWarningX = "Danger";
  QString m_sHeadWarningY = "Danger";
  QString m_sSternWarningX = "Danger";
  QString m_sSternWarningY = "Danger";
  //���˶�״̬�����ټ�������
  QString m_sMoveState = "Null";
  //��ģ��

public slots:
  void slotChangeBoatData();
  //�����ӻ�ȡ��ֻ�˶�����
  void slotLink();
  //�ر�TCP����
  void slotLinkClose();
  //��Qt�㷢�����źŰ󶨣������û�ָ���Ĵ�ֻID
  void slotGetUrl(const QString boatid);
};

#endif //_BOATCONTROL_H
