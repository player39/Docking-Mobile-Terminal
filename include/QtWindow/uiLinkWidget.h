
#ifndef _UILINKWIDGET_H
#define _UILINKWIDGET_H

#include "ui_uiLinkShipWidget.h"
#include "LinkBackground/LinkObject.h"
#include "Control/ObjectControl.h"

class uiLinkWidget : public QWidget
{
  Q_OBJECT

public:
  uiLinkWidget(QWidget* parent = Q_NULLPTR);
  ~uiLinkWidget();

  void setControl(jyObjectControlPtr controller);

private:
  Ui::uiLinkShipWidget ui;
  jyLinkObject* m_pLinkObject = Q_NULLPTR;
  QThread* m_pThread = Q_NULLPTR;

  std::weak_ptr<jyObjectControl> m_pObjectControl;

public slots:
  void slotThreadStart();
  void slotThreadClose();
  //void slotUpdateData(const stdMapString* shipdata);
};

#endif // _UILINKWIDGET_H