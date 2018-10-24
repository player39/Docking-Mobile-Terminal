
#ifndef _VIEWBASE_H
#define _VIEWBASE_H

#include <boost/signals2.hpp>
#include <control/ControlBase.h>

typedef boost::signals2::signal<void()>::slot_type slotType;

template<class Controller>
class jyViewBase
{

public:
  jyViewBase(Controller* controller);
  ~jyViewBase();
  void setControl(Controller* Control);
  Controller* getControl();
  void setUpdataConnect(boost::signals2::connection mconnect);
  boost::signals2::connection getUpdataConenct();
  virtual void initView();
  virtual void updataView();
  boost::signals2::connection connectUpdataSignal(const slotType& type);

private:
  Controller* m_pControl = NULL;
  boost::signals2::connection m_pUpdataConnect;
};

template<class Controller>
inline jyViewBase<Controller>::jyViewBase(Controller *controller)
{
  setControl(controller);
  setUpdataConnect(connectUpdataSignal(boost::bind(&jyViewBase::updataView,this)));
}

template<class Controller>
inline jyViewBase<Controller>::~jyViewBase()
{
  
}

template<class Controller>
inline void jyViewBase<Controller>::setControl(Controller* Control)
{
  m_pControl = Control;
}

template<class Controller>
inline Controller * jyViewBase<Controller>::getControl()
{
  return m_pControl;
}

template<class Controller>
inline void jyViewBase<Controller>::setUpdataConnect(boost::signals2::connection mconnect)
{
  m_pUpdataConnect = mconnect;
}

template<class Controller>
inline boost::signals2::connection jyViewBase<Controller>::getUpdataConenct()
{
  return boost::signals2::connection();
}

template<class Controller>
inline void jyViewBase<Controller>::initView()
{
}

template<class Controller>
inline void jyViewBase<Controller>::updataView()
{
}

template<class Controller>
inline boost::signals2::connection jyViewBase<Controller>::connectUpdataSignal(const slotType& type)
{
  return m_pControl->getUpdataSig().connect(type);
}

#endif // VIEWBASE_H