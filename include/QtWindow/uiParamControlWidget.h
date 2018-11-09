
#ifndef _UIPARAMCONTROLWIDGET_H
#define _UIPARAMCONTROLWIDGET_H

#include "ui_uiParamControlWidget.h"
#include "Control/ObjectControl.h"
#include "Control/ObjectControl.h"
#include <QtWidgets/QWidget>

class uiParamControlWidget : public QWidget
{
  Q_OBJECT

public:
  uiParamControlWidget(QWidget* parent = Q_NULLPTR);
  ~uiParamControlWidget();
  void setControlGroup(jyObjectControlPtr objectcontrol);

private:
  Ui::uiParamControlWidget ui;
};

#endif // _UIPARAMCONTROLWIDGET_H