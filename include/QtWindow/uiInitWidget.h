
#ifndef _UIINITWIDGET_H
#define _UIINITWIDGET_H

#include "ui_uiInitWidget.h"
#include "Control/ObjectControl.h"

class uiInitWidget : public QWidget
{
  Q_OBJECT

public:
  uiInitWidget(QWidget* parent = Q_NULLPTR);
  ~uiInitWidget();
  void setControl(jyObjectControlPtr controller);

private:
  Ui::uiInitWidget ui;
  std::weak_ptr<jyObjectControl> m_pObjectControl;

public slots:
  void slotInitSystem();
  void slotDeleteInitSystem();
};

#endif // _UIINITWIDGET_H