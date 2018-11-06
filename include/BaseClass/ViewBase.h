
#ifndef _VIEWBASE_H
#define _VIEWBASE_H

#include <boost/signals2.hpp>
#include "BaseClass/ControlBase.h"

typedef boost::signals2::signal<void()>::slot_type slotType;

template<class T>
class jyViewBase
{
public:
  jyViewBase();
  ~jyViewBase();
  virtual void setMvcControl(std::shared_ptr<T> controller);
  std::shared_ptr<T> getMvcControl() const;
  bool isValid();

protected:
  virtual void beforeSetMvcControl();
  virtual void afterSetMvcControl();

private:
  std::weak_ptr<T> m_pMvcControl;

};

template<class T>
inline jyViewBase<T>::jyViewBase()
{
  m_pMvcControl.reset();
}

template<class T>
inline jyViewBase<T>::~jyViewBase()
{
}

template<class T>
inline void jyViewBase<T>::setMvcControl(std::shared_ptr<T> controller)
{
  beforeSetMvcControl();
  if (m_pMvcControl.lock() == controller)
    return;
  m_pMvcControl = controller;
  afterSetMvcControl();
}

template<class T>
inline std::shared_ptr<T> jyViewBase<T>::getMvcControl() const
{
  return m_pMvcControl.lock();
}

template<class T>
inline bool jyViewBase<T>::isValid()
{
  return !m_pMvcControl.expired();
}

template<class T>
inline void jyViewBase<T>::beforeSetMvcControl()
{
}

template<class T>
inline void jyViewBase<T>::afterSetMvcControl()
{
}

#endif // _VIEWBASE_H
