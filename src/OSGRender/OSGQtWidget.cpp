#include "OSGRender\OSGQtWidget.h"

jyOSGQtWidget::jyOSGQtWidget()
{
  m_pViewer = new osgViewer::Viewer();
}

jyOSGQtWidget::~jyOSGQtWidget()
{}

void jyOSGQtWidget::setMvcControl(jyOSGControlPtr controller)
{
  m_conUpdateData.disconnect();
  jyViewBase::setMvcControl(controller);
  if (controller)
    m_conUpdateData = controller->connectUpdateData(boost::bind(&jyOSGQtWidget::updateData, this));
}

void jyOSGQtWidget::setGraphics(osgQt::GraphicsWindowQt * mGraphics)
{
  m_pGraphics = mGraphics;
}

osgQt::GraphicsWindowQt * jyOSGQtWidget::getGraphics()
{
  return m_pGraphics;
}

void jyOSGQtWidget::creatGraphicsWinQt(int x, int y, int w, int h, const std::string & name, bool windowDecoration)
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

QWidget * jyOSGQtWidget::getMainWidget()
{
  m_pNode = new osg::Node;
  m_pShipView = new jyShipMatrixTransform();
  m_pShipView->setMvcControl(this->getMvcControl()->getShipControl());
  m_pShipView->shipOSGInit();
  m_pLandView = new jyLandMatrixTransform();
  m_pLandView->setMvcControl(this->getMvcControl()->getLandControl());
  m_pLandView->landOSGInit();
  //-π‚’’
  osg::ref_ptr<osg::LightSource> pLightSource = new osg::LightSource();
  osg::ref_ptr<osg::Light> pLight = new osg::Light;

  pLight->setLightNum(0);
  pLight->setPosition(osg::Vec4(200.0, 200.0, 100.0, 0));
  pLight->setAmbient(osg::Vec4(0.3f, 0.3f, 0.3f, 1.0f));
  pLight->setDiffuse(osg::Vec4(0.7490196078431373f, 0.7490196078431373f, 0.7490196078431373f, 1.0));
  pLight->setSpecular(osg::Vec4(0.1f, 0.1f, 0.1f, 1.0f));
  pLight->setDirection(osg::Vec3(200.0, 200.0, -1.0));
  pLightSource->setLight(pLight);

  //--
  /*
  osgUtil::Optimizer optimizer;
  optimizer.optimize(m_pSkyBoxView->getRoot().get());*/
  osg::ref_ptr<osg::MatrixTransform> pTemRoot = new osg::MatrixTransform();
  /*π‚*/
  osg::ref_ptr<osg::StateSet> pRootState = pTemRoot->getOrCreateStateSet();
  pRootState->setMode(GL_LIGHTING, osg::StateAttribute::ON);
  pRootState->setMode(GL_LIGHT0, osg::StateAttribute::ON);

  pTemRoot->addChild(m_pShipView->getRoot().get());
  pTemRoot->addChild(m_pLandView->getRoot().get());
  //_testMatrix->addChild(m_pSkyBoxView->getRoot().get());
  //pTemRoot->addChild(pLightSource.get());
  //pTemRoot->addChild(m_pSeaView->getRoot().get());
  m_pNode = pTemRoot;
  const osgQt::GraphicsWindowQt::Traits* traits = this->getGraphics()->getTraits();
  osg::Camera* pCamera = m_pViewer->getCamera();
  pCamera->setGraphicsContext(m_pGraphics);
  pCamera->setClearColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
  pCamera->setViewport(0, 0, traits->width, traits->height);
  osg::Vec3d eye, center, up;

  pCamera->setProjectionMatrixAsPerspective(100, 2, 100, 500);

  jyOSGParam pointCameraParam = this->getMvcControl()->getOSGData();
  jyCameraParam cameraParam = pointCameraParam.cameraParam;
  /*eye = osg::Vec3d(39429295.12326589-getControl()->getCenterPoint().x, 4386100.12379118-getControl()->getCenterPoint().y, 400);
  center = osg::Vec3d(39429295.12326589-getControl()->getCenterPoint().x, 4386100.12379118-getControl()->getCenterPoint().y, 0);
  up = osg::Vec3d(-1, 0, 0);//*/

  eye = osg::Vec3d(cameraParam.eye.x, cameraParam.eye.y, cameraParam.eye.z);
  center = osg::Vec3d(cameraParam.center.x, cameraParam.center.y, 0);
  up = osg::Vec3d(-1, 0, 0);//*/
  /*
  eye = osg::Vec3d(1244198.838750, 1300135, 8);
  center = osg::Vec3d(1244198.838750, 1300150, 8);
  up = osg::Vec3d(0, 0, 1);
  //*/
  /*
  eye = osg::Vec3d(200,200,250);
  center = osg::Vec3d(200,200,0);
  up = osg::Vec3d(0,1,0);
  //*/
  pCamera->setViewMatrixAsLookAt(eye, center, up);
  m_pViewer->setSceneData(m_pNode);
  m_pViewer->addEventHandler(new osgViewer::StatsHandler);
  //m_pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
  m_pViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
  return m_pGraphics->getGLWidget();
}

void jyOSGQtWidget::ViewerFlush()
{
  if (m_pViewer)
    m_pViewer->frame();
}

void jyOSGQtWidget::updateData()
{
  osg::Vec3d eye, center, up;
  jyCameraParam CameraParam = this->getMvcControl()->getOSGData().cameraParam;
  eye = osg::Vec3d(CameraParam.eye.x, CameraParam.eye.y, CameraParam.eye.z);
  center = osg::Vec3d(CameraParam.eye.x, CameraParam.eye.y, 0);
  up = osg::Vec3d(-1, 0, 0);
  osg::Camera* pCamera = m_pViewer->getCamera();
  pCamera->setViewMatrixAsLookAt(eye, center, up);
}
