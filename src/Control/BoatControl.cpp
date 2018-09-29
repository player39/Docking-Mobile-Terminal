#include "..\..\include\Control\BoatControl.h"

jyBoatControl::jyBoatControl()
{
  m_pBoatLink = new jyLinkThread();
  m_pLinkThread = new QThread();
  m_NowCoordinate.x = 0;
  m_NowCoordinate.y = 0;
  m_NowCoordinate.z = 0;
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
  return m_mTranslate;
}

point jyBoatControl::getCoordinate()
{
  return m_NowCoordinate;
}

double jyBoatControl::getRotate()
{
  return m_dRotate;
}

void jyBoatControl::setRotate(double rotate)
{
  m_dRotate = rotate;
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
  return m_sLandRadio;
}

double jyBoatControl::getRate()
{
  return m_dRate;
}

QString jyBoatControl::getID()
{
  return m_sID;
}

QString jyBoatControl::getTime()
{
  return m_stime;
}

QString jyBoatControl::getMoveState()
{
  return m_sMoveState;
}

QString jyBoatControl::getHeadWarningX()
{
  return m_sHeadWarningX;
}

QString jyBoatControl::getHeadWarningY()
{
  return m_sHeadWarningY;
}

QString jyBoatControl::getSternWarningX()
{
  return m_sSternWarningX;
}

QString jyBoatControl::getSternWarningY()
{
  return m_sSternWarningY;
}

void jyBoatControl::slotGetUrl(const QString boatid)
{
  m_sBoatID = boatid;
}

void jyBoatControl::slotLink()
{
  /*�����ظ�����*/
  if(!m_pBoatLink)
  {
    m_pBoatLink = new jyLinkThread();
  }
  
  if (!m_pLinkThread)
  {
    m_pLinkThread = new QThread();
  }
  //����Ҫ���ӵĴ�ֻid
  m_pBoatLink->setBoatID(m_sBoatID);
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
  QMutexLocker _lock(&m_Lock);
  //����������QMap
  QMap<QString, QString>::const_iterator i;
  //ԭ������
  if (!m_pBoatLink)
  {
    return;
  }
  //��ʼ��ȡ�ʹ�������
  for (i = m_pBoatLink->getDataMap().constBegin(); i != m_pBoatLink->getDataMap().constEnd(); ++i)
  {
    //qDebug() << i.key() << ":" << i.value()<<"this is boat control";
    //����ֻ���꣬������ԭʼ����û�м�ȥ�������꣬����ͨ��ǰһ�μ�ȥ��ζ��������ݼ����ƽ������
    if (i.key() == QString("Boat_Coordinate"))
    {    
      QStringList _tem = i.value().split(',');//�᲻�����value��û��ֵ�����
      //����ƽ������
      m_mTranslate.x = _tem[0].toDouble() - m_NowCoordinate.x ;
      m_mTranslate.y = _tem[1].toDouble() - m_NowCoordinate.y ;
      m_mTranslate.z = 0;
      qDebug() << m_mTranslate.x << m_mTranslate.y;
      //�������µ�����
      m_NowCoordinate.x = _tem[0].toDouble();
      m_NowCoordinate.y = _tem[1].toDouble();
      m_NowCoordinate.z = 0;
    }
    //��ֻ�ٶ�
    if (i.key() == QString("Boat_Rate"))
    {
      m_dRate = i.value().toFloat();
    }
    //GPS�������ݵ�ʱ��
    if (i.key() == QString("Boat_Time"))
    {
      m_stime = i.value();
    }
    //��ֻ��ת�Ƕ�
    if (i.key() == QString("Boat_Rotate"))
    {
      qDebug() << "RotateGET"<<i.value();
      m_dRotate = i.value().toDouble();
    }
    //��ֻid
    if (i.key() == QString("Boat_ID"))
    {
      m_sID = i.value();
    }
    //��ֻ���ĵ��밶������
    if (i.key() == QString("Boat_AveLandDistance"))
    {
      m_dAveLandDistance = i.value().toDouble();
    }
    //��ͷ�밶������
    if (i.key() == QString("Boat_LandDistance1"))
    {
      m_dLandDistance1 = i.value().toDouble();
    }
    //��β�밶������
    if (i.key() == QString("Boat_LandDistance2"))
    {
      m_dLandDistance2 = i.value().toDouble();
    }
    //��ֻ�밶���нǣ���Ҫ�޸�ʵ�����ǿ����ȷ�ϴ�����̬
    if (i.key() == QString("Boat_LandRadio"))
    {
      m_sLandRadio = i.value();
    }
    //��ֻ�ʹ�ͷGPS����״̬
    if (i.key() == QString("Boat_ConnectionFlag1"))
    {
      if (QString(i.value()) == "True")
      {
        m_bGPSLinkFlag[0] = true;
      }
      else
      {
        m_bGPSLinkFlag[0] = false;
      }
    }
    //��ֻ�ʹ�βGPS����״̬
    if (i.key() == QString("Boat_ConnectionFlag2"))
    {
      if (QString(i.value()) == "True")
      {
        m_bGPSLinkFlag[1] = true;
      }
      else
      {
        m_bGPSLinkFlag[1] = false;
      }
    }
    //���˶�״̬�����ټ�������
    if (i.key() == QString("Boat_MoveState"))
    {
      if (QString(i.value()) == "0")
      {
        m_sMoveState = "Decelerate";
      }
      if (QString(i.value()) == "1")
      {
        m_sMoveState = "Uniform Speed";
      }
      if (QString(i.value()) == "2")
      {
        m_sMoveState = "Accelerate";
      }
    }
    //����flag ��ͷX���򱨾�
    if (i.key() == QString("Boat_HeadWarningX"))
    {
      if (QString(i.value()) == "False")
      {
        m_sHeadWarningX = "Safe";
      }
      else
      {
        m_sHeadWarningX = "Danger";
      }
    }
    //����flag ��ͷY���򱨾�
    if (i.key() == QString("Boat_HeadWarningY"))
    {
      if (QString(i.value()) == "False")
      {
        m_sHeadWarningY = "Safe";
      }
      else
      {
        m_sHeadWarningY = "Danger";
      }
    }
    //����flag ��βX���򱨾�
    if (i.key() == QString("Boat_SternWarningX"))
    {
      if (QString(i.value()) == "False")
      {
        m_sSternWarningX = "Safe";
      }
      else
      {
        m_sSternWarningX = "Danger";
      }
    }
    //����flag ��βY���򱨾�
    if (i.key() == QString("Boat_SternWarningY"))
    {
      if (QString(i.value()) == "False")
      {
        m_sSternWarningY = "Safe";
      }
      else
      {
        m_sSternWarningY = "Danger";
      }
    }
  }
  //�������ݸ�����ϵ��źţ�֪ͨ��ͼ�����������Ⱦ
   emitSigUpdata();
  
}
