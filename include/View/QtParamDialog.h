#ifndef _QTPARAMDIALOG_H
#define _QTPARAMDIALOG_H

#include <View/ViewBase.h>
#include <Control/QtParamControl.h>
#include <QtWidgets/QDialog>
#include <QtCore/QString>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QMainWindow>
#include "ui_ParamDialog.h"
//输入船只id的窗口
class jyParamDialog :public QDialog,public jyViewBase<jyParamControl>
{
  Q_OBJECT
public:
  jyParamDialog(jyParamControl *controller=0,QMainWindow *parent=Q_NULLPTR);
  Ui::LinkServerDialog getUI();

private:
  Ui::LinkServerDialog m_Ui;

signals :
  //发送船只id的信号给BoatControl做连接
  void sigSendBoatID(QString boatid);

public slots:
  //返回连接结果的函数，目前还没有用上
  void showLinkResult(bool resultflag);
  //发送包含船只id的信号
  void slotEmitBoatID();
};

#endif
