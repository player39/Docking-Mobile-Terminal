
#include "QtWindow/uiInitWidget.h"

uiInitWidget::uiInitWidget(QWidget* parent /* = Q_NULLPTR */):
  QWidget(parent)
{
  ui.setupUi(this);
  connect(ui.pushButton_Init, &QPushButton::clicked, this, &uiInitWidget::slotInitSystem);
  connect(ui.pushButton_Init, &QPushButton::clicked, this, &uiInitWidget::slotDeleteInitSystem);
}

uiInitWidget::~uiInitWidget()
{
}

void uiInitWidget::setControl(jyObjectControlPtr controller)
{
  m_pObjectControl = controller;
}

void uiInitWidget::slotInitSystem()
{
  m_pObjectControl.lock()->startInitSystem();
}

void uiInitWidget::slotDeleteInitSystem()
{

}