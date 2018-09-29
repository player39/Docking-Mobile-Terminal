#include <Control/SkyBoxCallBack.h>

void jyRotateCallback::operator()(osg::Node *node, osg::NodeVisitor* nv)
{
  osg::PositionAttitudeTransform *pat = dynamic_cast<osg::PositionAttitudeTransform*>(node);
  if (pat)
  {
    osg::Quat quat(osg::DegreesToRadians(_rotateZ), osg::Z_AXIS);
    pat->setAttitude(quat);
    _rotateZ += 0.030;
  }
 // qDebug() << _rotateZ;
  traverse(node, nv);
}