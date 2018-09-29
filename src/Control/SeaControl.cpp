#include "..\..\include\Control\SeaControl.h"

jySeaControl::jySeaControl()
{
  double _texColumn =1.0f/20.0f ;
  double _texRow = 1.0f/20.0f;
 // m_pOceanPoint[0].x = 0.0f;
 // m_pOceanPoint[0].z = 0.0f;
  int k = 0;
  //生成80X80方格顶点坐标
  for (int i = 0; i < 21; ++i)
  {
    for (int j = 0; j < 21; ++j)
    {
      /*
      m_pOceanPoint[k].x = m_pOceanPoint[i].x + i*20;
      m_pOceanPoint[k].z = m_pOceanPoint[j].z + 20.0f;
      ++k;
      */
      m_pOceanPoint[k].x = i * 20 ;
      m_pOceanPoint[k].z = j * 20;
      ++k;
    }
  }
  //生成方格索引数组
  int num = 0;
  /*
  for (int i = 0; i < 20; ++i)
  {
    for (int j = 0; j < 20; ++j)
    {
      m_iOceanPointIndex[num] = j + i * 21;
      ++num;
      m_iOceanPointIndex[num] = j + i * 21 + 1;
      ++num;
      m_iOceanPointIndex[num] = (i + 1) * 21 + j + 1;
      ++num;
    }
    for (int k = 0; k < 20; ++k)
    {
      m_iOceanPointIndex[num] = (i + 1) * 21 + k + 1;
      ++num;
      m_iOceanPointIndex[num] = k + i * 21;
      ++num;
      m_iOceanPointIndex[num] = (i + 1) * 21 + k;
      ++num;
    }
  }//*/

  /*
  for (int i = 0; i < 20; ++i)
  {
    for (int j = 0; j < 20; ++j)
    {
      m_iOceanPointIndex[num] = j + i * 21;
      ++num;
      m_iOceanPointIndex[num] = (i + 1) * 21 + j + 1;
      ++num;
      m_iOceanPointIndex[num] = j + i * 21 + 1;
      ++num;
      m_iOceanPointIndex[num] = j + i * 21;
      ++num;
      m_iOceanPointIndex[num] = (i + 1) * 21 + j;
      ++num;
      m_iOceanPointIndex[num] = (i + 1) * 21 + j + 1;
      ++num;
    }
  }//*/

  for (int i = 0; i < 20; ++i)
  {
    for (int j = 0; j < 20; ++j)
    {
      m_iOceanPointIndex[num] = j + i * 21;
      ++num;
      m_iOceanPointIndex[num] = (i + 1) * 21 + j;
      ++num;
      m_iOceanPointIndex[num] = j + i * 21 + 1;
      ++num;
      m_iOceanPointIndex[num] = (i + 1) * 21 + j + 1;
      ++num;
      m_iOceanPointIndex[num] = j + i * 21 + 1;
      ++num;
      m_iOceanPointIndex[num] = (i + 1) * 21 + j;
      ++num;
    }
  }

  //生成纹理坐标
  int texnum = 0;
  for (int column = 0; column < 20; ++column)
  {
    for (int row = 0; row < 20; ++row)
    {
      m_iOceanTexPoint[texnum].x = column * _texRow;
      m_iOceanTexPoint[texnum].y = row * _texColumn;
      ++texnum;
      m_iOceanTexPoint[texnum].x = column * _texRow + _texColumn;
      m_iOceanTexPoint[texnum].y = row * _texColumn ;
      ++texnum;
      m_iOceanTexPoint[texnum].x = column * _texRow ;
      m_iOceanTexPoint[texnum].y = row * _texColumn + _texRow;
      ++texnum;

      m_iOceanTexPoint[texnum].x = column * _texRow + _texColumn;
      m_iOceanTexPoint[texnum].y = row * _texColumn + _texColumn;
      ++texnum;
      m_iOceanTexPoint[texnum].x = column * _texRow ;
      m_iOceanTexPoint[texnum].y = row * _texColumn + _texColumn;
      ++texnum;
      m_iOceanTexPoint[texnum].x = column * _texRow + _texColumn;
      m_iOceanTexPoint[texnum].y = row * _texColumn ;
      ++texnum;
    }
  }

}

double * jySeaControl::getThetas()
{
  return m_dThetas;
}


double *jySeaControl::getOmegas()
{
  return m_omegas;
}

double *jySeaControl::getKs()
{
  return m_ks;
}

TexPoint * jySeaControl::getTexPoint()
{
  return m_iOceanTexPoint;
}

int* jySeaControl::getIndexArray()
{
  return m_iOceanPointIndex;
}

jySeaControl::~jySeaControl()
{
}

OceanXZpoint* jySeaControl::getOceanPoint()
{
  return m_pOceanPoint;
}