
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
  void setRotate(double dRotate);
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
  jyLinkThread* m_pBoatLink = NULL;
  QThread* m_pLinkThread = NULL;
  /*��*/
  QMutex m_Lock;
  //���˶��Ļ�������
  Matrix_Translate m_matrixTranslate = {0,0,0}; //= {1244198.838750, 1300793.477073};
  Matrix_Rotate m_matrixRotate = { 0,0,0,0 };
  //��ǰ����
  point m_pointNowCoordinate = {0,0,0};
  //����
  double m_dRate=0;
  //ʱ��
  QString m_strTime = "";
  double m_dRotate = 0.0;
  //������Ǵ�������gps�Ƿ���ͨ
  bool m_bGPSLinkFlag[2] = {false,false};
  /*�������룬�����ĵ㣬��ͷ��β����������*/
  double m_dAveLandDistance = 0.0;
  double m_dLandDistance1 = 0.0;
  double m_dLandDistance2 = 0.0;
  //�밶���н�
  QString m_strLandRadio = "";
  //�������˷��صĴ���ID
  QString m_strID="";
  //�ֳ��ն��û�ָ��Ҫ���Ӵ���ID
  QString m_strBoatID = "";
  //4������״̬���ֱ��Ǵ�ͷ��β xy����
  QString m_strHeadWarningX = "Danger";
  QString m_strHeadWarningY = "Danger";
  QString m_strSternWarningX = "Danger";
  QString m_strSternWarningY = "Danger";
  //���˶�״̬�����ټ�������
  QString m_strMoveState = "Null";
  //��ģ��

public slots:
  void slotChangeBoatData();
  //�����ӻ�ȡ��ֻ�˶�����
  void slotLink();
  //�ر�TCP����
  void slotLinkClose();
  //��Qt�㷢�����źŰ󶨣������û�ָ���Ĵ�ֻID
  void slotGetUrl(const QString& boatid);
};

#endif //_BOATCONTROL_H
