#include <View/OSGView.h>

jyOSGView::jyOSGView(jyOSGControl *controller):jyViewBase(controller)
{
  m_pViewer = new osgViewer::Viewer();
}

jyOSGView::~jyOSGView()
{
}

void jyOSGView::setGraphics(osgQt::GraphicsWindowQt * mGraphics)
{
  m_pGraphics = mGraphics;
}

osgQt::GraphicsWindowQt * jyOSGView::getGraphics()
{
  return m_pGraphics;
}

void jyOSGView::creatGraphicsWinQt(int x, int y, int w, int h, const std::string & name, bool windowDecoration)
{
  osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
  traits->windowName = name;
  traits->windowDecoration = windowDecoration;
  traits->x = x;
  traits->y = y;
  traits->width = w;
  traits->height = h;
  traits->doubleBuffer = true;
  traits->samples = 8;
  this->setGraphics(new osgQt::GraphicsWindowQt(traits.get()));
}

QWidget * jyOSGView::getMainWidget()
{
  m_pNode = new osg::Node;
  m_pBoatView = new jyBoatView(this->getControl()->getBoatControl());
  m_pLandView = new jyLandView(this->getControl()->getLandControl());
  m_pSkyBoxView = new jySkyBoxView(this->getControl()->getSkyBoxControl());
  m_pSeaView = new jySeaView(this->getControl()->getSeaControl());
  //-π‚’’
  osg::ref_ptr<osg::LightSource> ls = new osg::LightSource();
  osg::ref_ptr<osg::Light>lt = new osg::Light;

  lt->setLightNum(0);
  lt->setPosition(osg::Vec4(-1.0, -1.0, -1.0, 0));
  lt->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
  lt->setDiffuse(osg::Vec4(1.0, 1.0, 1.0, 1.0));
  ls->setLight(lt);

  //--
  osgUtil::Optimizer _optimizer;
  _optimizer.optimize(m_pSkyBoxView->getRoot().get());
  osg::ref_ptr<osg::MatrixTransform> _testMatrix = new osg::MatrixTransform();
  _testMatrix->addChild(m_pBoatView->getRoot().get());
  _testMatrix->addChild(m_pLandView->getRoot().get());
  //_testMatrix->addChild(m_pSkyBoxView->getRoot().get());
  //_testMatrix->addChild(ls.get());
  //_testMatrix->addChild(m_pSeaView->getRoot().get());
  m_pNode = _testMatrix;
  const osgQt::GraphicsWindowQt::Traits *traits = this->getGraphics()->getTraits();
  osg::Camera *_temCamera = m_pViewer->getCamera();
  _temCamera->setGraphicsContext(m_pGraphics);
  _temCamera->setClearColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
  _temCamera->setViewport(0, 0, traits->width, traits->height);
  osg::Vec3d eye, center, up;

  _temCamera->setProjectionMatrixAsPerspective(100, 2, 100, 500);
  
  eye = osg::Vec3d(39429295.12326589-getControl()->getCenterPoint().x, 4386100.12379118-getControl()->getCenterPoint().y, 400);
  center = osg::Vec3d(39429295.12326589-getControl()->getCenterPoint().x, 4386100.12379118-getControl()->getCenterPoint().y, 0);
  up = osg::Vec3d(-1, 0, 0);//*/
  
  /*
  eye = osg::Vec3d(1244198.838750, 1300135, 8);
  center = osg::Vec3d(1244198.838750, 1300150, 8);
  up = osg::Vec3d(0, 0, 1);
  //*/
  
  /*eye = osg::Vec3d(200,200,250);
  center = osg::Vec3d(200,200,0);
  up = osg::Vec3d(0,1,0);
  //*/
  _temCamera->setViewMatrixAsLookAt(eye, center, up);
  m_pViewer->setSceneData(m_pNode);
  m_pViewer->addEventHandler(new osgViewer::StatsHandler);
//  m_pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
  m_pViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
  return m_pGraphics->getGLWidget();
}

void jyOSGView::ViewerFlush()
{
  if (m_pViewer)
  {
    m_pViewer->frame();
  }
}
