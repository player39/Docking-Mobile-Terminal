
#ifndef _UISELECTSHIPWIDGET_H
#define _UISELECTSHIPWIDGET_H

#include <QtCore/QObject>
#include <QtWidgets/QDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtCore/QVector>
#include <QtCore/QDebug>
#include "ui_uiSelectShipWidget.h"
#include "BaseClass/ViewBase.h"
#include "Control/SelectShipControl.h"
#include "Control/ObjectControl.h"

class uiSelectShipWidget :public QDialog, public jyViewBase<jySelectShipControl>
{
  Q_OBJECT

public:
  uiSelectShipWidget(QWidget* parent = Q_NULLPTR);
  ~uiSelectShipWidget();

  virtual void setMvcControl(jySelectShipControlPtr controller);
  virtual void updateData();
  //根据船只id添加button
  void addPushButton(const QStringList& ShipIDGroup);
  void setControl(jyObjectControlPtr controller);

private:
  Ui::uiSelectShipWidget ui;
  QVector<QPushButton*> m_pButtonGroup;
  boost::signals2::connection m_conUpdateData;
  std::weak_ptr<jyObjectControl> m_pObjectControl;

signals:


public slots :
  void slotLinkStart();

};

#endif // _SHIPLISTDIALOG_H