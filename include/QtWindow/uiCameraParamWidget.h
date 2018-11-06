
#ifndef _UICAMERAPARAMWIDGET_H
#define _UICAMERAPARAMWIDGET_H

#include "ui_uiCameraParamWidget.h"

class uiCameraParamWidget : public QWidget
{
  Q_OBJECT

public:
  uiCameraParamWidget(QWidget* parent = Q_NULLPTR);
  ~uiCameraParamWidget();

private:
  Ui::uiCameraParamWidget ui;
};

#endif // _UICAMERAPARAMWIDGET_H