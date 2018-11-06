
#ifndef _UIMAINWINDOW_H
#define _UIMAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "ui_uiMainWindow.h"
#include "Control/ShipControl.h"
#include "Data/Config.h"

class uiMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  uiMainWindow(QWidget* parent = Q_NULLPTR);
  ~uiMainWindow();

private:
  Ui::uiMainWindow ui;
  jyShipControlPtr m_pShipControl;
};

#endif // _UIMAINWINDOW_H