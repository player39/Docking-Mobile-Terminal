
#include "QtWindow/uiMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  

  uiMainWindow* mainWin = new uiMainWindow();
  mainWin->show();
  
  app.exec();
}