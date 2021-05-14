#include "EnemyMgr.h"
#include "Global.h"
#include "Config.h"
#include "DataClass.h"
CEnemyMgr::CEnemyMgr()
{
	CGlobal::getInstance()->m_pEnemyMgr = this;
}

CEnemyMgr::~CEnemyMgr()
{
}

bool CEnemyMgr::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->CreateEnemy();

	//用于更新敌人动画
	this->schedule(CC_CALLBACK_1(CEnemyMgr::updateEnemyAnimation, this), 0.15f, "updateEnemyAnimation");

	return true;
}

void CEnemyMgr::CreateEnemy()
{
	//获取怪物层
	m_pEnemyLayer = CGlobal::getInstance()->m_pGameMap->getLayer("enemy");
	
	Size tiledSize = m_pEnemyLayer->getLayerSize();

	//遍历enemy层，将存在的怪物保存到数组中
	for (int x = 0; x < tiledSize.width; x++)
	{
		for (int y = 0; y < tiledSize.height; y++)
		{
			int gid = m_pEnemyLayer->getTileGIDAt(Point(x, y));
			
			if (gid != 0)
			{
				int nNewGid = gid - 68;
				SEnemyDt* pDataMgr = static_cast<SEnemyDt*>(CConfigMgr::getInstance()->getData("EnemyDtMgr")->getDataByID(nNewGid));
				CEnemy* enemy = new CEnemy();

				//保存怪物坐标
				enemy->position = Point(x, y);
				enemy->m_pImg = m_pEnemyLayer->getTileAt(Point(x, y));
				//保存怪物起始的图块ID
				enemy->m_nStartGID = gid;
				enemy->setAck(pDataMgr->nAck);
				enemy->setHp(pDataMgr->nHp);
				enemy->setDef(pDataMgr->nDef);
				enemy->setMoney(pDataMgr->nMoney);
				//添加怪物对象到数组
				m_VecEnemy.insert(pair<int,CEnemy*>(gid,enemy));
			}
		}
	}


}

void CEnemyMgr::updateEnemyAnimation(float time)
{
	
	//需要移除的怪物
	//CEnemy* needRemove = nullptr;
	pair<int, CEnemy*>(needRemove) = pair<int, CEnemy*>(0,nullptr);

	//遍历保存所有怪物对象的数组
	for (pair<int, CEnemy*>(pEnemy):m_VecEnemy)
	{
		
		if (pEnemy.second != nullptr)
		{
			//获取怪物当前的图块ID
			int gid = m_pEnemyLayer->getTileGIDAt(pEnemy.second->position);

			//如果怪物被删除了，需要把它在enemyArray中也删除
			if (gid == 0)
			{
				needRemove = pEnemy;
				continue;
			}
			gid++;

			//如果下一个图块ID 起始图块ID
			if (gid - pEnemy.second->m_nStartGID > 3)
			{
				gid = pEnemy.second->m_nStartGID;
			}

			//给怪物设置新的图块
			m_pEnemyLayer->setTileGID(gid, pEnemy.second->position);
		}
	}

	//删除被消灭的怪物
	if (needRemove.second != NULL)
	{
		auto iter= m_VecEnemy.find(needRemove.first);
		m_VecEnemy.erase(iter);
	}
}
