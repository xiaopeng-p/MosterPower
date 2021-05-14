#include "LoadData.h"
#include "Config.h"
#include "DataClass.h"
CLoadData::CLoadData()
{
	this->initConfigs();
}

CLoadData::~CLoadData()
{
}

void CLoadData::initConfigs()
{
	//���ص�������
	CEnemyDtMgr* pEnemyDtMgr = new CEnemyDtMgr();
	pEnemyDtMgr->loadFile("Data/EnemyDt.json");
	//�洢�����ù���������
	CConfigMgr::getInstance()->setData("EnemyDtMgr", pEnemyDtMgr);

}
