#include "..\..\include\View\LandView.h"

jyLandView::jyLandView(jyLandControl * controller):jyViewBase(controller)
{
  initView();
}

jyLandView::~jyLandView()
{
}

void jyLandView::initView()
{
  m_pRoot = new osg::MatrixTransform();
  m_pRoot->setMatrix(m_pRoot->getMatrix()*osg::Matrix::translate(getControl()->getTranslate().x-getControl()->getCenterPoint().x, getControl()->getTranslate().y-getControl()->getCenterPoint().y, getControl()->getTranslate().z));
  m_pGeode = new osg::Geode();
  m_pRoot->addChild(m_pGeode.get());
  m_pGeometry = new osg::Geometry();
  osg::ref_ptr<osg::Vec3Array> _Vertex = new osg::Vec3Array();
  point *_tem = this->getControl()->getPoint();
  for (int i = 0; i < 6; ++i)
  {
    for (int k = 0; k < 4; ++k)
    {
      _Vertex->push_back(osg::Vec3(_tem[this->getControl()->m_fSurface[i][k]].x, _tem[this->getControl()->m_fSurface[i][k]].y, _tem[this->getControl()->m_fSurface[i][k]].z));
    }
  }
  m_pGeometry->setVertexArray(_Vertex.get());
  /*
  osg::ref_ptr<osg::Vec3Array> _Normal = new osg::Vec3Array();
  _Normal->push_back(osg::Vec3(0.0, -1.0, 0.0));
  _Normal->push_back(osg::Vec3(-1.0, 0.0, 0.0));
  _Normal->push_back(osg::Vec3(0.0, 1.0, 0.0));
  _Normal->push_back(osg::Vec3(1.0, 0.0, 0.0));
  _Normal->push_back(osg::Vec3(0.0, 0.0, 1.0));
  _Normal->push_back(osg::Vec3(0.0, 0.0, -1.0));
  m_pGeometry->setNormalArray(_Normal.get());
  m_pGeometry->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);*/
  m_pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 24));
  osg::ref_ptr<osg::Vec4Array> _Color = new osg::Vec4Array();
  for (int i = 0; i < 24; ++i)
  {
    _Color->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
  }
  m_pGeometry->setColorArray(_Color.get());
  m_pGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
  osgUtil::SmoothingVisitor::smooth(*(m_pGeometry.get()));
  m_pGeode->addDrawable(m_pGeometry.get());
}

void jyLandView::updataView()
{
  qDebug() << "test==================";
}

osg::ref_ptr<osg::MatrixTransform> jyLandView::getRoot()
{
  return m_pRoot;
}

