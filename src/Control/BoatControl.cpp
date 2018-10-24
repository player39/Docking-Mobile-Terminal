#include "..\..\include\Control\BoatControl.h"

jyBoatControl::jyBoatControl()
{
  m_pBoatLink = new jyLinkThread();
  m_pLinkThread = new QThread();
  m_pointNowCoordinate.x = 0;
  m_pointNowCoordinate.y = 0;
  m_pointNowCoordinate.z = 0;
  /*��ʱ�Ĵ�ֻ��������*/
  float _tem[8][3] = { {50,-20,0}, {-50,-20,0}, {-50,-20,2}, {50,-20,2},
                       {50,20,0}, {-50,20,0}, {-50,20,2}, {50,20,2} };
  
  for (int i = 0; i < 8; ++i)
  {
    m_point[i].x = _tem[i][0];
    m_point[i].y = _tem[i][1];
    m_point[i].z = _tem[i][2];
  }
  int _iSurface[6][4] = { {3,2,1,0}, {2,6,5,1}, {6,7,4,5},
                 {7,3,0,4}, {7,6,2,3}, {4,0,1,5} };
  for (int i = 0; i < 6; ++i)
  {
    for (int k = 0; k < 4; ++k)
    {
      m_iSurface[i][k] = _iSurface[i][k];
    }
  }



}

jyBoatControl::~jyBoatControl()
{
}

jyLinkThread * jyBoatControl::getLinkThread()
{
  return m_pBoatLink;
}

point * jyBoatControl::getPoint()
{
  return m_point;
}

Matrix_Translate jyBoatControl::getTranslate()
{
  return m_matrixTranslate;
}

point jyBoatControl::getCoordinate()
{
  return m_pointNowCoordinate;
}

double jyBoatControl::getRotate()
{
  return m_dRotate;
}

void jyBoatControl::setRotate(double dRotate)
{
  m_dRotate = dRotate;
}

double jyBoatControl::getLandAveDistance()
{
  return m_dAveLandDistance;
}

double jyBoatControl::getDistance1()
{
  return m_dLandDistance1;
}

double jyBoatControl::getDistance2()
{
  return m_dLandDistance2;
}

bool * jyBoatControl::getGPSLinkFlag()
{
  return m_bGPSLinkFlag;
}

QString jyBoatControl::getLandRadio()
{
  return m_strLandRadio;
}

double jyBoatControl::getRate()
{
  return m_dRate;
}

QString jyBoatControl::getID()
{
  return m_strID;
}

QString jyBoatControl::getTime()
{
  return m_strTime;
}

QString jyBoatControl::getMoveState()
{
  return m_strMoveState;
}

QString jyBoatControl::getHeadWarningX()
{
  return m_strHeadWarningX;
}

QString jyBoatControl::getHeadWarningY()
{
  return m_strHeadWarningY;
}

QString jyBoatControl::getSternWarningX()
{
  return m_strSternWarningX;
}

QString jyBoatControl::getSternWarningY()
{
  return m_strSternWarningY;
}

void jyBoatControl::slotGetUrl(const QString& boatid)
{
  m_strBoatID = boatid;
}

