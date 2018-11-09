
#include "Control/ObjectControl.h"

jyObjectControl::jyObjectControl(QObject* parent /* = Q_NULLPTR */)
{
  m_pOSGControl.reset(new jyOSGControl);
  m_pSelectShipControl.reset(new jySelectShipControl);
  m_pInitSystem = new jyInitSystem(this);
  connect(m_pInitSystem, &jyInitSystem::sigSendData, this, &jyObjectControl::slotInitSystemEnd);
  //connect(m_pInitSystem, &jyInitSystem::sigHttpLinkErrorMsg, this ,&jyObjectControl::slot)
}

jyObjectControl::~jyObjectControl()
{

}

void jyObjectControl::ThreadStart(const QString& shipid)
{
  if (m_pLinkObject && m_pThread)
    return;

  m_pThread = new QThread(this);
  m_pLinkObject = new jyLinkObject();
  m_pLinkObject->setShipID(shipid);
  m_pLinkObject->changeLoopFlag(true);
  m_pLinkObject->moveToThread(m_pThread);
  connect(m_pLinkObject, &jyLinkObject::sigShipData, this, &jyObjectControl::slotUpdateData);
  connect(m_pThread, &QThread::started, m_pLinkObject, &jyLinkObject::slotLinkStart);
  m_pThread->start();
}

void jyObjectControl::ThreadClose()
{
  if (!m_pThread || !m_pThread->isRunning())
    return;
  m_pLinkObject->changeLoopFlag(false);
  m_pThread->quit();
  m_pThread->wait();
  disconnect(m_pLinkObject, &jyLinkObject::sigShipData, this, &jyObjectControl::slotUpdateData);
  disconnect(m_pThread, &QThread::started, m_pLinkObject, &jyLinkObject::slotLinkStart);
  m_pThread->deleteLater();
  m_pLinkObject->deleteLater();
  m_pThread = Q_NULLPTR;
  m_pLinkObject = Q_NULLPTR;
}

void jyObjectControl::slotUpdateData(const stdMapString* shipdata)
{
  m_pOSGControl->getShipControl()->emitUpdateSig(shipdata);
}

void jyObjectControl::startInitSystem()
{
  m_pInitSystem->InitSystem();
}

jyOSGControlPtr jyObjectControl::getOSGControl()
{
  return m_pOSGControl;
}

jySelectShipControlPtr jyObjectControl::getSelectShipControl()
{
  return m_pSelectShipControl;
}

void jyObjectControl::slotInitSystemEnd(const stdMapString* initdata)
{
  m_pOSGControl->getLandControl()->initControlParam(initdata);
  m_pOSGControl->initControlParam(initdata);
  m_pSelectShipControl->initControlParam(initdata);
}
