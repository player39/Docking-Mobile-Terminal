#ifndef _GLDRAWABLE_H
#define _GLDRAWABLE_H

#include <osg/Drawable>
#include <osg/Geometry>
#include <osg/Timer>
#include <QtCore/QDebug>
#include <math.h>
#include <osg/Vec3>

#define pi 3.1415926535


class jyGLDrawable :public osg::Drawable::UpdateCallback
{

public:
  jyGLDrawable();
  double* jymath1(double _x, double _y);
  double jymath2(double _xgroup[2], double _ygroup[2]);
  virtual void update(osg::NodeVisitor *m_nodeVisitor, osg::Drawable *m_drawable);

private:
  osg::Timer m_pTimer ;
  /*
  double m_dThetas[2] = { 0.38,1.42 };
  double m_omegas[3] = { 3.27,3.31,3.42 };
  double m_ks[3] = { 1.091,1.118,1.1935 };
  double m_amplitudes[3][2] = { 0.2,0.2,0.3,0.50,0.2,0.6 };*/
  //这里的参数成环了调整一下
  double m_dL[3] = { 3.4, 4.3, 6.2 };
  double m_dA[3] = { 2.5,2.1,1.5 };
  double m_dS[3] = { 1.06,1.08,1.09 };
  double m_dQ[3] = { 0.01,0.05,0.08 };//{1/(sqrt(2*pi*9.8/m_dL[0]))/m_dA[0], 1/(sqrt(2*pi/m_dL[1]*9.8))/m_dA[1], 1 / (sqrt(2 * pi / m_dL[2]*9.8))/m_dA[2] };
  int flag = 0;
  osg::ref_ptr<osg::Vec3Array> m_pPoint;
  osg::Vec3Array::iterator m_pPointIterator;
  osg::Vec3Array::iterator m_pNormalIterator;
  bool flagpoint = false;
  bool flagpoint2 = false;
  double m_dNowtime = 0;
  double m_dLasttime = 0;
};

#endif