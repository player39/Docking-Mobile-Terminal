#include "..\..\include\View\QtParamDialog.h"

jyParamDialog::jyParamDialog(jyParamControl* controller, QMainWindow* parent) :jyViewBase(controller), QDialog(parent)
{
  m_Ui.setupUi(this);
  connect(m_Ui.pushButton_LinkStart, &QPushButton::clicked, this, &jyParamDialog::slotEmitBoatID);
  connect(m_Ui.pushButton_Cancel, &QPushButton::clicked, this, &jyParamDialog::close);
}

void jyParamDialog::EmitShipID(const QString& shipid)
{
  emit sigSendBoatID(shipid);
}

Ui::LinkServerDialog jyParamDialog::getUI()
{
  return m_Ui;
}

void jyParamDialog::slotEmitBoatID()
{
  emit sigSendBoatID(m_Ui.lineEdit_BoatID->text());
}

void jyParamDialog::showLinkResult(bool resultflag)
{
  if (resultflag)
    QMessageBox::critical(NULL,"Error", "LinkError");
}
