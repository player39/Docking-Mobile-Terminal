
#ifndef _UILINKWIDGET_H
#define _UILINKWIDGET_H

#include "ui_uiLinkShipWidget.h"
#include "LinkBackground/LinkObject.h"
#include "Control/ShipControl.h"

class uiLinkWidget : public QWidget
{
  Q_OBJECT

public:
  uiLinkWidget(QWidget* parent = Q_NULLPTR);
  ~uiLinkWidget();

  void setControl(jyShipControlPtr controller);

private:
  Ui::uiLinkShipWidget ui;
  jyLinkObject* m_pLinkObject = Q_NULLPTR;
  QThread* m_pThread = Q_NULLPTR;

  std::weak_ptr<jyShipControl> m_pControl;

public slots:
  void slotThreadStart();
  void slotThreadClose();
  void slotUpdateData(const stdMapString* shipdata);
};

#endif // _UILINKWIDGET_H