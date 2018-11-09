
#include "OSGRender/ShipMatrixTransform.h"

jyShipMatrixTransform::jyShipMatrixTransform()
{
}

jyShipMatrixTransform::~jyShipMatrixTransform()
{
}

//��ͼ���º���
void jyShipMatrixTransform::updateData()
{
  jyShipControlPtr pController = this->getMvcControl();
  const bool* pGPSLink = pController->getShipData().m_bGPSLinkFlag;
  if (pGPSLink[0] || pGPSLink[1])
  {
    //���´��ڵ����꣬��ת��̬
    jyPoint matrixShipTranslate = pController->getMatrixTranslate();
    m_pTransform->setMatrix(m_pTransform->getMatrix() * osg::Matrix::translate(matrixShipTranslate.x, matrixShipTranslate.y, matrixShipTranslate.z));

    osg::Matrix matrixTemTranslate = m_pTransform->getMatrix();
    m_pTransform->setMatrix(osg::Matrix::translate(0, 0, 0));
    m_pTransform->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(pController->getShipData().m_dRotate), 0, 0, 1));
    m_pTransform->setMatrix(m_pTransform->getMatrix() * matrixTemTranslate);
    //���������Ͽ�����Ҳ�᲻ͣ�ظ���һ����ת
    //pController->setRotate(0.0);
  }
}

void jyShipMatrixTransform::shipOSGInit()
{
  m_pTransform = new osg::MatrixTransform();
  jyShipControlPtr pController = this->getMvcControl();
  //��һ�ν�������������λ��0��0��0
  jyPoint matrixTemTranslate = pController->getMatrixTranslate();
  m_pTransform->setMatrix(m_pTransform->getMatrix()*osg::Matrix::translate(matrixTemTranslate.x, matrixTemTranslate.y, matrixTemTranslate.z));
  //���ڵ�
  m_pBoatGeode = new osg::Geode();
  m_pTransform->addChild(m_pBoatGeode.get());

  m_pBoatGeometry = new osg::Geometry();
  osg::ref_ptr<osg::Vec3Array> pBox = new osg::Vec3Array();
  jyPoint* pTemPoint = pController->m_point;
  for (int i = 0; i < 6; ++i)
  {
    for (int k = 0; k < 4; ++k)
    {
      pBox->push_back(osg::Vec3(pTemPoint[pController->m_iSurface[i][k]].x, pTemPoint[pController->m_iSurface[i][k]].y, pTemPoint[pController->m_iSurface[i][k]].z));
    }
  }
  m_pBoatGeometry->setVertexArray(pBox.get());
  m_pBoatGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 24));

  osg::ref_ptr<osg::Vec4Array> pColor = new osg::Vec4Array();
  for (int i = 0; i < 24; ++i)
  {
    pColor->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
  }
  m_pBoatGeometry->setColorArray(pColor.get());
  m_pBoatGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
  osgUtil::SmoothingVisitor::smooth(*(m_pBoatGeometry.get()));
  /*
  osg::ref_ptr<osg::Material> test = new osg::Material;
  test->setAmbient(osg::Material::FRONT, osg::Vec4(1, 0, 0, 1));
  test->setSpecular(osg::Material::FRONT, osg::Vec4(1, 0, 0, 1));
  test->setShininess(osg::Material::FRONT, 90);
  test->setColorMode(osg::Material::DIFFUSE);
  m_pBoatGeode->getOrCreateStateSet()->setAttribute(test);*/

  m_pBoatGeode->addDrawable(m_pBoatGeometry.get());
}

osg::ref_ptr<osg::MatrixTransform> jyShipMatrixTransform::getRoot()
{
  return m_pTransform;
}
