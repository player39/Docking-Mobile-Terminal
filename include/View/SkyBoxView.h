
#ifndef _SKYBOXVIEW_H
#define _SKYBOXVIEW_H

#include <View/ViewBase.h>
#include <Control/SkyBoxControl.h>
#include <osgDB/WriteFile>
#include <osgDB/ReadFile>
#include <osgUtil/SmoothingVisitor>
#include <osg/Texture2D>
#include <osgUtil/Optimizer>
#include <osg/Image>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Geometry>
#include <Control/SkyBoxCallBack.h>

class jySkyBoxView :public jyViewBase<jySkyBoxControl>
{
public:
  jySkyBoxView(jySkyBoxControl *controller);
  ~jySkyBoxView();
  virtual void initView();
  float toRadians(float angle);
  osg::ref_ptr<osg::PositionAttitudeTransform> getRoot();

private:
  osg::ref_ptr<osg::PositionAttitudeTransform> m_pRoot = NULL;
  osg::ref_ptr<osg::Geode> m_pSkyGeode = NULL;
  osg::ref_ptr<osg::Geometry> m_pSkyGeometry = NULL;


};

#endif //_SKYBOXVIEW_H
