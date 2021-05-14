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
	//加载敌人数据
	CEnemyDtMgr* pEnemyDtMgr = new CEnemyDtMgr();
	pEnemyDtMgr->loadFile("Data/EnemyDt.json");
	//存储到配置管理者里面
	CConfigMgr::getInstance()->setData("EnemyDtMgr", pEnemyDtMgr);

}
