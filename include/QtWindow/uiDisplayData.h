
#ifndef _UIDATADISPLAY_H
#define _UIDATADISPLAY_H

#include "ui_uiDisplayData.h"
#include "BaseClass/ShipDataControlView.h"
#include <QtWidgets/QWidget>
#include <iostream>

class uiDisplayData : public QWidget, public jyShipDataControlView
{
  Q_OBJECT

public:
  uiDisplayData(QWidget* parent = Q_NULLPTR);
  ~uiDisplayData();
  virtual void updateData();

private:
  Ui::uiDisplayData ui;
};

#endif // _UIDATADISPLAY_H