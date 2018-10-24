
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
  //添加负责渲染的widget
  void initWidget();
  //更新显示数据
  virtual void updataView();
  //将BoatControl的SigUpdata绑定到QtView，接收到python端的数据以后不仅要通知osgView更新图像也要通知QtView进行数据显示，如果不绑定每个Control的信号只能传送到上层View
  boost::signals2::connection connectUpdataBoatSignal(const slotType& type);
  //safe绿 danger红
  void changeWarningColor(QLabel* warninglabel);
  //主动调用去查看init结果 判断是否弹窗
  void checkInitResult();
  //主动调用去查看init中获取的船只id，进行自动连接
  void autoLinkShip();
  //返回ShipListDialog
  jyShipListDialog* getShipListDialog();


protected:
  virtual void paintEvent(QPaintEvent* event);

private:
  Ui::OSGBoat m_Ui;
  //刷新窗口
  QTimer* m_ptime = NULL;
  //弹窗
  jyParamDialog* m_pParamDialog = NULL;
  //渲染视图
  jyOSGView* m_pOSGView = NULL;
//QTimer *m_FlashTime = NULL;
  //维护船连接
  boost::signals2::connection m_BoatConnect;
  //自动连接船只的弹窗
  jyShipListDialog* m_pAutoLinkDialog = NULL;
  //显示小数的位数
  int m_iAccuracy = 2;

public slots:
  void slotShowLinkBoatDialog();
  //接收到ShipListDialog信号后与用户选择的船只连接
  void slotLinkShip(const QString& shipid);
  //void slotInitResultShow(QString InitFlag);
  //更改显示精度
  void slotChangeAccuracy();
};

#endif // _QTVIEW_H
