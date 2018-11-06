
#ifndef _CONTROLBASE_H
#define _CONTROLBASE_H

#include "BaseClass/ViewBase.h"
#include <boost/signals2.hpp>

class jyControlBase
{
public:
  jyControlBase();
  ~jyControlBase();
  typedef boost::signals2::signal<void()> sig_UpdateData;
  sig_UpdateData m_sigUpdateData;
  boost::signals2::connection connectUpdateData(const sig_UpdateData::slot_type& slot);

private:

};

#endif