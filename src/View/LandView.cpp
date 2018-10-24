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
  jyLandControl* pController = this->getControl();
  Matrix_Translate matrixTranslate = pController->getTranslate();

  m_pRoot = new osg::MatrixTransform();
  m_pRoot->setMatrix(m_pRoot->getMatrix() * osg::Matrix::translate(matrixTranslate.x, matrixTranslate.y, matrixTranslate.z));

  m_pGeode = new osg::Geode();
  m_pRoot->addChild(m_pGeode.get());

  m_pGeometry = new osg::Geometry();
  osg::ref_ptr<osg::Vec3Array> pVertex = new osg::Vec3Array();
  point* pTemVertex = this->getControl()->getPoint();
  for (int i = 0; i < 6; ++i)
  {
    for (int k = 0; k < 4; ++k)
    {
      pVertex->push_back(osg::Vec3(pTemVertex[pController->m_fSurface[i][k]].x, pTemVertex[pController->m_fSurface[i][k]].y, pTemVertex[pController->m_fSurface[i][k]].z));
    }
  }
  m_pGeometry->setVertexArray(pVertex.get());
  m_pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 24));

  osg::ref_ptr<osg::Vec4Array> pColor = new osg::Vec4Array();
  for (int i = 0; i < 24; ++i)
  {
    pColor->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
  }
  m_pGeometry->setColorArray(pColor.get());
  m_pGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
  osgUtil::SmoothingVisitor::smooth(*(m_pGeometry.get()));

  m_pGeode->addDrawable(m_pGeometry.get());
}

void jyLandView::updataView()
{
}

osg::ref_ptr<osg::MatrixTransform> jyLandView::getRoot()
{
  return m_pRoot;
}

