
#include "Control/ShipControl.h"

jyShipControl::jyShipControl()
{
  m_pointLastCoordinate = jyPoint(0.0f, 0.0f, 0.0f);
  /*暂时的船只顶点数据*/
  float _tem[8][3] = { { 50,-20,0 },{ -50,-20,0 },{ -50,-20,2 },{ 50,-20,2 },
  { 50,20,0 },{ -50,20,0 },{ -50,20,2 },{ 50,20,2 } };

  for (int i = 0; i < 8; ++i)
  {
  m_point[i].x = _tem[i][0];
  m_point[i].y = _tem[i][1];
  m_point[i].z = _tem[i][2];
  }
  int _iSurface[6][4] = { { 3,2,1,0 },{ 2,6,5,1 },{ 6,7,4,5 },
  { 7,3,0,4 },{ 7,6,2,3 },{ 4,0,1,5 } };
  for (int i = 0; i < 6; ++i)
  {
  for (int k = 0; k < 4; ++k)
  {
  m_iSurface[i][k] = _iSurface[i][k];
  }
  }
}

jyShipControl::~jyShipControl()
{
}
/*
const jyShipData& jyShipControl::getShipData()
{
  return m_shipData;
}

void jyShipControl::setShipData(const stdMapString* shipdata)
{
  
}
*/
void jyShipControl::emitUpdateSig(const stdMapString* shipdata)
{
  if(m_pShipData!=shipdata)
    m_pShipData = shipdata;
  handleShipData();
  m_sigUpdateData();
}

void jyShipControl::setLinkState(const QString & linkstate)
{
  m_sBackLinkState = linkstate.toStdString();
  m_sigUpdateData();
}

std::string jyShipControl::getLinkState()
{
  return m_sBackLinkState;
}
const jyShipData & jyShipControl::getShipData()
{
  return m_shipData;
}
//感觉需要改
void jyShipControl::handleShipData()
{
  for (stdMapString::const_iterator itr = m_pShipData->cbegin() ; itr != m_pShipData->cend(); ++itr)
  {
    if (itr->first == "Boat_Coordinate")
    {
      QStringList strlTemCoor = QString::fromStdString(itr->second).split(',');//会不会存在value中没有值的情况
      jyPoint& pointNowCoor = m_shipData.m_pointNowCoordinate;
      pointNowCoor.x = strlTemCoor[0].toDouble();
      pointNowCoor.y = strlTemCoor[1].toDouble();
      pointNowCoor.z = 0;
      m_matrixTranslate = jyPoint(pointNowCoor.x - m_pointLastCoordinate.x, pointNowCoor.y - m_pointLastCoordinate.y, 0);
      m_pointLastCoordinate = jyPoint(pointNowCoor.x, pointNowCoor.y, 0);
      continue;
    }
    //船只速度
    if (itr->first == "Boat_Rate")
    {
      m_shipData.m_dRate = QString::fromStdString(itr->second).toFloat();
      continue;
    }
    //GPS发送数据的时间
    if (itr->first == "Boat_Time")
    {
      m_shipData.m_strTime = QString::fromStdString(itr->second);
      continue;
    }
    //船只旋转角度
    if (itr->first == "Boat_Rotate")
    {
      m_shipData.m_dRotate = QString::fromStdString(itr->second).toDouble();
      continue;
    }
    //船只id
    if (itr->first == "Boat_ID")
    {
      m_shipData.m_strID = QString::fromStdString(itr->second);
      continue;
    }
    //船只中心点离岸基距离
    if (itr->first == "Boat_AveLandDistance")
    {
      m_shipData.m_dAveLandDistance = QString::fromStdString(itr->second).toDouble();
      continue;
    }
    //船头离岸基距离
    if (itr->first == "Boat_LandDistance1")
    {
      m_shipData.m_dLandDistance1 = QString::fromStdString(itr->second).toDouble();
      continue;
    }
    //船尾离岸基距离
    if (itr->first == "Boat_LandDistance2")
    {
      m_shipData.m_dLandDistance2 = QString::fromStdString(itr->second).toDouble();
      continue;
    }
    //船只与岸基夹角，需要修改实际上是靠这个确认船体姿态
    if (itr->first == "Boat_LandRadio")
    {
      m_shipData.m_strLandRadio = QString::fromStdString(itr->second).toDouble();
      continue;
    }
    //船只和船头GPS连接状态
    if (itr->first == "Boat_ConnectionFlag1")
    {
      m_shipData.m_bGPSLinkFlag[0] = (itr->second == "True") ? true : false;
      continue;
    }
    //船只和船尾GPS连接状态
    if (itr->first == "Boat_ConnectionFlag2")
    {
      m_shipData.m_bGPSLinkFlag[1] = (itr->second == "True") ? true : false;
      continue;
    }
    //船运动状态，加速减速匀速
    if (itr->first == "Boat_MoveState")
    {
      if (itr->second == "0")
      {
        m_shipData.m_strMoveState = "Decelerate";
        continue;
      }
      if (itr->second == "1")
      {
        m_shipData.m_strMoveState = "Uniform Speed";
        continue;
      }
      if (itr->second == "2")
      {
        m_shipData.m_strMoveState = "Accelerate";
        continue;
      }
    }
    //报警flag 船头X方向报警
    if (itr->first == "Boat_HeadWarningX")
    {
      m_shipData.m_strHeadWarningX = (itr->second == "False") ? "Safe" : "Danger";
      continue;
    }
    //报警flag 船头Y方向报警
    if (itr->first == "Boat_HeadWarningY")
    {
      m_shipData.m_strHeadWarningY = (itr->second == "False") ? "Safe" : "Danger";
      continue;
    }
    //报警flag 船尾X方向报警
    if (itr->first == "Boat_SternWarningX")
    {
      m_shipData.m_strSternWarningX = (itr->second == "False") ? "Safe" : "Danger";
      continue;
    }
    //报警flag 船尾Y方向报警
    if (itr->first == "Boat_SternWarningY")
    {
      m_shipData.m_strSternWarningY = (itr->second == "False") ? "Safe" : "Danger";
      continue;
    }
  }
}

jyPoint jyShipControl::getMatrixTranslate()
{
  return m_matrixTranslate;
}




