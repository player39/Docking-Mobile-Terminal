
#ifndef _UIINITWIDGET_H
#define _UIINITWIDGET_H

#include "ui_uiInitWidget.h"

class uiInitWidget : public QWidget
{
  Q_OBJECT

public:
  uiInitWidget(QWidget* parent = Q_NULLPTR);
  ~uiInitWidget();

private:
  Ui::uiInitWidget ui;

};

#endif // _UIINITWIDGET_H