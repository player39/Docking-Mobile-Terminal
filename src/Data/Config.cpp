#include "Data/Config.h"

QSettings g_Settings("config.ini", QSettings::IniFormat);
std::string g_sURL = "http://127.0.0.1";
int g_iPort = 8000;
std::string g_sInitViewName = "initRender";
std::string g_sLinkViewName = "CTest";