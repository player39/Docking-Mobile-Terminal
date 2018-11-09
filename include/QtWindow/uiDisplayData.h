
#ifndef _UIDATADISPLAY_H
#define _UIDATADISPLAY_H

#include "ui_uiDisplayData.h"
#include "BaseClass/ShipDataControlView.h"
#include "Math/MathMethod.h"
#include <QtWidgets/QWidget>
#include <iostream>
#include <sstream>

class uiDisplayData : public QWidget, public jyShipDataControlView
{
  Q_OBJECT

public:
  uiDisplayData(QWidget* parent = Q_NULLPTR);
  ~uiDisplayData();
  void changeWarningColor(QLabel* warninglabel);
  virtual void updateData();

private:
  Ui::uiDisplayData ui;
  int m_iAccuracy = 2;
};

#endif // _UIDATADISPLAY_H