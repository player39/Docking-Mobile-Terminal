#include "..\..\include\View\QtView.h"

jyQtView::jyQtView(jyQtControl * controller):jyViewBase(controller)
{
  m_Ui.setupUi(this);
  m_ptime = new QTimer(this);
  m_pParamDialog = new jyParamDialog(this->getControl()->getParamControl(), this);
  m_pOSGView = new jyOSGView(this->getControl()->getOSGControl());
  m_pAutoLinkDialog = new jyShipListDialog(this->getControl()->getShipListControl(), this);

  initWidget();

  connect(m_ptime, &QTimer::timeout, this, static_cast<void (QMainWindow::*)()>(&QMainWindow::update));
  connect(m_Ui.actionChangeView_LinkBoat, &QAction::triggered, this, &jyQtView::slotShowLinkBoatDialog);
  m_BoatConnect = connectUpdataBoatSignal(boost::bind(&jyQtView::updataView, this));

  m_ptime->start(40);
  //���°�ť��Boatid��ֵ��BoatControl�����������߳̿�ʼ����
  connect(m_pParamDialog, &jyParamDialog::sigSendBoatID, this->getBoatControl(), &jyBoatControl::slotGetUrl);
  connect(m_pParamDialog->getUI().pushButton_LinkStart, &QPushButton::clicked, this->getBoatControl(), &jyBoatControl::slotLink);
  connect(m_Ui.pushButton_closeLink, &QPushButton::clicked, this->getBoatControl(), &jyBoatControl::slotLinkClose);
  //�󶨳�ʼ�������ʾ�Ĳۺ���
//  connect(this->getControl()->getOSGControl(), &jyOSGControl::sigInitFlag, this, &jyQtView::slotInitResultShow);
//connect(m_pParamDialog->getUI().pushButton_LinkStart, &QPushButton::clicked, this->getControl()->getOSGControl()->getLinkThread(), &jyLinkThread::slotGetURL);
  //���ڸ�����ֻ������� �����û�������ť��������
  connect(m_pAutoLinkDialog, &jyShipListDialog::sigShipID, this, &jyQtView::slotLinkShip);
  //�󶨾��ȱ���Ĳۺ���
  connect(m_Ui.pushButton_accuracy, &QPushButton::clicked, this, &jyQtView::slotChangeAccuracy);
}

void jyQtView::slotShowLinkBoatDialog()
{
  m_pParamDialog->show();
}

jyQtView::~jyQtView()
{
  m_pParamDialog->deleteLater();
}

jyBoatControl * jyQtView::getBoatControl()
{
  return this->getControl()->getOSGControl()->getBoatControl();
}

void jyQtView::initWidget()
{
  QVBoxLayout *_boxLayout = new QVBoxLayout();
  m_pOSGView->creatGraphicsWinQt(0, 0, 1600, 900, "mainWin", false);
 // _boxLayout->addWidget(m_pOSGView->getMainWidget());
 // this->m_Ui.centralwidget->setLayout(_boxLayout);
  m_Ui.boxlayout->addWidget(m_pOSGView->getMainWidget());
//m_FlashTime = new QTimer();
//m_FlashTime->start(40);
//  connect(m_FlashTime, &QTimer::timeout, this, static_cast<void (QMainWindow::*)()>(&QMainWindow::update));
}

void jyQtView::paintEvent(QPaintEvent* event)
{
  m_pOSGView->ViewerFlush();
}

void jyQtView::slotLinkShip(const QString& shipid)
{
  m_pParamDialog->EmitShipID(shipid);
  this->getBoatControl()->slotLink();
  m_pAutoLinkDialog->close();
  m_pAutoLinkDialog->deleteLater();
}

