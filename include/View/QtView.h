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
#include <QtWidgets/QVBoxLayout>
#include <QtCore/QTimer>
#include <QtWidgets/QMessageBox>
#include <QtGui/QPalette>
#include "ui_OSGBoat.h"

class jyQtView :public QMainWindow,public jyViewBase<jyQtControl>
{

  Q_OBJECT

public:
  jyQtView(jyQtControl *controller);
  ~jyQtView();
  jyBoatControl *getBoatControl();
  //��Ӹ�����Ⱦ��widget
  void initWidget();
  //������ʾ����
  virtual void updataView();
  boost::signals2::connection connectUpdataBoatSignal(const slotType& type);
  //safe�� danger��
  void changeWarningColor(QLabel *warninglabel);

protected:
  virtual void paintEvent(QPaintEvent *event);

private:
  Ui::OSGBoat m_Ui;
  //ˢ�´���
  QTimer *m_ptime=NULL;
  //����
  jyParamDialog *m_pParamDialog=NULL;
  //��Ⱦ��ͼ
  jyOSGView *m_pOSGView = NULL;
//QTimer *m_FlashTime = NULL;
  //ά��������
  boost::signals2::connection m_BoatConnect;

public slots:
  void slotShowLinkBoatDialog();
};

#endif
