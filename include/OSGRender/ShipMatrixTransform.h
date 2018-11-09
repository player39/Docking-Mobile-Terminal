
#ifndef _SHIPMATRIXTRANSFORM_H
#define _SHIPMATRIXTRANSFORM_H

#include "BaseClass/ShipDataControlView.h"
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osgUtil/SmoothingVisitor>
#include <osg/Material>

class jyShipMatrixTransform :public jyShipDataControlView
{
public:
  jyShipMatrixTransform();
  ~jyShipMatrixTransform();
  virtual void updateData();
  void shipOSGInit();
  osg::ref_ptr<osg::MatrixTransform> getRoot();

private:
  osg::ref_ptr<osg::Geode> m_pBoatGeode;
  osg::ref_ptr<osg::Node> m_pBoatNode;
  osg::ref_ptr<osg::Geometry> m_pBoatGeometry;
  osg::ref_ptr<osg::MatrixTransform> m_pTransform;
};

#endif // _SHIPMATRIXTRANSFORM_H