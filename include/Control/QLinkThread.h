
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
  /*get set ����*/
  //�����û�ָ���Ĵ�ֻid
  void setBoatID(QString boatid);
  //��ȡ���ݣ��Լ�ֵ�Ե���ʽ
  QMap<QString, QString>& getDataMap();
  void clearDataMapRotate();

private:
  //QNetworkReply* m_pReply = NULL;
  QNetworkAccessManager* m_pAccessManager = NULL;
  QNetworkRequest* m_pRequest = NULL;
  QUrl m_sURL = "http://192.168.1.132:8000/CTest";
  //��ֻid
  QString m_strBoatID = "";
  //�յ������� ��������Ҳ����޸ģ�Ϊ�˱��ڲ������������Ŀ���������Json���ݸ�ʽ
  //Map insert����keyֵ��ͬ�Ḳ��ԭ�ȵ�ֵ
  QMap<QString, QString> m_qmapData;
  QByteArray m_byteSendData;
  QTimer* m_pTime = NULL;
  //bool m_bSendFlag = true;
  QMutex m_qmutexLock;

signals:
  //�������ӽ����Dialog
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
