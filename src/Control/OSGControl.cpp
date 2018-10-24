#include <Control/OSGControl.h>

jyOSGControl::jyOSGControl()
{
//  m_pLink = new jyLinkThread();
 // m_pLinkThread = new QThread();
  m_pBoatControl = new jyBoatControl();
  m_pLandControl = new jyLandControl();
  m_pSkyBoxControl = new jySkyBoxControl();
  m_pSeaControl = new jySeaControl();
  qDebug() << "URL:" << QString::fromStdString(this->getBackgroundUrl()+"initRender");
  //��ʼ�������������������
  m_pInitCoordinateRequest = new QNetworkRequest();
  m_pInitCoordinateRequest->setUrl(QUrl(QString::fromStdString(this->getBackgroundUrl())+"initRender"));
  m_pInitCoordinateRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  //���Զ���������д�ֻ�ڷ�Χ�ڿ����Զ����ӣ�������ֻ����ѡ���ѡ��
  //m_autoLink.setUrl(QUrl(QString::fromStdString(this->getBackgroundUrl() + "getShipID")));
  //m_autoLink.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  //�󶨽������ݺ���
  m_pAccessManager = new QNetworkAccessManager(this);
 // connect(m_AccessManager, &QNetworkAccessManager::finished, this, &jyOSGControl::slotFinished);
  //���г�ʼ��
//  this->initRender();
//  m_pOSGControl = new jyOSGControl();
}
/*
jyLinkThread * jyOSGControl::getLinkThread()
{
  return m_pLink;
}
*/
//��ʼ���ĺ�����ȡ��������Ͱ������꣬����QNetworkAccessManager�������������֣�����http����Ĺ���Ӧ����һ���첽�Ĺ��̣�������������ʱ���ͷ���������tcp���ӣ�֮��Ĺ�������http�ķ�Χ��
//��һ���첽�Ĺ��̣���ʱ����ʹ���źŲۣ����ݹٷ��ĵ�������QNetworkAccessManager����һ��pending network reply����ʱ����finished�źţ�����źźͰ󶨵Ĳۺ����޷�������
//��Ҫʹ���¼�ѭ�������̣߳��ȴ����������ز��ܷ����źţ�ͬʱ����������˹ر�tcp����ʧ�����ֱ�ӷ��ؽ������finish�źš�

void jyOSGControl::initRender()
{
  //����һ��������
  QString strSendData = " ";
  //��մ�����Ϣ
  m_strInitFlag = "";
  //����post���󣬷������ݴ�ŵ�m_pReply
  //�����¼�ѭ�����ӵ�����ǰ��������ʵ��ͬ������
  //connect(m_AccessManager, &QNetworkAccessManager::finished, this, &jyOSGControl::slotHttpSuccessQuit);
  connect(m_pAccessManager, &QNetworkAccessManager::finished, &m_HttpLoop, &QEventLoop::quit);
  m_pReply = m_pAccessManager->post(*m_pInitCoordinateRequest, strSendData.toLatin1());
  //��ʱ������,10�볬ʱ
  m_HttpTimer.setInterval(10000);
  m_HttpTimer.setSingleShot(true);
  //�󶨳�ʱ�����䳬ʱ��Ŀ������tcp����ͨ�˵����������������������û�д��䵽�ͻ��ˣ����������tcp�׶�����ʧ�ܻ�ֱ�ӷ���finished�ź�
  connect(&m_HttpTimer, &QTimer::timeout, &m_HttpLoop, &QEventLoop::quit);
  //�¼�ѭ���ȴ���������Ӧ
  m_HttpTimer.start();
  m_HttpLoop.exec();
  //QString test = "";
  //qDebug() << test.prepend(m_pReply->readAll());
  //�¼�ѭ����ֹ���������һ�����з��ط���finished�ź��˳��¼�ѭ������һ���Ƕ�ʱ����ʱ�˳��¼�ѭ��
  //�����ʱ���Լ����˵���������������¼�����
  if (m_HttpTimer.isActive())
  {
    m_HttpTimer.stop();
    //����
    if (m_pReply->error() != QNetworkReply::NoError)
    {
      qDebug() << "Error:" << m_pReply->errorString();
      m_strInitFlag = "001";
      m_strErrorMessage = "Error:" + m_pReply->errorString();
    }
    //δ����
    else
    {
      QByteArray byteData = m_pReply->readAll();
      QJsonDocument jsonDocument = QJsonDocument::fromJson(byteData);
      QJsonObject jsonObject = jsonDocument.object();
      for (QJsonObject::iterator i = jsonObject.begin(); i != jsonObject.end(); ++i)
      {
        //��ȡ��������
        if (i.key() == QString("LandCoordinate"))
        {
        //  qDebug() << i.value().toString();
          QString _temLandCoor = i.value().toString();
          //�������Ϊ�գ���ʼ��ʧ��
          if (_temLandCoor == "")
          {
            m_strInitFlag = "002";
            m_strErrorMessage += "Error: LandDataError Server return empty ";
            continue;
          }
          QStringList _temLandPoint = _temLandCoor.mid(1, _temLandCoor.length() - 2).split(',');
          double _temLandX = (_temLandPoint[0].toDouble() + _temLandPoint[2].toDouble()) / 2;
          double _temLandY = (_temLandPoint[1].toDouble() + _temLandPoint[3].toDouble()) / 2;
          m_pLandControl->setLandCoordinate(_temLandX, _temLandY);
       //   qDebug() << m_pLandControl->getTranslate().x<<m_pLandControl->getTranslate().y;
          //����������꣬˼·������������밶����ֱ��ֱ���ϲ��Ҿ��밶��ֱ����900��ͨ����������������������
          m_CameraCoor.x = _temLandX;
          m_CameraCoor.y = _temLandY + 900.0;
          m_CameraCoor.z = 400.0;
          //��initflag��Ϊ000 ��ʾ�ɹ�
          m_strInitFlag = "000";
          continue;
        }
        //��ȡServer�������еĴ�ֻ�������Զ�����
        if (i.key() == "ShipID")
        {
          QJsonArray _ShipID = i.value().toArray();
          for (QJsonArray::iterator k = _ShipID.begin(); k != _ShipID.end(); ++k)
          {
            m_strlShipList.append(k->toString());
          }
        }
        //�������keyֵ�����������ʼ��ʧ�ܣ�Ŀǰ��������һ���������� ȷ����web���Ժ󲻷������������ٰ�ע��ȥ��
        //m_strInitFlag = false;
      }
      //��ѭ���Ժ���init�ź�֪ͨqt����
     // slotEmitInitSig();
    }
  }
  //��ʱ��δ���˵����ʱ
  else
  {
    qDebug() << "time out";
    m_strInitFlag = "003";
    m_strErrorMessage = "Error: Time Out";
   // slotEmitInitSig();
  }
}

void jyOSGControl::slotEmitInitSig()
{
  emit sigInitFlag(m_strInitFlag);
}

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
point jyOSGControl::getCameraCoor()
{
  return m_CameraCoor;
}
QString jyOSGControl::getInitResult()
{
  return m_strInitFlag;
}
QString jyOSGControl::getErrorMessage()
{
  return m_strErrorMessage;
}
QStringList jyOSGControl::getShipList()
{
  return m_strlShipList;
}
/*
void jyOSGControl::slotLink()
{
  m_pLink->moveToThread(m_pLinkThread);
  connect(m_pLinkThread, &QThread::started, m_pLink, &jyLinkThread::slotLinkStart);
  m_pLinkThread->start();
}*/
