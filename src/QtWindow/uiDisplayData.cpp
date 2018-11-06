
#include "QtWindow/uiDisplayData.h"

uiDisplayData::uiDisplayData(QWidget* parent /* = Q_NULLPTR */):
  QWidget(parent)
{
  ui.setupUi(this);
}

uiDisplayData::~uiDisplayData()
{
}

void uiDisplayData::updateData()
{
  const stdMapString* pShipData = this->getMvcControl()->getShipData();
  for (stdMapString::const_iterator itr = pShipData->cbegin(); itr != pShipData->cend(); ++itr)
  {
    std::cout << itr->first << " " << itr->second << std::endl;
  }
}
