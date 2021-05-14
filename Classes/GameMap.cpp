#include "GameMap.h"

//CGameMap* CGameMap::m_pInstance = nullptr;
CGameMap::CGameMap()
{
	CGlobal::getInstance()->m_pGameMap = this;
}

CGameMap::~CGameMap()
{
	this->unscheduleAllCallbacks();
}

//��cocos2d-x����ת��ΪTilemap����
Vec2 CGameMap::getTiledByPos(Vec2& pos)
{
	int x = pos.x / this->getTileSize().width;
	int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - pos.y) / this->getTileSize().height;
	return Point(x, y);
}
//��Tiledmap����ת����cocos2d-x����
Vec2 CGameMap::getPosByTiled(Vec2& tile)
{
	Point pos = Point((tile.x * this->getTileSize().width), ((this->getMapSize().height - tile.y - 1) * this->getTileSize().height));
	return pos;
}


CGameMap* CGameMap::createMapWithTMXFile(const char* tmxFile)
{
	//newһ������
	CGameMap* pRet = new CGameMap();

	//����init����
	if (pRet && pRet->initWithTMXFile(tmxFile))
	{
		//���ö����init����
		pRet->extraInit();
		//��ʵ������autorelease�أ�ͳһ��������ƶ������������
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

void CGameMap::extraInit()
{
	//��������ͼ����������
	enableAnitiAliasForEachLayer();

	//��ʼ���������
	m_pFloorLayer = this->getLayer("floor");
	m_pWallLayer = this->getLayer("wall");
	m_pEnemyLayer = this->getLayer("enemy");
	m_pItemLayer = this->getLayer("item");
	m_pDoorLayer = this->getLayer("door");

	//initEnemy();
	initObject();
	m_pEnemyMgr = CEnemyMgr::create();
	this->addChild(m_pEnemyMgr);
}


//��ʼ�������
void CGameMap::initObject()
{
	//��ȡ�����
	TMXObjectGroup* group = this->getObjectGroup("object");

	//��ȡ������ڵ����ж���
	const ValueVector& objects = group->getObjects();

	//�������ж���
	for (auto it: objects)
	{
		const ValueMap& dict = it.asValueMap();

		string key = "x";

		//��ȡx����
		int x = dict.at(key).asInt();
		key = "y";

		//��ȡy����
		int y = dict.at(key).asInt();
		Vec2 tileCoord = getTiledByPos(Vec2(x, y));

		//����ΨһID
		int index = tileCoord.x + tileCoord.y * this->getMapSize().width;
		key = "type";

		//��ȡ�������
		string type = dict.at(key).asString();

		//��������Ǵ�����
		if (type == "teleport")
		{
			CTeleport* teleport = new CTeleport(dict, x, y);
			m_mTeleport.insert(index, teleport);
		}
		//���������NPC����
		else if (type == "npc")
		{
			CNPC* npc = new CNPC(dict, x, y);
			m_mNpc.insert(index, npc);
		}
	}
}

void CGameMap::enableAnitiAliasForEachLayer()
{
	const Vector<Node*>& childrenArray = this->getChildren();

	//����Tilemap������ͼ��
	for (size_t i = 0, count = childrenArray.size(); i < count; i++)
	{
		SpriteBatchNode* child = (SpriteBatchNode*)childrenArray.at(i);

		if (!child)
		{
			break;
		}

		//��ͼ��������������
		child->getTexture()->setAntiAliasTexParameters();
	}
}