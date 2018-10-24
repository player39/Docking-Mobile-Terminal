
#ifndef _QLINKTHREAD_H
#define _QLINKTHREAD_H

#include <QtCore/QThread>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QTimer>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QMap>
#include <QtCore/QMutex>

class jyLinkThread :public QObject
{

  Q_OBJECT

public:
  jyLinkThread();
  ~jyLinkThread();
  /*get set 函数*/
  //设置用户指定的船只id
  void setBoatID(QString boatid);
  //获取数据，以键值对的形式
  QMap<QString, QString>& getDataMap();
  void clearDataMapRotate();

private:
  //QNetworkReply* m_pReply = NULL;
  QNetworkAccessManager* m_pAccessManager = NULL;
  QNetworkRequest* m_pRequest = NULL;
  QUrl m_sURL = "http://192.168.1.132:8000/CTest";
  //船只id
  QString m_strBoatID = "";
  //收到的数据 数据类型也许会修改，为了便于操作。送来过的可能是乱序Json数据格式
  //Map insert方法key值相同会覆盖原先的值
  QMap<QString, QString> m_qmapData;
  QByteArray m_byteSendData;
  QTimer* m_pTime = NULL;
  //bool m_bSendFlag = true;
  QMutex m_qmutexLock;

signals:
  //返回连接结果给Dialog
  void sigLinkResult(QString result);
  void sigGetData();

public slots:
 // void slotEmitsigLinkResult();
  void slotGetURL(const QString& mboatid);
  void slotFinished(QNetworkReply* reply);
  void slotLinkStart();
  void slotLinkFinished();
  void slotLink();
};
#endif //_QLINKTHREAD_H
