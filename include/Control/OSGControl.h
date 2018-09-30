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
  //初始化渲染区域，完成获取中心坐标和自动连接船只的功能
  void initRender();
  jyBoatControl *getBoatControl();
  jyLandControl *getLandControl();
  jySkyBoxControl *getSkyBoxControl();
  jySeaControl *getSeaControl();

private:
  //在这里维护每个视图的control
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
  //进行http通信必要的事件循环使其变成同步，异步的话接收不到数据
  QEventLoop m_HttpLoop;
  //初始化成功与否的判断依据
  bool m_bInitFlag = true;
  //控制连接超时的timer
  QTimer m_HttpTimer;

signals:
  void sigInitFlag(bool initflag);

public slots:
  void slotFinished(QNetworkReply *reply);
  void slotLink();
  //发送初始化结果的信号
  void slotEmitInitSig();
  //post请求成功，进行InitFlag标志位设置，同时退出事件循环
  void slotHttpSuccessQuit();
  //post请求失败，~~~~~
  void slotHttpFailedQuit();
 // void slotLink();
};

#endif
