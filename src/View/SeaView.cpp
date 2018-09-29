#include "..\..\include\View\SeaView.h"

jySeaView::jySeaView(jySeaControl * controller):jyViewBase(controller)
{
  /*
  m_vertShader = new osg::Shader(osg::Shader::VERTEX);
  m_fragShader = new osg::Shader(osg::Shader::FRAGMENT);
  m_program = new osg::Program;
  */
  m_pRoot = new osg::MatrixTransform;
  m_pSeaGeode = new osg::Geode;
  m_pSeaGeometry = new osg::Geometry;
  initView();
}

jySeaView::~jySeaView()
{
}

void jySeaView::initView()
{
  m_pRoot->addChild(m_pSeaGeode);
 // m_pSeaGeode->addChild(m_pSeaGeometry);
  osg::ref_ptr<osg::Vec3Array> _temArray = new osg::Vec3Array;
  osg::ref_ptr<osg::DrawElementsUInt> _temIndexArray = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
  osg::ref_ptr<osg::Vec4Array> _temColor = new osg::Vec4Array;
  
  for (int i = 0; i < /*441*/ 20*20*2*3; ++i)
  {
   // _temArray->push_back(osg::Vec3(getControl()->getOceanPoint()[i].x, getControl()->getOceanPoint()[i].z, 10));
    _temArray->push_back(osg::Vec3(getControl()->getOceanPoint()[getControl()->getIndexArray()[i]].x, getControl()->getOceanPoint()[getControl()->getIndexArray()[i]].z, 10));
  }

  for (int i = 0; i < 2400; ++i)
  {
    _temIndexArray->push_back(getControl()->getIndexArray()[i]);
   // _temColor->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 0.1f));
  }

  osg::ref_ptr<osg::Vec2Array> _temTexArray = new osg::Vec2Array;
  for (int i = 0; i < 2400; ++i)
  {
    _temTexArray->push_back(osg::Vec2f(getControl()->getTexPoint()[i].x, getControl()->getTexPoint()[i].y));
  }

  m_pSeaGeometry->setTexCoordArray(0, _temTexArray);
  osg::ref_ptr<osg::Texture2D> _SeaTex = new osg::Texture2D;
  osg::ref_ptr<osg::Image> _SeaImage = osgDB::readImageFile("C://Users//Administrator//Desktop//water.JPG");
  _SeaTex->setImage(_SeaImage.get());
  
  _SeaTex->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
  _SeaTex->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
  //设置对边界的处理方式
  _SeaTex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
  _SeaTex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
  /*
  _temArray->push_back(osg::Vec3(0, 0, 0));

  _temArray->push_back(osg::Vec3(0, 1, 0));

  _temArray->push_back(osg::Vec3(1, 0, 0));

  _temIndexArray->push_back(0);
  _temIndexArray->push_back(1);
  _temIndexArray->push_back(2);
  _temColor->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
  _temColor->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
  _temColor->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
  */
  m_pSeaGeometry->setVertexArray(_temArray);
 // m_pSeaGeometry->setColorArray(_temColor);
 // m_pSeaGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
  //手动生成法线
  osg::ref_ptr<osg::Vec3Array> _normal = new osg::Vec3Array;
  for (int i = 0; i < 2400; ++i)
  {
    _normal->push_back(osg::Vec3(0, 0, 0));
  }
  m_pSeaGeometry->setNormalArray(_normal);
  m_pSeaGeometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
  //自动生成法线
 // osgUtil::SmoothingVisitor::smooth(*(m_pSeaGeometry.get()));
  m_pSeaGeometry->addPrimitiveSet(/*_temIndexArray*/new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0 ,2400));
//  m_pSeaGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 3));
  m_pSeaGeometry->setUpdateCallback(new jyGLDrawable);
  m_pSeaGeometry->setUseDisplayList(false);
  m_pSeaGeometry->setUseVertexBufferObjects(true);

  osg::ref_ptr<osg::StateSet> stateset = m_pSeaGeode->getOrCreateStateSet();
//  stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
//  stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
  stateset->setTextureAttributeAndModes(0, _SeaTex, 1);
  
  //设置网格模型
  osg::ref_ptr<osg::PolygonMode> polyMode = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
 // stateset->setAttribute(polyMode);
  m_pSeaGeode->addDrawable(m_pSeaGeometry.get());
//  m_pSeaGeode->getOrCreateStateSet()->setTextureAttributeAndModes(0, _SeaTex, 1);
 // loadShaders(m_pSeaGeode->getOrCreateStateSet());
}
osg::ref_ptr<osg::MatrixTransform> jySeaView::getRoot()
{
  return m_pRoot;
}
/*
void jySeaView::drawImplementation(osg::RenderInfo& RenderInfo,const osg::Drawable* drawable)const
{
  //glGenBuffersARB(1, this->getControl()->getOceanPoint());
}

void jySeaView::loadShaders(osg::StateSet * ss)
{
  m_vertShader->loadShaderSourceFromFile("");
  m_vertShader->loadShaderSourceFromFile("");
  m_program->addShader(m_vertShader);
  m_program->addShader(m_fragShader);
  ss->setAttributeAndModes(m_program, osg::StateAttribute::ON);
}

osg::ref_ptr<osg::Node> jySeaView::getRoot()
{
  return m_pRoot;
}
*/
