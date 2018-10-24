
#ifndef _QTVIEW_H
#define _QTVIEW_H

#include <QtWidgets/QMainWindow>
#include <QtCore/QTimer>
#include <QtWidgets/QPushButton>
#include <View/ViewBase.h>
#include <View/QtParamDialog.h>
#include <Control/QtControl.h>
#include <Control/QLinkThread.h>
#include <View/OSGView.h>
#include <View/ShipListDialog.h>
#include <QtWidgets/QVBoxLayout>
#include <QtCore/QTimer>
#include <QtWidgets/QMessageBox>
#include <QtGui/QPalette>
#include "ui_OSGBoat.h"

class jyQtView :public QMainWindow, public jyViewBase<jyQtControl>
{

  Q_OBJECT

public:
  jyQtView(jyQtControl* controller);
  ~jyQtView();
  jyBoatControl* getBoatControl();
  //��Ӹ�����Ⱦ��widget
  void initWidget();
  //������ʾ����
  virtual void updataView();
  //��BoatControl��SigUpdata�󶨵�QtView�����յ�python�˵������Ժ󲻽�Ҫ֪ͨosgView����ͼ��ҲҪ֪ͨQtView����������ʾ���������ÿ��Control���ź�ֻ�ܴ��͵��ϲ�View
  boost::signals2::connection connectUpdataBoatSignal(const slotType& type);
  //safe�� danger��
  void changeWarningColor(QLabel* warninglabel);
  //��������ȥ�鿴init��� �ж��Ƿ񵯴�
  void checkInitResult();
  //��������ȥ�鿴init�л�ȡ�Ĵ�ֻid�������Զ�����
  void autoLinkShip();
  //����ShipListDialog
  jyShipListDialog* getShipListDialog();


protected:
  virtual void paintEvent(QPaintEvent* event);

private:
  Ui::OSGBoat m_Ui;
  //ˢ�´���
  QTimer* m_ptime = NULL;
  //����
  jyParamDialog* m_pParamDialog = NULL;
  //��Ⱦ��ͼ
  jyOSGView* m_pOSGView = NULL;
//QTimer *m_FlashTime = NULL;
  //ά��������
  boost::signals2::connection m_BoatConnect;
  //�Զ����Ӵ�ֻ�ĵ���
  jyShipListDialog* m_pAutoLinkDialog = NULL;
  //��ʾС����λ��
  int m_iAccuracy = 2;

public slots:
  void slotShowLinkBoatDialog();
  //���յ�ShipListDialog�źź����û�ѡ��Ĵ�ֻ����
  void slotLinkShip(const QString& shipid);
  //void slotInitResultShow(QString InitFlag);
  //������ʾ����
  void slotChangeAccuracy();
};

#endif // _QTVIEW_H
