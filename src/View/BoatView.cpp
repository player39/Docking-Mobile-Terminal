#include "..\..\include\View\BoatView.h"

jyBoatView::jyBoatView(jyBoatControl * controller):jyViewBase(controller)
{
  m_pTransform = new osg::MatrixTransform();
  //第一次将船设置在中心位置0，0，0
  m_pTransform->setMatrix(m_pTransform->getMatrix()*osg::Matrix::translate(getControl()->getTranslate().x/*-getControl()->getCenterPoint().x*/, getControl()->getTranslate().y/*-getControl()->getCenterPoint().y*/, getControl()->getTranslate().z));
  //船节点
  m_pBoatGeode = new osg::Geode();
  m_pTransform->addChild(m_pBoatGeode.get());
  m_pBoatGeometry = new osg::Geometry();
  osg::ref_ptr<osg::Vec3Array> _Box = new osg::Vec3Array();
  point *_temPoint = this->getControl()->getPoint();
  for (int i = 0; i < 6; ++i)
  {
    for (int k = 0; k < 4; ++k)
    {
      _Box->push_back(osg::Vec3(_temPoint[this->getControl()->m_iSurface[i][k]].x, _temPoint[this->getControl()->m_iSurface[i][k]].y, _temPoint[this->getControl()->m_iSurface[i][k]].z));
    }
  }
  //_Box->push_back(osg::Vec3(2.0,0.0,0.0));
  //_Box->push_back(osg::Vec3(-2.0, 0.0, 0.0));
  m_pBoatGeometry->setVertexArray(_Box.get());
  osg::ref_ptr<osg::Vec3Array> _n1 = new osg::Vec3Array();
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
  osg::ref_ptr<osg::Vec4Array> _color = new osg::Vec4Array();
  for (int i = 0; i < 24; ++i)
  {
    _color->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
  }
  m_pBoatGeometry->setColorArray(_color.get());
  m_pBoatGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
  osgUtil::SmoothingVisitor::smooth(*(m_pBoatGeometry.get()));
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
  if (getControl()->getGPSLinkFlag()[0] || getControl()->getGPSLinkFlag()[1])
  {
//    osg::Matrix test2 = osg::Matrix::translate(this->getControl()->getTranslate().x, this->getControl()->getTranslate().y, this->getControl()->getTranslate().z);
    //更新船节点坐标，旋转姿态
    m_pTransform->setMatrix(m_pTransform->getMatrix()*osg::Matrix::translate(this->getControl()->getTranslate().x, this->getControl()->getTranslate().y, this->getControl()->getTranslate().z));
    osg::Matrix _tem = m_pTransform->getMatrix();
//    osg::Matrix test1 = osg::Matrix::rotate(osg::DegreesToRadians(getControl()->getRotate()), 0, 0, 1);
    m_pTransform->setMatrix(osg::Matrix::translate(0, 0, 0));
    m_pTransform->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(getControl()->getRotate()), 0, 0, 1));
    m_pTransform->setMatrix(m_pTransform->getMatrix()*_tem);
    //不清零就算断开连接也会不停重复上一次旋转
    getControl()->getLinkThread()->ClearDataMapRotate();
  }
  getControl()->setRotate(0.0);
}

osg::ref_ptr<osg::MatrixTransform> jyBoatView::getRoot()
{
  return m_pTransform;
}
