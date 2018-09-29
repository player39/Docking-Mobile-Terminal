#ifndef _SKYBOXCALLBACK_H
#define _SKYBOXCALLBACK_H

#include <osg/NodeCallback>
#include <osg/Node>
#include <osg/NodeVisitor>
#include <osg/PositionAttitudeTransform>
#include <QtCore/QDebug>
//天空盒回调函数，控制旋转
class jyRotateCallback :public osg::NodeCallback
{
public:
  jyRotateCallback() :_rotateZ(0.0) {};
  virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

protected:
  double _rotateZ;
};

#endif // !1
