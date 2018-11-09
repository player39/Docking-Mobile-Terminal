
#include "QtWindow/uiDisplayData.h"

uiDisplayData::uiDisplayData(QWidget* parent /* = Q_NULLPTR */):
  QWidget(parent)
{
  ui.setupUi(this);
}

uiDisplayData::~uiDisplayData()
{
}

void uiDisplayData::changeWarningColor(QLabel * warninglabel)
{
  QPalette palette;
  if (warninglabel->text() == "Safe")
  {
    palette.setColor(QPalette::WindowText, Qt::green);
  }
  else
  {
    palette.setColor(QPalette::WindowText, Qt::red);
  }
  warninglabel->setPalette(palette);
}

void uiDisplayData::updateData()
{
  jyShipControlPtr pShipControl = this->getMvcControl();
  const jyShipData& shipData = pShipControl->getShipData();

  pShipControl->getLinkState();

  if (shipData.m_bGPSLinkFlag[0] || shipData.m_bGPSLinkFlag[1])
  {
    ui.label_Distance->setText(QString::number(shipData.m_dAveLandDistance, 'f', m_iAccuracy));
    QString strTemCoor = QString::number(shipData.m_pointNowCoordinate.x, 'f', m_iAccuracy) + "," + QString::number(shipData.m_pointNowCoordinate.y, 'f', m_iAccuracy);
    ui.label_Coordinate->setText(strTemCoor);
    ui.label_ShipRate->setText(QString::number(shipData.m_dRate, 'f', m_iAccuracy));
    ui.label_Distance1->setText(QString::number(shipData.m_dLandDistance1, 'f', m_iAccuracy));
    ui.label_Distance2->setText(QString::number(shipData.m_dLandDistance2, 'f', m_iAccuracy));
    ui.label_ShipID->setText(shipData.m_strBoatID);
    ui.label_Time->setText(QString::fromLocal8Bit(DoubleToTimeData(shipData.m_strTime.toDouble()).c_str()));
    ui.label_Radio->setText(QString::number(shipData.m_strLandRadio, 'f', m_iAccuracy));
    ui.label_GPS1->setText(QString::number(shipData.m_bGPSLinkFlag[0]));
    ui.label_GPS2->setText(QString::number(shipData.m_bGPSLinkFlag[1]));
    ui.label_GPSLinkState->setText("LinkSuccess");
    ui.label_MoveState->setText(shipData.m_strMoveState);
    ui.label_HeadWarningX->setText(shipData.m_strHeadWarningX);
    ui.label_HeadWarningY->setText(shipData.m_strHeadWarningY);
    ui.label_SternWarningX->setText(shipData.m_strSternWarningX);
    ui.label_SternWarningY->setText(shipData.m_strSternWarningY);
    changeWarningColor(ui.label_HeadWarningX);
    changeWarningColor(ui.label_HeadWarningY);
    changeWarningColor(ui.label_SternWarningX);
    changeWarningColor(ui.label_SternWarningY);
  }
  else
  {
    ui.label_GPS1->setText(QString::number(shipData.m_bGPSLinkFlag[0]));
    ui.label_GPS2->setText(QString::number(shipData.m_bGPSLinkFlag[1]));
    if (ui.label_GPSLinkState->text().length() > 17)
    {
      ui.label_GPSLinkState->setText("Reconnection.");
    }
    else
    {
      ui.label_GPSLinkState->setText(ui.label_GPSLinkState->text() + QString::fromStdString("."));
    }
  }
}
