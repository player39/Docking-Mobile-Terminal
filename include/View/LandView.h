
#ifndef _LANDVIEW_H
#define _LANDVIEW_H

#include <Control/LandControl.h>
#include <View/ViewBase.h>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/Geometry>
#include <osgUtil/SmoothingVisitor>
#include <QtCore/QDebug>

class jyLandView :public jyViewBase<jyLandControl>
{
public:
  jyLandView(jyLandControl *controller);
  ~jyLandView();
  virtual void initView();
  virtual void updataView();
  osg::ref_ptr<osg::MatrixTransform> getRoot();

private:
  osg::ref_ptr<osg::MatrixTransform> m_pRoot = NULL;
  osg::ref_ptr<osg::Geode> m_pGeode = NULL;
  osg::ref_ptr<osg::Geometry> m_pGeometry = NULL;

};

#endif // _LANDVIEW_H
