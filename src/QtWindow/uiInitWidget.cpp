
#include "QtWindow/uiInitWidget.h"

uiInitWidget::uiInitWidget(QWidget* parent /* = Q_NULLPTR */):
  QWidget(parent)
{
  ui.setupUi(this);
}

uiInitWidget::~uiInitWidget()
{
}