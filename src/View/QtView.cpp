#include "..\..\include\View\QtView.h"

jyQtView::jyQtView(jyQtControl * controller):jyViewBase(controller)
{
  m_Ui.setupUi(this);
  m_ptime = new QTimer(this);
  m_pParamDialog = new jyParamDialog(this->getControl()->getParamControl(), this);
  m_pOSGView = new jyOSGView(this->getControl()->getOSGControl());
  initWidget();
  connect(m_ptime, &QTimer::timeout, this, static_cast<void (QMainWindow::*)()>(&QMainWindow::update));
  connect(m_Ui.actionChangeView_LinkBoat, &QAction::triggered, this, &jyQtView::slotShowLinkBoatDialog);
  m_BoatConnect = connectUpdataBoatSignal(boost::bind(&jyQtView::updataView, this));
  m_ptime->start(40);
  //按下按钮后将Boatid赋值给BoatControl，并且启动线程开始连接
  connect(m_pParamDialog, &jyParamDialog::sigSendBoatID, this->getControl()->getOSGControl()->getBoatControl(), &jyBoatControl::slotGetUrl);
  connect(m_pParamDialog->getUI().pushButton_LinkStart, &QPushButton::clicked, this->getControl()->getOSGControl()->getBoatControl(),&jyBoatControl::slotLink);
  connect(m_Ui.pushButton_closeLink, &QPushButton::clicked, this->getControl()->getOSGControl()->getBoatControl(), &jyBoatControl::slotLinkClose);
  //绑定初始化结果显示的槽函数
  connect(this->getControl()->getOSGControl(), &jyOSGControl::sigInitFlag, this, &jyQtView::slotInitResultShow);
//  connect(m_pParamDialog->getUI().pushButton_LinkStart, &QPushButton::clicked, this->getControl()->getOSGControl()->getLinkThread(), &jyLinkThread::slotGetURL);
}

void jyQtView::slotShowLinkBoatDialog()
{
  m_pParamDialog->show();
}

jyQtView::~jyQtView()
{
 // delete m_ptime;
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

void jyQtView::paintEvent(QPaintEvent * event)
{
  m_pOSGView->ViewerFlush();
}

void jyQtView::slotInitResultShow(bool InitFlag)
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

void jyQtView::updataView()
{
  if (this->getBoatControl()->getGPSLinkFlag()[0] && this->getBoatControl()->getGPSLinkFlag()[1])
  {
    m_Ui.label_Distance->setText(QString::number(this->getBoatControl()->getLandAveDistance(), 'f', 6));
    QString _temCoor = QString::number(this->getBoatControl()->getCoordinate().x, 'f', 6) + "," + QString::number(this->getBoatControl()->getCoordinate().y, 'f', 6);
    m_Ui.label_Coordinate->setText(_temCoor);
    m_Ui.label_Rate->setText(QString::number(this->getBoatControl()->getRate(), 'f', 6));
    m_Ui.label_Distance1->setText(QString::number(this->getBoatControl()->getDistance1(), 'f', 6));
    m_Ui.label_Distance2->setText(QString::number(this->getBoatControl()->getDistance2(), 'f', 6));
    m_Ui.label_ID->setText(this->getBoatControl()->getID());
    m_Ui.label_Time->setText(this->getBoatControl()->getTime());
    m_Ui.label_Radio->setText(this->getBoatControl()->getLandRadio());
    m_Ui.label_GPS1->setText(QString::number(this->getBoatControl()->getGPSLinkFlag()[0]));
    m_Ui.label_GPS2->setText(QString::number(this->getBoatControl()->getGPSLinkFlag()[1]));
    m_Ui.label_LinkState->setText(QString("LinkSuccess"));
    m_Ui.label_MoveState->setText(this->getBoatControl()->getMoveState());
    m_Ui.label_HeadWarningX->setText(this->getBoatControl()->getHeadWarningX());
    m_Ui.label_HeadWarningY->setText(this->getBoatControl()->getHeadWarningY());
    m_Ui.label_SternWarningX->setText(this->getBoatControl()->getSternWarningX());
    m_Ui.label_SternWarningY->setText(this->getBoatControl()->getSternWarningY());
    changeWarningColor(m_Ui.label_HeadWarningX);
    changeWarningColor(m_Ui.label_HeadWarningY);
    changeWarningColor(m_Ui.label_SternWarningX);
    changeWarningColor(m_Ui.label_SternWarningY);
  }
  else
  {
    m_Ui.label_GPS1->setText(QString::number(this->getBoatControl()->getGPSLinkFlag()[0]));
    m_Ui.label_GPS2->setText(QString::number(this->getBoatControl()->getGPSLinkFlag()[1]));
    if(m_Ui.label_LinkState->text().length() > 17)
    {
      m_Ui.label_LinkState->setText(QString("Reconnection") + QString("."));
    }
    else
    {
      m_Ui.label_LinkState->setText(m_Ui.label_LinkState->text() + QString("."));
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

boost::signals2::connection jyQtView::connectUpdataBoatSignal(const slotType & type)
{
  return this->getBoatControl()->getUpdataSig().connect(type);
}

void jyQtView::changeWarningColor(QLabel * warninglabel)
{
  QPalette _pe;
  if (warninglabel->text() == "Safe")
  {
    _pe.setColor(QPalette::WindowText, Qt::green);
  }
  else
  {
    _pe.setColor(QPalette::WindowText, Qt::red);
  }
  warninglabel->setPalette(_pe);
}
