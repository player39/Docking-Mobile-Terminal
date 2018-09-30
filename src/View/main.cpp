#include <View/QtView.h>
#include <Control/QtControl.h>
#include <View/OSGView.h>
#include <Control/BoatControl.h>
#include <Control/LandControl.h>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  jyQtControl *mainControl = new jyQtControl();
  jyQtView *mainWin = new jyQtView(mainControl);
  mainWin->show();
 // mainControl->getOSGControl()->initRender();
 // jyBoatControl *boat = new jyBoatControl();
 // jyLandControl *test = new jyLandControl();
  app.exec();
//  jyOSGView *test = new jyOSGView();

//  connect(reply,&QNetworkReply::finished,THIS,&)
}