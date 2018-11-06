
#ifndef _UIDISPLAYPARAMWIDGET_H
#define _UIDISPLAYPARAMWIDGET_H

#include "ui_uiDisplayParamWidget.h"

class uiDisplayParamWidget : public QWidget
{
  Q_OBJECT

public:
  uiDisplayParamWidget(QWidget* parent = Q_NULLPTR);
  ~uiDisplayParamWidget();

private:
  Ui::uiDisplayParamWidget ui;
};

#endif // _UIDISPLAYPARAMWIDGET_H