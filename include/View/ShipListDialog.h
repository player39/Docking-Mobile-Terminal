
#ifndef _SHIPLISTDIALOG_H
#define _SHIPLISTDIALOG_H

#include <View/ViewBase.h>
#include <Control/ShipListControl.h>
#include <QtCore/QObject>
#include <QtWidgets/QDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtCore/QVector>
#include <QtCore/QDebug>
#include "ui_InitShipList.h"

class jyShipListDialog :public QDialog, public jyViewBase<jyShipListControl>
{

  Q_OBJECT

public:
  jyShipListDialog(jyShipListControl* controller = 0, QMainWindow* parent = Q_NULLPTR);
  //根据船只id添加button
  void addPushButton(QStringList& ShipIDGroup);

private:
  Ui::InitShipList_ui ui;
  QVector<QPushButton*> m_vButtonGroup;

signals:
  void sigShipID(const QString& shipidgroup);

public slots:
  void slotEmitShipID();
  //void slotLinkShip();

};

#endif // _SHIPLISTDIALOG_H
