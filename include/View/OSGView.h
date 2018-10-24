
#ifndef _OSGVIEW_H
#define _OSGVIEW_H

#include <View/ViewBase.h>
#include <Control/OSGControl.h>
#include <QtWidgets/QWidget>
#include <osgQt/GraphicsWindowQt>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/NodeCallback>
#include <osg/PositionAttitudeTransform>
#include <osg/Material>
#include <View/BoatView.h>
#include <View/LandView.h>
#include <View/SkyBoxView.h>
#include <View/SeaView.h>

class jyOSGView : public jyViewBase<jyOSGControl>
{
//  Q_OBJECT
public:
  jyOSGView(jyOSGControl* controller);
  ~jyOSGView();
  void setGraphics(osgQt::GraphicsWindowQt* mGraphics);
  osgQt::GraphicsWindowQt* getGraphics();
  void creatGraphicsWinQt(int x, int y, int w, int h, const std::string& name = "", bool windowDecoration = false);
  QWidget * getMainWidget();
  void ViewerFlush();
 // virtual void updataView();

private:
  osgQt::GraphicsWindowQt* m_pGraphics = NULL;
  osg::ref_ptr<osgViewer::Viewer> m_pViewer = NULL;
  osg::ref_ptr<osg::Node> m_pNode = NULL;
  osg::ref_ptr<osg::MatrixTransform> m_pRoot = NULL;
  jyBoatView* m_pBoatView = NULL;
  jyLandView* m_pLandView = NULL;
  jySkyBoxView* m_pSkyBoxView = NULL;
  jySeaView* m_pSeaView = NULL;
};

#endif // _OSGVIEW_H
