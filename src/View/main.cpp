#include <View/QtView.h>
#include <Control/QtControl.h>
#include <View/OSGView.h>
#include <Control/BoatControl.h>
#include <Control/LandControl.h>
#include <QtCore/QFile>
//--
#include <View/ShipListDialog.h>
#include <Control/ShipListControl.h>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  jyQtControl *mainControl = new jyQtControl();

  jyQtView *mainWin = new jyQtView(mainControl);
  mainWin->checkInitResult();
  mainWin->autoLinkShip();

  QFile qss("C://workspace//OSGBoat//resources//test.qss");
  qss.open(QFile::ReadOnly);
  qApp->setStyleSheet(qss.readAll());
  qss.close();

  mainWin->show();
  app.exec();
}