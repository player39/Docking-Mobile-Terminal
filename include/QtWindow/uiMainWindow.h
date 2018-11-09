
#ifndef _UIMAINWINDOW_H
#define _UIMAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "QtWindow/uiSelectShipWidget.h"
#include "ui_uiMainWindow.h"
#include "Control/OSGControl.h"
#include "Data/Config.h"
#include "OSGRender/OSGQtWidget.h"

class uiMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  uiMainWindow(QWidget* parent = Q_NULLPTR);
  ~uiMainWindow();

protected:
  virtual void paintEvent(QPaintEvent* event);
private:
  Ui::uiMainWindow ui;
  //jyShipControlPtr m_pShipControl;
  jyObjectControlPtr m_pObjectControl;
  uiSelectShipWidget* m_pSelectShipWidget = Q_NULLPTR;
  jyOSGQtWidget* m_pOSGQtWidget = NULL;
  QTimer* m_pFlashTimer = Q_NULLPTR;
};

#endif // _UIMAINWINDOW_H