void jyBoatControl::slotLink()
{
  /*�����ظ�����*/
  if(!m_pBoatLink)
    m_pBoatLink = new jyLinkThread();
  if (!m_pLinkThread)
    m_pLinkThread = new QThread();
  //����Ҫ���ӵĴ�ֻid
  m_pBoatLink->setBoatID(m_strBoatID);
  /*�����߳̽��մ�ֻ���ݣ�QThread ������Ĭ�ϵ���exec()�¼�ѭ������ȡ����д����Ϊ��ʹ��QLinkThread���ж���ĺ�������QThread������*/
  m_pBoatLink->moveToThread(m_pLinkThread);
  m_pLinkThread->start();
  /*�߳������ͽ���ʱ����Ӧ�Ĳۺ���*/
  connect(m_pLinkThread, &QThread::started, m_pBoatLink, &jyLinkThread::slotLinkStart);
  connect(m_pLinkThread, &QThread::finished, m_pBoatLink, &jyLinkThread::slotLinkFinished);
  //��QLinkThread�е�sigGetData�����յ����ݵ�ʱ�򷢳�����ź�֪ͨ��BoatControl����
  connect(m_pBoatLink, &jyLinkThread::sigGetData, this, &jyBoatControl::slotChangeBoatData);
}
//�Ͽ�����ʱ���еĲ������ͷŶ���Ͽ��ۺ������ӣ�ָ�븳ֵΪnull�����ڵ���deleteLater����ͷ�ʱ���Զ��ͷ��Ӷ���
void jyBoatControl::slotLinkClose()
{
  /*�ж��߳��Ƿ�������*/
  if (m_pLinkThread)
  {
    if (m_pLinkThread->isRunning())
    {
      //���¼�ѭ�����ͽ����ź�
      m_pLinkThread->quit();
      //�ȴ��߳�ִ����ϣ���run�з��أ������߳�ʱ������û������ʱ�� Ĭ��ֵ��Զ���ᳬʱ
      m_pLinkThread->wait();
      //�Ͽ��ۺ�������
      disconnect(m_pLinkThread, &QThread::started, m_pBoatLink, &jyLinkThread::slotLinkStart);
      disconnect(m_pLinkThread, &QThread::finished, m_pBoatLink, &jyLinkThread::slotLinkFinished);
      disconnect(m_pBoatLink, &jyLinkThread::sigGetData, this, &jyBoatControl::slotChangeBoatData);
      m_pLinkThread->deleteLater();
      m_pBoatLink->deleteLater();
      m_pLinkThread = NULL;
      m_pBoatLink = NULL;
    }
  }
}
/*���պʹ������ݵĺ�����������һ�����⣬���û�ѡ��Ͽ��ʹ�����ʱ������slotLinkclose��
���н�� m_pLinkThread��slotLinkFinished�󶨣������и����ڽ����֮���Ծ�ִ��һ��slotChangeBoatData��
��ʱ����m_pBoatLink�Ѿ��ͷű��null��˻��ָ���������ִ���������ʱ�Ƚ���һ���жϣ����m_pBoatLinkΪnull��ֱ��return��
����Ϊʲô����ִ��һ��slotChangeBoatData��ԭ�򻹲������disconnect����ֵ��Ϊtrue
*/
void jyBoatControl::slotChangeBoatData()
{
  //���̷߳���һ����Դ������
  QMutexLocker mutexLock(&m_Lock);
  //����������QMap

  //ԭ������
  if (!m_pBoatLink)
    return;
  //��ʼ��ȡ�ʹ�������
  /*
  for (QMap<QString, QString>::const_iterator i = m_pBoatLink->getDataMap().constBegin(); i != m_pBoatLink->getDataMap().constEnd(); ++i)
  {*/
  QMapIterator<QString, QString> itr(m_pBoatLink->getDataMap());
  while(itr.hasNext())
  {
    itr.next();
    //qDebug() << i.key() << ":" << i.value()<<"this is boat control";
    //����ֻ���꣬������ԭʼ����û�м�ȥ�������꣬����ͨ��ǰһ�μ�ȥ��ζ��������ݼ����ƽ������
    if (itr.key() == "Boat_Coordinate")
    {    
      QStringList strlTemCoor = itr.value().split(',');//�᲻�����value��û��ֵ�����
      //����ƽ������
      m_matrixTranslate.x = strlTemCoor[0].toDouble() - m_pointNowCoordinate.x ;
      m_matrixTranslate.y = strlTemCoor[1].toDouble() - m_pointNowCoordinate.y ;
      m_matrixTranslate.z = 0;
      //qDebug() << "ShipCoor:" << strlTemCoor;
      //qDebug() <<"translate:" << m_matrixTranslate.x << m_matrixTranslate.y;
      //�������µ�����
      m_pointNowCoordinate.x = strlTemCoor[0].toDouble();
      m_pointNowCoordinate.y = strlTemCoor[1].toDouble();
      m_pointNowCoordinate.z = 0;
      continue;
    }
    //��ֻ�ٶ�
    if (itr.key() == "Boat_Rate")
    {
      m_dRate = itr.value().toFloat();
      continue;
    }
    //GPS�������ݵ�ʱ��
    if (itr.key() == "Boat_Time")
    {
      m_strTime = itr.value();
      continue;
    }
    //��ֻ��ת�Ƕ�
    if (itr.key() == "Boat_Rotate")
    {
      m_dRotate = itr.value().toDouble();
      continue;
    }
    //��ֻid
    if (itr.key() == "Boat_ID")
    {
      m_strID = itr.value();
      continue;
    }
    //��ֻ���ĵ��밶������
    if (itr.key() == "Boat_AveLandDistance")
    {
      m_dAveLandDistance = itr.value().toDouble();
      continue;
    }
    //��ͷ�밶������
    if (itr.key() == "Boat_LandDistance1")
    {
      m_dLandDistance1 = itr.value().toDouble();
      continue;
    }
    //��β�밶������
    if (itr.key() == "Boat_LandDistance2")
    {
      m_dLandDistance2 = itr.value().toDouble();
      continue;
    }
    //��ֻ�밶���нǣ���Ҫ�޸�ʵ�����ǿ����ȷ�ϴ�����̬
    if (itr.key() == "Boat_LandRadio")
    {
      m_strLandRadio = itr.value();
      continue;
    }
    //��ֻ�ʹ�ͷGPS����״̬
    if (itr.key() == "Boat_ConnectionFlag1")
    {
      m_bGPSLinkFlag[0] = (itr.value() == "True") ? true : false;
      continue;
    }
    //��ֻ�ʹ�βGPS����״̬
    if (itr.key() == "Boat_ConnectionFlag2")
    {
      m_bGPSLinkFlag[1] = (itr.value() == "True") ? true : false;
      continue;
    }
    //���˶�״̬�����ټ�������
    if (itr.key() == "Boat_MoveState")
    {
      if (itr.value() == "0")
      {
        m_strMoveState = "Decelerate";
        continue;
      }
      if (itr.value() == "1")
      {
        m_strMoveState = "Uniform Speed";
        continue;
      }
      if (itr.value() == "2")
      {
        m_strMoveState = "Accelerate";
        continue;
      }
      qDebug() << "error";
    }
    //����flag ��ͷX���򱨾�
    if (itr.key() == "Boat_HeadWarningX")
    {
      m_strHeadWarningX = (itr.value() == "False") ? "Safe" : "Danger";
      continue;
    }
    //����flag ��ͷY���򱨾�
    if (itr.key() == "Boat_HeadWarningY")
    {
      m_strHeadWarningY = (itr.value() == "False") ? "Safe" : "Danger";
      continue;
    }
    //����flag ��βX���򱨾�
    if (itr.key() == "Boat_SternWarningX")
    {
      m_strSternWarningX = (itr.value() == "False") ? "Safe" : "Danger";
      continue;
    }
    //����flag ��βY���򱨾�
    if (itr.key() == "Boat_SternWarningY")
    {
      m_strSternWarningY = (itr.value() == "False") ? "Safe" : "Danger";
      continue;
    }
  }
  //�������ݸ�����ϵ��źţ�֪ͨ��ͼ�����������Ⱦ
   emitSigUpdata();
}
