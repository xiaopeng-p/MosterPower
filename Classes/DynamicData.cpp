#include "DynamicData.h"

CDynamicData* CDynamicData::m_pInstance = nullptr;
CDynamicData::CDynamicData()
	:m_nCurMapID(0)
{
	//m_pMap = new CGameMap();
}

CDynamicData::~CDynamicData()
{
}

CDynamicData* CDynamicData::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CDynamicData();
	}
	return m_pInstance;
}
