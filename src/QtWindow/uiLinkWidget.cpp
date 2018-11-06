
#include "QtWindow/uiLinkWidget.h"

uiLinkWidget::uiLinkWidget(QWidget* parent /* = Q_NULLPTR */):
  QWidget(parent)
{
  ui.setupUi(this);
  connect(ui.pushButton_Link, &QPushButton::clicked, this, &uiLinkWidget::slotThreadStart);
  connect(ui.pushButton_Stop, &QPushButton::clicked, this, &uiLinkWidget::slotThreadClose);
}

uiLinkWidget::~uiLinkWidget()
{
}

void uiLinkWidget::setControl(jyShipControlPtr controller)
{
  m_pControl = controller;
}

void uiLinkWidget::slotThreadStart()
{
  if (m_pLinkObject&&m_pThread)
    return;

  m_pThread = new QThread(this);
  m_pLinkObject = new jyLinkObject();

  m_pLinkObject->setShipID(ui.lineEdit_ShipID->text());
  m_pLinkObject->changeLoopFlag(true);
  m_pLinkObject->moveToThread(m_pThread);
  connect(m_pLinkObject, &jyLinkObject::sigShipData, this, &uiLinkWidget::slotUpdateData);
  connect(m_pThread, &QThread::started, m_pLinkObject, &jyLinkObject::slotLinkStart);
  m_pThread->start();
}

void uiLinkWidget::slotThreadClose()
{
  if (!m_pThread||!m_pThread->isRunning())
    return;
  m_pLinkObject->changeLoopFlag(false);
  m_pThread->quit();
  m_pThread->wait();
  disconnect(m_pLinkObject, &jyLinkObject::sigShipData, this, &uiLinkWidget::slotUpdateData);
  disconnect(m_pThread, &QThread::started, m_pLinkObject, &jyLinkObject::slotLinkStart);
  m_pThread->deleteLater();
  m_pLinkObject->deleteLater();
  m_pThread = Q_NULLPTR;
  m_pLinkObject = Q_NULLPTR;
}

void uiLinkWidget::slotUpdateData(const stdMapString* shipdata)
{
  m_pControl.lock()->emitUpdateSig(shipdata);
}

