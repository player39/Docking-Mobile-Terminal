#include <Control/OSGControl.h>

jyOSGControl::jyOSGControl()
{
//  m_pLink = new jyLinkThread();
 // m_pLinkThread = new QThread();
  m_pBoatControl = new jyBoatControl();
  m_pLandControl = new jyLandControl();
  m_pSkyBoxControl = new jySkyBoxControl();
  m_pSeaControl = new jySeaControl();
//  m_pOSGControl = new jyOSGControl();
}
/*
jyLinkThread * jyOSGControl::getLinkThread()
{
  return m_pLink;
}
*/
jyBoatControl * jyOSGControl::getBoatControl()
{
  return m_pBoatControl;
}
jyLandControl * jyOSGControl::getLandControl()
{
  return m_pLandControl;
}
jySkyBoxControl * jyOSGControl::getSkyBoxControl()
{
  return m_pSkyBoxControl;
}

jySeaControl * jyOSGControl::getSeaControl()
{
  return m_pSeaControl;
}
/*
void jyOSGControl::slotLink()
{
  m_pLink->moveToThread(m_pLinkThread);
  connect(m_pLinkThread, &QThread::started, m_pLink, &jyLinkThread::slotLinkStart);
  m_pLinkThread->start();
}*/
