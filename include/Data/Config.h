
#ifndef _CONFIG_H
#define _CONFIG_H

#include <QtCore/QSettings>
#include <string>

extern QSettings g_Settings;
extern std::string g_sURL;
extern int g_iPort;
extern std::string g_sInitViewName;
extern std::string g_sLinkViewName;
typedef std::map<std::string, std::string> stdMapString;


#endif // _CONFIG_H