void jyQtView::slotChangeAccuracy()
{
  QString strAccuracy = m_Ui.lineEdit_accuracy->text();
  m_iAccuracy = strAccuracy.toInt();
}
/*
void jyQtView::slotInitResultShow(QString InitFlag)
{
  qDebug() << InitFlag;
  if (InitFlag)
  {
    QMessageBox::about(this, QString("Init"), QString("InitSuccess"));
  }
  else
  {
    QMessageBox::about(this, QString("Init"), QString("InitFailed"));
  }
}
*/
void jyQtView::updataView()
{
  //ֻҪ��һ��GPS�����Ͼ���ʾ����
  jyBoatControl* pBoatControl = this->getBoatControl();
  if (pBoatControl->getGPSLinkFlag()[0] || pBoatControl->getGPSLinkFlag()[1])
  {
    m_Ui.label_Distance->setText(QString::number(pBoatControl->getLandAveDistance(), 'f', m_iAccuracy));
    QString strTemCoor = QString::number(pBoatControl->getCoordinate().x, 'f', m_iAccuracy) + "," + QString::number(pBoatControl->getCoordinate().y, 'f', m_iAccuracy);
    m_Ui.label_Coordinate->setText(strTemCoor);
    m_Ui.label_Rate->setText(QString::number(pBoatControl->getRate(), 'f', m_iAccuracy));
    m_Ui.label_Distance1->setText(QString::number(pBoatControl->getDistance1(), 'f', m_iAccuracy));
    m_Ui.label_Distance2->setText(QString::number(pBoatControl->getDistance2(), 'f', m_iAccuracy));
    m_Ui.label_ID->setText(pBoatControl->getID());
    m_Ui.label_Time->setText(QString::fromLocal8Bit(DoubleToTimeData(pBoatControl->getTime().toDouble()).c_str()));
    m_Ui.label_Radio->setText(pBoatControl->getLandRadio());
    m_Ui.label_GPS1->setText(QString::number(pBoatControl->getGPSLinkFlag()[0]));
    m_Ui.label_GPS2->setText(QString::number(pBoatControl->getGPSLinkFlag()[1]));
    m_Ui.label_LinkState->setText("LinkSuccess");
    m_Ui.label_MoveState->setText(pBoatControl->getMoveState());
    m_Ui.label_HeadWarningX->setText(pBoatControl->getHeadWarningX());
    m_Ui.label_HeadWarningY->setText(pBoatControl->getHeadWarningY());
    m_Ui.label_SternWarningX->setText(pBoatControl->getSternWarningX());
    m_Ui.label_SternWarningY->setText(pBoatControl->getSternWarningY());
    changeWarningColor(m_Ui.label_HeadWarningX);
    changeWarningColor(m_Ui.label_HeadWarningY);
    changeWarningColor(m_Ui.label_SternWarningX);
    changeWarningColor(m_Ui.label_SternWarningY);
  }
  else
  {
    m_Ui.label_GPS1->setText(QString::number(pBoatControl->getGPSLinkFlag()[0]));
    m_Ui.label_GPS2->setText(QString::number(pBoatControl->getGPSLinkFlag()[1]));
    if(m_Ui.label_LinkState->text().length() > 17)
    {
      m_Ui.label_LinkState->setText("Reconnection.");
    }
    else
    {
      m_Ui.label_LinkState->setText(m_Ui.label_LinkState->text() + QString::fromStdString("."));
    }
    /*
    if (!this->getBoatControl()->getGPSLinkFlag()[0]&&this->getBoatControl()->getGPSLinkFlag()[1])
    {
      QMessageBox::critical(this, "LinkFailed", "GPS1 Link Error");
    }
    if (!this->getBoatControl()->getGPSLinkFlag()[1]&&this->getBoatControl()->getGPSLinkFlag()[0])
    {
      QMessageBox::critical(this, "LinkFailed", "GPS2 Link Error");
    }
    if (!this->getBoatControl()->getGPSLinkFlag()[1] && !this->getBoatControl()->getGPSLinkFlag()[0])
    {
      QMessageBox::critical(this, "LinkFailed", "GPS1 and GPS2 Link Error");
    }
    */
  }
}

boost::signals2::connection jyQtView::connectUpdataBoatSignal(const slotType& type)
{
  return this->getBoatControl()->getUpdataSig().connect(type);
}

void jyQtView::changeWarningColor(QLabel* warninglabel)
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

void jyQtView::checkInitResult()
{
  QString strInitResult = getControl()->getOSGControl()->getInitResult();
  QString strErrorMessage = getControl()->getOSGControl()->getErrorMessage();
  //��ʼ���ɹ�
  if (strInitResult == "000")
  {
    QMessageBox::about(this, "Init", "InitSuccess");
  }
  //��ʼ��ʧ��
  else
  {
    QMessageBox::about(this, "Init", strErrorMessage);
  }
}

void jyQtView::autoLinkShip()
{
  int iShipNum = getControl()->getOSGControl()->getShipList().size();
  const QStringList& strlShipList = getControl()->getOSGControl()->getShipList();
  //û�д�ֻ�����
  if (iShipNum == 0)
    return;
  //��һ�������Զ���������
  if (iShipNum == 1)
  {
    m_pParamDialog->EmitShipID(strlShipList[0]);
    this->getBoatControl()->slotLink();
    return;
  }
  //�ж��������������û�ѡ���������
  else
  {
    m_pAutoLinkDialog->addPushButton(this->getControl()->getOSGControl()->getShipList());
    m_pAutoLinkDialog->setModal(true);
    m_pAutoLinkDialog->show();
    return;
  }
}

jyShipListDialog* jyQtView::getShipListDialog()
{
  return m_pAutoLinkDialog;
}
