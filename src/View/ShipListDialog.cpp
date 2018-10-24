
#include <View/ShipListDialog.h>

jyShipListDialog::jyShipListDialog(jyShipListControl* controller, QMainWindow* parent) :
  jyViewBase(controller), QDialog(parent)
{
  ui.setupUi(this);
}

void jyShipListDialog::addPushButton(QStringList& ShipIDGroup)
{
  for(int i = 0; i< ShipIDGroup.length(); ++i)
  {
    m_vButtonGroup.append(new QPushButton(this));
    m_vButtonGroup[i]->setText("ShipID:" + ShipIDGroup[i]);
    ui.verticalLayout->addWidget(m_vButtonGroup[i]);
    connect(m_vButtonGroup[i], &QPushButton::clicked, this, &jyShipListDialog::slotEmitShipID);
  }
}

void jyShipListDialog::slotEmitShipID()
{
  QPushButton* pButton = qobject_cast<QPushButton*>(sender());
  QString strShipID = pButton->text().split(':')[1];
  emit sigShipID(strShipID);
}