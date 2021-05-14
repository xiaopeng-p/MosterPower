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

	//���ڸ��µ��˶���
	this->schedule(CC_CALLBACK_1(CEnemyMgr::updateEnemyAnimation, this), 0.15f, "updateEnemyAnimation");

	return true;
}

void CEnemyMgr::CreateEnemy()
{
	//��ȡ�����
	m_pEnemyLayer = CGlobal::getInstance()->m_pGameMap->getLayer("enemy");
	
	Size tiledSize = m_pEnemyLayer->getLayerSize();

	//����enemy�㣬�����ڵĹ��ﱣ�浽������
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

				//�����������
				enemy->position = Point(x, y);
				enemy->m_pImg = m_pEnemyLayer->getTileAt(Point(x, y));
				//���������ʼ��ͼ��ID
				enemy->m_nStartGID = gid;
				enemy->setAck(pDataMgr->nAck);
				enemy->setHp(pDataMgr->nHp);
				enemy->setDef(pDataMgr->nDef);
				enemy->setMoney(pDataMgr->nMoney);
				//��ӹ����������
				m_VecEnemy.insert(pair<int,CEnemy*>(gid,enemy));
			}
		}
	}


}

void CEnemyMgr::updateEnemyAnimation(float time)
{
	
	//��Ҫ�Ƴ��Ĺ���
	//CEnemy* needRemove = nullptr;
	pair<int, CEnemy*>(needRemove) = pair<int, CEnemy*>(0,nullptr);

	//�����������й�����������
	for (pair<int, CEnemy*>(pEnemy):m_VecEnemy)
	{
		
		if (pEnemy.second != nullptr)
		{
			//��ȡ���ﵱǰ��ͼ��ID
			int gid = m_pEnemyLayer->getTileGIDAt(pEnemy.second->position);

			//������ﱻɾ���ˣ���Ҫ������enemyArray��Ҳɾ��
			if (gid == 0)
			{
				needRemove = pEnemy;
				continue;
			}
			gid++;

			//�����һ��ͼ��ID ��ʼͼ��ID
			if (gid - pEnemy.second->m_nStartGID > 3)
			{
				gid = pEnemy.second->m_nStartGID;
			}

			//�����������µ�ͼ��
			m_pEnemyLayer->setTileGID(gid, pEnemy.second->position);
		}
	}

	//ɾ��������Ĺ���
	if (needRemove.second != NULL)
	{
		auto iter= m_VecEnemy.find(needRemove.first);
		m_VecEnemy.erase(iter);
	}
}
