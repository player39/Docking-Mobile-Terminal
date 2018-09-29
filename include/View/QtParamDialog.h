#ifndef _QTPARAMDIALOG_H
#define _QTPARAMDIALOG_H

#include <View/ViewBase.h>
#include <Control/QtParamControl.h>
#include <QtWidgets/QDialog>
#include <QtCore/QString>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QMainWindow>
#include "ui_ParamDialog.h"
//���봬ֻid�Ĵ���
class jyParamDialog :public QDialog,public jyViewBase<jyParamControl>
{
  Q_OBJECT
public:
  jyParamDialog(jyParamControl *controller=0,QMainWindow *parent=Q_NULLPTR);
  Ui::LinkServerDialog getUI();

private:
  Ui::LinkServerDialog m_Ui;

signals :
  //���ʹ�ֻid���źŸ�BoatControl������
  void sigSendBoatID(QString boatid);

public slots:
  //�������ӽ���ĺ�����Ŀǰ��û������
  void showLinkResult(bool resultflag);
  //���Ͱ�����ֻid���ź�
  void slotEmitBoatID();
};

#endif
