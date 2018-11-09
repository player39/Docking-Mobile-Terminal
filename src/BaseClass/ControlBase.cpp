
#include "BaseClass/ControlBase.h"

jyControlBase::jyControlBase()
{
}

jyControlBase::~jyControlBase()
{
}

boost::signals2::connection jyControlBase::connectUpdateData(const sig_UpdateData::slot_type& slotMethod)
{
  return m_sigUpdateData.connect(slotMethod);
}

void jyControlBase::initControlParam(const stdMapString * initdatagroup)
{
}

