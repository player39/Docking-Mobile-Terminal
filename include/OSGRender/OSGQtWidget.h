
#ifndef _OSGQTWIDGET_H
#define _OSGQTWIDGET_H

#include "Control/OSGControl.h"
#include "BaseClass/ViewBase.h"
#include "OSGRender/LandMatrixTransform.h"
#include "OSGRender/ShipMatrixTransform.h"
#include <QtWidgets/QWidget>
#include <osgQt/GraphicsWindowQt>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/NodeCallback>
#include <osg/PositionAttitudeTransform>
#include <osg/Material>

class jyOSGQtWidget : public jyViewBase<jyOSGControl>
{
public:
  jyOSGQtWidget();
  ~jyOSGQtWidget();
  //绑定MvcControl
  virtual void setMvcControl(jyOSGControlPtr controller);
  void setGraphics(osgQt::GraphicsWindowQt* mGraphics);
  osgQt::GraphicsWindowQt* getGraphics();
  void creatGraphicsWinQt(int x, int y, int w, int h, const std::string& name = "", bool windowDecoration = false);
  QWidget* getMainWidget();
  void ViewerFlush();
  //更改相机视角
  virtual void updateData();

private:
  boost::signals2::connection m_conUpdateData;
  osgQt::GraphicsWindowQt* m_pGraphics = NULL;
  osg::ref_ptr<osgViewer::Viewer> m_pViewer = NULL;
  osg::ref_ptr<osg::Node> m_pNode = NULL;
  osg::ref_ptr<osg::MatrixTransform> m_pRoot = NULL;
  jyShipMatrixTransform* m_pShipView = NULL;
  jyLandMatrixTransform* m_pLandView = NULL;
};

#endif // _OSGQTWIDGET_H