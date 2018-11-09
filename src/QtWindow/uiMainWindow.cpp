
#include "QtWindow/uiMainWindow.h"

#define FLASHTICK 40

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
  m_pObjectControl.reset(new jyObjectControl);
  jyOSGControlPtr pOSGControl = m_pObjectControl->getOSGControl();
  ui.widget_DisplayData->setMvcControl(pOSGControl->getShipControl());
  ui.widget_ParamControl->setControlGroup(m_pObjectControl);

  m_pSelectShipWidget = new uiSelectShipWidget(this);
  m_pSelectShipWidget->setMvcControl(m_pObjectControl->getSelectShipControl());
  m_pSelectShipWidget->setControl(m_pObjectControl);
  //OSG初始化
  m_pFlashTimer = new QTimer(this);
  connect(m_pFlashTimer, &QTimer::timeout, this, static_cast<void (QMainWindow::*)()>(&QMainWindow::update));
  m_pOSGQtWidget = new jyOSGQtWidget();
  m_pOSGQtWidget->setMvcControl(pOSGControl);
  m_pOSGQtWidget->creatGraphicsWinQt(0, 0, 1600, 900, "mainWin", false);
  ui.gridLayout->addWidget(m_pOSGQtWidget->getMainWidget());
  m_pFlashTimer->start(FLASHTICK);
  //手动调用进行初始化
  m_pObjectControl->startInitSystem();
}

uiMainWindow::~uiMainWindow()
{
}

void uiMainWindow::paintEvent(QPaintEvent * event)
{
  m_pOSGQtWidget->ViewerFlush();
}
