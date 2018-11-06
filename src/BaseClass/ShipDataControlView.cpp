
#include "BaseClass/ShipDataControlView.h"

jyShipDataControlView::jyShipDataControlView()
{
}

jyShipDataControlView::~jyShipDataControlView()
{
  m_conUpdateData.disconnect();
}

void jyShipDataControlView::setMvcControl(jyShipControlPtr controller)
{
  m_conUpdateData.disconnect();
  jyViewBase::setMvcControl(controller);

  if (controller)
    m_conUpdateData = controller->connectUpdateData(boost::bind(&jyShipDataControlView::updateData, this));

}
/*
void jyShipDataControlView::updateData()
{
}*/
