
#include "QtWindow/uiLinkWidget.h"

uiLinkWidget::uiLinkWidget(QWidget* parent /* = Q_NULLPTR */):
  QWidget(parent)
{
  ui.setupUi(this);
  connect(ui.pushButton_Link, &QPushButton::clicked, this, &uiLinkWidget::slotThreadStart);
  connect(ui.pushButton_Stop, &QPushButton::clicked, this, &uiLinkWidget::slotThreadClose);
}

uiLinkWidget::~uiLinkWidget()
{
}

void uiLinkWidget::setControl(jyObjectControlPtr controller)
{
  m_pObjectControl = controller;
}

void uiLinkWidget::slotThreadStart()
{
  m_pObjectControl.lock()->ThreadStart(ui.lineEdit_ShipID->text());
}

void uiLinkWidget::slotThreadClose()
{
  m_pObjectControl.lock()->ThreadClose();
}
/*
void uiLinkWidget::slotUpdateData(const stdMapString* shipdata)
{
  m_pControl.lock()->emitUpdateSig(shipdata);
}
*/

