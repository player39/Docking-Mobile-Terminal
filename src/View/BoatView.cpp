#include "..\..\include\View\BoatView.h"

jyBoatView::jyBoatView(jyBoatControl* pController):jyViewBase(pController)
{
  m_pTransform = new osg::MatrixTransform();
  //第一次将船设置在中心位置0，0，0
  Matrix_Translate matrixTemTranslate = this->getControl()->getTranslate();
  m_pTransform->setMatrix(m_pTransform->getMatrix()*osg::Matrix::translate(matrixTemTranslate.x/*-getControl()->getCenterPoint().x*/, matrixTemTranslate.y/*-getControl()->getCenterPoint().y*/, matrixTemTranslate.z));
  //船节点
  m_pBoatGeode = new osg::Geode();
  m_pTransform->addChild(m_pBoatGeode.get());
  m_pBoatGeometry = new osg::Geometry();
  osg::ref_ptr<osg::Vec3Array> pBox = new osg::Vec3Array();
  point* pTemPoint = this->getControl()->getPoint();
  for (int i = 0; i < 6; ++i)
  {
    for (int k = 0; k < 4; ++k)
    {
      pBox->push_back(osg::Vec3(pTemPoint[this->getControl()->m_iSurface[i][k]].x, pTemPoint[this->getControl()->m_iSurface[i][k]].y, pTemPoint[this->getControl()->m_iSurface[i][k]].z));
    }
  }
  //_Box->push_back(osg::Vec3(2.0,0.0,0.0));
  //_Box->push_back(osg::Vec3(-2.0, 0.0, 0.0));
  m_pBoatGeometry->setVertexArray(pBox.get());
  //osg::ref_ptr<osg::Vec3Array> _n1 = new osg::Vec3Array();
  /*
  _n1->push_back(osg::Vec3(0.0, -1.0, 0.0));
  _n1->push_back(osg::Vec3(-1.0, 0.0, 0.0));
  _n1->push_back(osg::Vec3(0.0, 1.0, 0.0));
  _n1->push_back(osg::Vec3(1.0, 0.0, 0.0));
  _n1->push_back(osg::Vec3(0.0, 0.0, 1.0));
  _n1->push_back(osg::Vec3(0.0, 0.0, -1.0));
  m_pBoatGeometry->setNormalArray(_n1.get());
  m_pBoatGeometry->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);*/
  m_pBoatGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 24));
  osg::ref_ptr<osg::Vec4Array> pColor = new osg::Vec4Array();
  for (int i = 0; i < 24; ++i)
  {
    pColor->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
  }
  m_pBoatGeometry->setColorArray(pColor.get());
  m_pBoatGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
  osgUtil::SmoothingVisitor::smooth(*(m_pBoatGeometry.get()));

  osg::ref_ptr<osg::Material> test = new osg::Material;
  test->setAmbient(osg::Material::FRONT, osg::Vec4(1, 0, 0, 1));
  test->setSpecular(osg::Material::FRONT, osg::Vec4(1, 0, 0, 1));
  test->setShininess(osg::Material::FRONT, 90);
  test->setColorMode(osg::Material::DIFFUSE);
  m_pBoatGeode->getOrCreateStateSet()->setAttribute(test);
  m_pBoatGeode->addDrawable(m_pBoatGeometry.get());
}

jyBoatView::~jyBoatView()
{
}

void jyBoatView::initView()
{
}
//视图更新函数
void jyBoatView::updataView()
{
  jyBoatControl* pController = this->getControl();
  if (pController->getGPSLinkFlag()[0] || pController->getGPSLinkFlag()[1])
  {
    //更新船节点坐标，旋转姿态
    Matrix_Translate matrixShipTranslate = pController->getTranslate();
    m_pTransform->setMatrix(m_pTransform->getMatrix() * osg::Matrix::translate(matrixShipTranslate.x, matrixShipTranslate.y, matrixShipTranslate.z));
    osg::Matrix matrixTemTranslate = m_pTransform->getMatrix();

    m_pTransform->setMatrix(osg::Matrix::translate(0, 0, 0));
    m_pTransform->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(pController->getRotate()), 0, 0, 1));
    m_pTransform->setMatrix(m_pTransform->getMatrix() * matrixTemTranslate);
    //不清零就算断开连接也会不停重复上一次旋转
    pController->getLinkThread()->clearDataMapRotate();
  }
  pController->setRotate(0.0);
}

osg::ref_ptr<osg::MatrixTransform> jyBoatView::getRoot()
{
  return m_pTransform;
}
