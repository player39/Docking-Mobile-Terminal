
#ifndef _BOATVIEW_H
#define _BOATVIEW_H

#include <Control/BoatControl.h>
#include <View/ViewBase.h>
#include <Model/BoatData.h>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osgUtil/SmoothingVisitor>
#include <osg/Material>

class jyBoatView :public jyViewBase<jyBoatControl>
{
public:
  jyBoatView(jyBoatControl* pController);
  ~jyBoatView();
  virtual void initView();
  virtual void updataView();
  osg::ref_ptr<osg::MatrixTransform> getRoot();

private:
  osg::ref_ptr<osg::Geode> m_pBoatGeode;
  osg::ref_ptr<osg::Node> m_pBoatNode;
  osg::ref_ptr<osg::Geometry> m_pBoatGeometry;
  osg::ref_ptr<osg::MatrixTransform> m_pTransform;
};

#endif // _BOATVIEW_H
