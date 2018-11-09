
#include "QtWindow\uiParamControlWidget.h"

uiParamControlWidget::uiParamControlWidget(QWidget* parent /* = Q_NULLPTR */)
{
  ui.setupUi(this);
}

uiParamControlWidget::~uiParamControlWidget()
{
}

void uiParamControlWidget::setControlGroup(jyObjectControlPtr shipcontrol)
{
  ui.widget_Link->setControl(shipcontrol);
  ui.widget_Init->setControl(shipcontrol);
}
