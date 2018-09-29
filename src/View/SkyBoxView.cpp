#include "..\..\include\View\SkyBoxView.h"

jySkyBoxView::jySkyBoxView(jySkyBoxControl *controller):jyViewBase(controller)
{
  m_pRoot = new osg::PositionAttitudeTransform;
  m_pRoot->setUpdateCallback(new jyRotateCallback);
  m_pSkyGeode = new osg::Geode;
  m_pSkyGeometry = new osg::Geometry;
  initView();
}

jySkyBoxView::~jySkyBoxView()
{
}

void jySkyBoxView::initView()
{
  osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
  osg::ref_ptr<osg::Vec2Array> tcs = new osg::Vec2Array;
  int tc = 0;
  int ts = getControl()->getTexCoorLength();
  float *result = getControl()->getTexCoordinate();
  float tx1, tx2 = 0.0f;
  for (float vAngle = 90; vAngle > 0; vAngle = vAngle - 18)
  {
    for (float hAngle = 360; hAngle > 0; hAngle = hAngle - 18)
    {
      float ANGLE_SPAN = 18;
      float radius = getControl()->getRadius();
      double xozLength = radius*cos(toRadians(vAngle));
      //他这里写错了 z1求出来应该是y轴坐标
      float x1 = (float)(xozLength*cos(toRadians(hAngle)));
      float z1 = (float)(xozLength*sin(toRadians(hAngle)));
      float y1 = (float)(radius*sin(toRadians(vAngle)));

      xozLength = radius*cos(toRadians(vAngle - ANGLE_SPAN));
      float x2 = (float)(xozLength*cos(toRadians(hAngle)));
      float z2 = (float)(xozLength*sin(toRadians(hAngle)));
      float y2 = (float)(radius*sin(toRadians(vAngle - ANGLE_SPAN)));

      xozLength = radius*cos(toRadians(vAngle - ANGLE_SPAN));
      float x3 = (float)(xozLength*cos(toRadians(hAngle - ANGLE_SPAN)));
      float z3 = (float)(xozLength*sin(toRadians(hAngle - ANGLE_SPAN)));
      float y3 = (float)(radius*sin(toRadians(vAngle - ANGLE_SPAN)));

      xozLength = radius*cos(toRadians(vAngle));
      float x4 = (float)(xozLength*cos(toRadians(hAngle - ANGLE_SPAN)));
      float z4 = (float)(xozLength*sin(toRadians(hAngle - ANGLE_SPAN)));
      float y4 = (float)(radius*sin(toRadians(vAngle)));

      
      coords->push_back(osg::Vec3(x1, -z1, y1));
      coords->push_back(osg::Vec3(x4, -z4, y4));
      coords->push_back(osg::Vec3(x2, -z2, y2));
      //构建第一三角形


      //构建第二三角形

      coords->push_back(osg::Vec3(x2, -z2, y2));
      coords->push_back(osg::Vec3(x4, -z4, y4));
      coords->push_back(osg::Vec3(x3, -z3, y3));

      

      
      tx1 = result[tc++%ts];
      tx2 = result[tc++%ts];
      tcs->push_back(osg::Vec2(tx1, tx2));
      tx1 = result[tc++%ts];
      tx2 = result[tc++%ts];
      tcs->push_back(osg::Vec2(tx1, tx2));
      tx1 = result[tc++%ts];
      tx2 = result[tc++%ts];
      tcs->push_back(osg::Vec2(tx1, tx2));

      //第二三角形3个顶点的6个纹理坐标

      tx1 = result[tc++%ts];
      tx2 = result[tc++%ts];
      tcs->push_back(osg::Vec2(tx1, tx2));
      tx1 = result[tc++%ts];
      tx2 = result[tc++%ts];
      tcs->push_back(osg::Vec2(tx1, tx2));
      tx1 = result[tc++%ts];
      tx2 = result[tc++%ts];
      tcs->push_back(osg::Vec2(tx1, tx2));
    }
  }
  m_pSkyGeometry->setVertexArray(coords.get());
  m_pSkyGeometry->setTexCoordArray(0,tcs.get());
  m_pSkyGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, coords->size()));
  osgUtil::SmoothingVisitor::smooth(*(m_pSkyGeometry.get()));
  m_pSkyGeode->addDrawable(m_pSkyGeometry.get());
  osg::ref_ptr<osg::Texture2D> _SkyTex = new osg::Texture2D;
  osg::ref_ptr<osg::Image> _Skyimage = osgDB::readImageFile("C://Users//Administrator//Desktop//skyimage3.jpg");
  _SkyTex->setImage(_Skyimage);
  _SkyTex->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
  _SkyTex->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
  _SkyTex->setWrap(osg::Texture::WRAP_R, osg::Texture::REPEAT);
  _SkyTex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
  _SkyTex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
  m_pSkyGeode->getOrCreateStateSet()->setTextureAttributeAndModes(0, _SkyTex, 1);
  m_pRoot->addChild(m_pSkyGeode.get());
}

float jySkyBoxView::toRadians(float angle)
{
  return angle/180*osg::PI;
}

osg::ref_ptr<osg::PositionAttitudeTransform> jySkyBoxView::getRoot()
{
  return m_pRoot;
}
