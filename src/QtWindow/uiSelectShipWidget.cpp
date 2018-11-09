
#include "QtWindow/uiSelectShipWidget.h"

uiSelectShipWidget::uiSelectShipWidget(QWidget* parent) :
  QDialog(parent)
{
  ui.setupUi(this);
}

uiSelectShipWidget::~uiSelectShipWidget()
{
  m_conUpdateData.disconnect();
}

void uiSelectShipWidget::setMvcControl(jySelectShipControlPtr controller)
{
  m_conUpdateData.disconnect();
  jyViewBase::setMvcControl(controller);
  if (controller)
    m_conUpdateData = controller->connectUpdateData(boost::bind(&uiSelectShipWidget::updateData, this));
}

void uiSelectShipWidget::setControl(jyObjectControlPtr controller)
{
  m_pObjectControl = controller;
}

void uiSelectShipWidget::updateData()
{
  jySelectShipControlPtr pSelectShipControl = this->getMvcControl();
  QStringList strlShipList = pSelectShipControl->getShipList();
  if (strlShipList.length() > 1)
  {
    addPushButton(strlShipList);
    this->show();
  }
  else
  {
    if (strlShipList.length())
      return;
    m_pObjectControl.lock()->ThreadStart(strlShipList[0]);
  }
}

void uiSelectShipWidget::addPushButton(const QStringList& ShipIDGroup)
{
  for (int i = 0; i < ShipIDGroup.length(); ++i)
  {
    m_pButtonGroup.append(new QPushButton(this));
    m_pButtonGroup[i]->setText("ShipID:" + ShipIDGroup[i]);
    ui.ShipList->addWidget(m_pButtonGroup[i]);
    connect(m_pButtonGroup[i], &QPushButton::clicked, this, &uiSelectShipWidget::slotLinkStart);
  }
}

void uiSelectShipWidget::slotLinkStart()
{
  QPushButton* pButton = qobject_cast<QPushButton*>(sender());
  QString strShipID = pButton->text().split(':')[1];
  m_pObjectControl.lock()->ThreadStart(strShipID);
  this->close();
}
