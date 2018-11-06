
#include "QtWindow/uiMainWindow.h"

uiMainWindow::uiMainWindow(QWidget* parent /*= Q_NULLPTR*/) :
  QMainWindow(parent)
{
  ui.setupUi(this);
  //读取或创建配置文件
  g_Settings.beginGroup("UrlParam");
  QString strURL = "URL";
  if (g_Settings.value(strURL).isNull())
    g_Settings.setValue(strURL, QString::fromStdString(g_sURL));
  g_sURL = g_Settings.value(strURL).toString().toStdString();

  QString strPort = "Port";
  if (g_Settings.value(strPort).isNull())
    g_Settings.setValue(strPort, g_iPort);
  g_iPort = g_Settings.value(strPort).toInt();

  QString strInitViewName = "InitViewName";
  if (g_Settings.value(strInitViewName).isNull())
    g_Settings.setValue(strInitViewName, QString::fromStdString(g_sInitViewName));
  g_sInitViewName = g_Settings.value(strInitViewName).toString().toStdString();

  QString strLinkViewName = "LinkViewName";
  if (g_Settings.value(strLinkViewName).isNull())
    g_Settings.setValue(strLinkViewName, QString::fromStdString(g_sLinkViewName));
  g_sLinkViewName = g_Settings.value(strLinkViewName).toString().toStdString();

  g_Settings.endGroup();
  //初始化
  m_pShipControl.reset(new jyShipControl);
  ui.widget_DisplayData->setMvcControl(m_pShipControl);
  ui.widget_ParamControl->setControlGroup(m_pShipControl);
}

uiMainWindow::~uiMainWindow()
{
}