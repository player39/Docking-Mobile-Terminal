#ifndef _OSGCONTROL_H
#define _OSGCONTROL_H

#include <Control/ControlBase.h>
#include <Control/QLinkThread.h>
#include <Control/BoatControl.h>
#include <Control/OSGControl.h>
#include <Control/LandControl.h>
#include <Control/SkyBoxControl.h>
#include <Control/SeaControl.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QEventLoop>

class jyOSGControl :public QObject,public jyControlBase
{
  Q_OBJECT
public:
  jyOSGControl();
 // jyLinkThread *getLinkThread();
  //��ʼ����Ⱦ������ɻ�ȡ����������Զ����Ӵ�ֻ�Ĺ���
  void initRender();
  jyBoatControl *getBoatControl();
  jyLandControl *getLandControl();
  jySkyBoxControl *getSkyBoxControl();
  jySeaControl *getSeaControl();

private:
  //������ά��ÿ����ͼ��control
  jyBoatControl *m_pBoatControl = NULL;
  jyLandControl *m_pLandControl = NULL;
  jySkyBoxControl *m_pSkyBoxControl = NULL;
  jySeaControl *m_pSeaControl = NULL;
 // jyOSGControl *m_pOSGControl = NULL;
  QNetworkAccessManager *m_AccessManager = NULL;
  QString m_sUrl = "";
  QNetworkRequest *m_initCoordinateRequest = NULL;
  QNetworkRequest m_autoLink;
  QNetworkReply *m_pReply=NULL;
  //����httpͨ�ű�Ҫ���¼�ѭ��ʹ����ͬ�����첽�Ļ����ղ�������
  QEventLoop m_HttpLoop;
  //��ʼ���ɹ������ж�����
  bool m_bInitFlag = true;
  //�������ӳ�ʱ��timer
  QTimer m_HttpTimer;

signals:
  void sigInitFlag(bool initflag);

public slots:
  void slotFinished(QNetworkReply *reply);
  void slotLink();
  //���ͳ�ʼ��������ź�
  void slotEmitInitSig();
  //post����ɹ�������InitFlag��־λ���ã�ͬʱ�˳��¼�ѭ��
  void slotHttpSuccessQuit();
  //post����ʧ�ܣ�~~~~~
  void slotHttpFailedQuit();
 // void slotLink();
};

#endif
