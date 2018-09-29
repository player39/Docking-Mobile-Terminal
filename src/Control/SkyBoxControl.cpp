#include "..\..\include\Control\SkyBoxControl.h"

jySkyBoxControl::jySkyBoxControl()
{
  int _ImageColumn = (int)(360 / m_fAngleSpan);
  int _ImageRow = (int)(m_fAngleV / m_fAngleSpan);
  //ÿ����һ�����Σ������������ι��ɣ���6���� 6���������꣬��12������
  float *_TexCoorLength = new float[_ImageColumn*_ImageRow * 6 * 2];
  m_fTexCoordinate = _TexCoorLength;
  float _TexColumnSize = 1.0f / _ImageColumn;
  float _TexRowSize = 1.0f / _ImageRow;
  int k = 0;
  for (int i = 0; i < _ImageRow; ++i)
  {
    for (int j = 0; j < _ImageColumn; ++j)
    {
      //��ʾ�ڼ��еڼ���
      float _Column = j*_TexColumnSize;
      float _Row = i*_TexRowSize;
      m_fTexCoordinate[k++] = _Column;
      m_fTexCoordinate[k++] = _Row;

      m_fTexCoordinate[k++] = _Column + _TexColumnSize;
      m_fTexCoordinate[k++] = _Row;

      m_fTexCoordinate[k++] = _Column;
      m_fTexCoordinate[k++] = _Row + _TexRowSize;

      m_fTexCoordinate[k++] = _Column;
      m_fTexCoordinate[k++] = _Row + _TexRowSize;

      m_fTexCoordinate[k++] = _Column + _TexColumnSize;
      m_fTexCoordinate[k++] = _Row;

      m_fTexCoordinate[k++] = _Column + _TexColumnSize;
      m_fTexCoordinate[k++] = _Row + _TexRowSize;
    }
  }
  //�������鳤��
  m_iTexCoorLength = _ImageColumn * _ImageRow * 6 * 2;
}

jySkyBoxControl::~jySkyBoxControl()
{
}

float jySkyBoxControl::getRadius()
{
  return m_fSkyBoxRadius;
}

float * jySkyBoxControl::getTexCoordinate()
{
  return m_fTexCoordinate;
}

int jySkyBoxControl::getTexCoorLength()
{
  return m_iTexCoorLength;
}
