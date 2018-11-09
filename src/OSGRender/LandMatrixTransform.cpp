#include "OSGRender\LandMatrixTransform.h"

jyLandMatrixTransform::jyLandMatrixTransform()
{
}

jyLandMatrixTransform::~jyLandMatrixTransform()
{
  m_conUpdateData.disconnect();
}

void jyLandMatrixTransform::setMvcControl(jyLandControlPtr controller)
{
  m_conUpdateData.disconnect();
  jyViewBase::setMvcControl(controller);
  if (controller)
    controller->connectUpdateData(boost::bind(&jyLandMatrixTransform::updateData, this));
}

void jyLandMatrixTransform::updateData()
{
  const jyPoint& pointLandCoor = this->getMvcControl()->getCenterCoor();
  m_pRoot->setMatrix(m_pRoot->getMatrix() * osg::Matrix::translate(osg::Vec3d(pointLandCoor.x, pointLandCoor.y, pointLandCoor.z)));
}

osg::ref_ptr<osg::MatrixTransform> jyLandMatrixTransform::getRoot()
{
  return m_pRoot;
}

void jyLandMatrixTransform::landOSGInit()
{
  jyLandControlPtr pController = this->getMvcControl();
  jyPoint matrixTranslate = pController->getCenterCoor();

  m_pRoot = new osg::MatrixTransform();
  m_pRoot->setMatrix(m_pRoot->getMatrix() * osg::Matrix::translate(matrixTranslate.x, matrixTranslate.y, matrixTranslate.z));

  m_pGeode = new osg::Geode();
  m_pRoot->addChild(m_pGeode.get());

  m_pGeometry = new osg::Geometry();
  osg::ref_ptr<osg::Vec3Array> pVertex = new osg::Vec3Array();
  jyPoint* pTemVertex = this->getMvcControl()->getPoint();
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
