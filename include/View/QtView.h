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
  //添加负责渲染的widget
  void initWidget();
  //更新显示数据
  virtual void updataView();
  boost::signals2::connection connectUpdataBoatSignal(const slotType& type);
  //safe绿 danger红
  void changeWarningColor(QLabel *warninglabel);

protected:
  virtual void paintEvent(QPaintEvent *event);

private:
  Ui::OSGBoat m_Ui;
  //刷新窗口
  QTimer *m_ptime=NULL;
  //弹窗
  jyParamDialog *m_pParamDialog=NULL;
  //渲染视图
  jyOSGView *m_pOSGView = NULL;
//QTimer *m_FlashTime = NULL;
  //维护船连接
  boost::signals2::connection m_BoatConnect;

public slots:
  void slotShowLinkBoatDialog();
};

#endif
