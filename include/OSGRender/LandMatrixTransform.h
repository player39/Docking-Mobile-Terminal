
#ifndef _LANDMATRIXTRANSFORM_H
#define _LANDMATRIXTRANSFORM_H

#include <Control/LandControl.h>
#include <BaseClass/ViewBase.h>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/Geometry>
#include <osgUtil/SmoothingVisitor>
#include <QtCore/QDebug>

class jyLandMatrixTransform :public jyViewBase<jyLandControl>
{
public:
  jyLandMatrixTransform();
  ~jyLandMatrixTransform();
  //  [11/8/2018 Administrator]
  virtual void setMvcControl(jyLandControlPtr controller);
  virtual void updateData();
  osg::ref_ptr<osg::MatrixTransform> getRoot();
  void landOSGInit();

private:
  osg::ref_ptr<osg::MatrixTransform> m_pRoot = NULL;
  osg::ref_ptr<osg::Geode> m_pGeode = NULL;
  osg::ref_ptr<osg::Geometry> m_pGeometry = NULL;

  boost::signals2::connection m_conUpdateData;

};

#endif // _LANDVIEW_H