#include <View/GLDrawable.h>

jyGLDrawable::jyGLDrawable()
{
  m_pTimer.setStartTick();
  m_pPoint = new osg::Vec3Array();
  qDebug() << m_dQ[0] << m_dQ[1] << m_dQ[2];
}

double* jyGLDrawable::jymath1(double _x, double _y)
{
  double group[2];
  group[0] = _x / sqrt(_x*_x + _y*_y);
  group[1] = _y / sqrt(_x*_x + _y*_y);
  return group;
}

double jyGLDrawable::jymath2(double _xgroup[2], double _ygroup[2])
{
  return _xgroup[0] * _ygroup[0] + _xgroup[1] * _ygroup[1];
}

void jyGLDrawable::update(osg::NodeVisitor * m_nodevisitor, osg::Drawable * m_drawable)
{
  flag = 0;
  osg::Geometry *geom = dynamic_cast<osg::Geometry*>(m_drawable);
  if (!geom)
    return;
  osg::Vec3Array *vertices = dynamic_cast<osg::Vec3Array *>(geom->getVertexArray());
  osg::Vec3Array *_normal = dynamic_cast<osg::Vec3Array *>(geom->getNormalArray());

  if (vertices)
  {
    if (flagpoint)
    {
      m_pPointIterator = m_pPoint->begin();
      m_pNormalIterator = _normal->begin();
    }

    
    for (osg::Vec3Array::iterator itr = vertices->begin(); itr != vertices->end() ; ++itr)
    {
      //qDebug() << "Point:" << flag++;
     // qDebug() << flag;
      if (!flagpoint)
      {
        m_pPoint->push_back(osg::Vec3(itr->x(),itr->y(),itr->z()));
      }

      flag++;
      
      if (flagpoint)
      {
        double x0 = itr->x();
        double y0 = itr->y();
        double z0 = itr->z();
        double _x = 0;
        double _y = 0;
        double _z = 0;
        double x = m_pPointIterator->x();
        double y = m_pPointIterator->y();
        double z = m_pPointIterator->z();
        //double Di[] = { x / sqrt(x*x + y*y),y / sqrt(x*x + y*y) };
       // double Di[] = { 1,0 };
        double Di[3][2] = { {1.0,0},{0,1},{1.0,1.0} };
        /*
        for (int i = 0; i < 3; i++)
        {
          for (int j = 0; j < 2; j++)
          {
            x -= cos(m_dThetas[j])*m_amplitudes[i][j] * sin(m_ks[i] * (x0*cos(m_dThetas[j]) + y0*sin(m_dThetas[j])) - m_omegas[i] * m_pTimer.time_s());
            z += m_amplitudes[i][j] * cos(m_ks[i] * (x0*cos(m_dThetas[j]) + y0*sin(m_dThetas[j])) - m_omegas[i] * m_pTimer.time_s());
            y -= sin(m_dThetas[j])*m_amplitudes[i][j] * sin(m_ks[i] * (x0*cos(m_dThetas[j]) + y0*sin(m_dThetas[j])) - m_omegas[i] * m_pTimer.time_s());
          }
        }*/

        for (int i = 0; i < 3; ++i)
        {
          _x = _x + m_dQ[i] * m_dA[i] * Di[i][0] * cos(sqrt(9.8 * 2 * pi / m_dL[i]) * (x*Di[i][0] + y*Di[i][1]) + m_dS[i] * 2 * pi / m_dL[i] * (m_dNowtime));
          _y = _y + m_dQ[i] * m_dA[i] * Di[i][1] * cos(sqrt(9.8 * 2 * pi / m_dL[i]) * (x*Di[i][0] + y*Di[i][1]) + m_dS[i] * 2 * pi / m_dL[i] * (m_dNowtime));
          _z = _z + m_dA[i] * sin(sqrt(9.8 * 2 * pi / m_dL[i]) * (x*Di[i][0] + y*Di[i][1]) + m_dS[i] * 2 * pi / m_dL[i] * (m_dNowtime));
          //qDebug() << "times" << m_dNowtime - m_dLasttime;
        }
        if (flagpoint)
        {
          if (x0 == 0 && y0 == 0)
          {
            itr->set(x0, y0, z0);
            qDebug() << flag;
          }
          else
          {
            x0 = m_pPointIterator->x() + _x;
            y0 = m_pPointIterator->y() + _y;
            z0 = m_pPointIterator->z() + _z;
            itr->set(x0, y0, z0);
          }
        }
        
        if (flagpoint)
        {
          double normal_x = 0;
          double normal_y = 0;
          double normal_z = 0;
          for (int i = 0; i < 3; ++i)
          {
            normal_x = normal_x + (((sqrt(9.8 * 2 * pi / m_dL[i]))*m_dA[i])*Di[i][0]*cos(sqrt(9.8 * 2 * pi / m_dL[i]) * (x * Di[i][0] + y*Di[i][1]) + m_dS[i] * 2 * pi / m_dL[i] * m_dNowtime));
            normal_y = normal_y + (((sqrt(9.8 * 2 * pi / m_dL[i]))*m_dA[i])*Di[i][1]*cos(sqrt(9.8 * 2 * pi / m_dL[i]) * (x * Di[i][0] + y*Di[i][1]) + m_dS[i] * 2 * pi / m_dL[i] * m_dNowtime));
            normal_z = normal_z + m_dQ[i] * m_dA[i] * sqrt(9.8 * 2 * pi / m_dL[i]) * sin(sqrt(9.8 * 2 * pi / m_dL[i]) * (x * Di[i][0] + y*Di[i][1]) + m_dS[i] * 2 * pi / m_dL[i] * m_dNowtime);
          }
          if (x == 0 && y == 0)
          {
            m_pNormalIterator->set(0, 0, 0);
           // qDebug() << flag;
          }
          else
          {
            //qDebug() << -normal_x << -normal_y << 1 - normal_z;
            m_pNormalIterator->set(-normal_x, -normal_y, 1 - normal_z);
          }
        }//*/
        if (flagpoint)
        {
          ++m_pPointIterator;
        }
        
        if (flagpoint)
        {
          ++m_pNormalIterator;
        }//*/
         //qDebug() << "Coordinate: " << x0 << y0 << z0;
        
      }
    }
    vertices->dirty();
    //qDebug() << "dirty";
    m_dLasttime = m_dNowtime;
    m_dNowtime += 0.1;
    flagpoint = true;
    flag = 0;
  }
}


