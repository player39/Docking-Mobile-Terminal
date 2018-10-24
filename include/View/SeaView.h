#ifndef _SEAVIEW_H
#define _SEAVIEW_H

#include <View/ViewBase.h>
#include <Control/SeaControl.h>
#include <osg/Shader>
#include <osg/Program>
#include <osg/Group>
#include <osg/Geode>
#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/Drawable>
#include <osg/Geometry>
#include <osgUtil/SmoothingVisitor>
#include <View/GLDrawable.h>
#include <osg/MatrixTransform>
#include <osg/StateSet>
#include <osg/PolygonMode>
#include <osgDB/ReadFile>
#include <osg/Texture2D>
#include <osg/Material>

class jySeaView :public jyViewBase<jySeaControl>
{

public:
  jySeaView(jySeaControl* controller);
  ~jySeaView();
  virtual void initView();
 // virtual void drawImplementation(osg::RenderInfo& RenderInfo, const osg::Drawable* drawable)const;
 // void loadShaders(osg::StateSet* ss);
  osg::ref_ptr<osg::MatrixTransform> getRoot();

private:
  osg::ref_ptr<osg::MatrixTransform> m_pRoot = NULL;
  osg::ref_ptr<osg::Geode> m_pSeaGeode = NULL;
  osg::ref_ptr<osg::Geometry> m_pSeaGeometry = NULL;

};

#endif
