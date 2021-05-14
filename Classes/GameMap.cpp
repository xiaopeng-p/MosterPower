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

//从cocos2d-x坐标转换为Tilemap坐标
Vec2 CGameMap::getTiledByPos(Vec2& pos)
{
	int x = pos.x / this->getTileSize().width;
	int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - pos.y) / this->getTileSize().height;
	return Point(x, y);
}
//从Tiledmap坐标转换到cocos2d-x坐标
Vec2 CGameMap::getPosByTiled(Vec2& tile)
{
	Point pos = Point((tile.x * this->getTileSize().width), ((this->getMapSize().height - tile.y - 1) * this->getTileSize().height));
	return pos;
}


CGameMap* CGameMap::createMapWithTMXFile(const char* tmxFile)
{
	//new一个对象
	CGameMap* pRet = new CGameMap();

	//调用init方法
	if (pRet && pRet->initWithTMXFile(tmxFile))
	{
		//调用额外的init方法
		pRet->extraInit();
		//将实例放入autorelease池，统一由引擎控制对象的生命周期
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

void CGameMap::extraInit()
{
	//开启各个图层的纹理抗锯齿
	enableAnitiAliasForEachLayer();

	//初始化各层对象
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


//初始化对象层
void CGameMap::initObject()
{
	//获取对象层
	TMXObjectGroup* group = this->getObjectGroup("object");

	//获取对象层内的所有对象
	const ValueVector& objects = group->getObjects();

	//遍历所有对象
	for (auto it: objects)
	{
		const ValueMap& dict = it.asValueMap();

		string key = "x";

		//获取x坐标
		int x = dict.at(key).asInt();
		key = "y";

		//获取y坐标
		int y = dict.at(key).asInt();
		Vec2 tileCoord = getTiledByPos(Vec2(x, y));

		//计算唯一ID
		int index = tileCoord.x + tileCoord.y * this->getMapSize().width;
		key = "type";

		//获取对象类别
		string type = dict.at(key).asString();

		//如果类型是传送门
		if (type == "teleport")
		{
			CTeleport* teleport = new CTeleport(dict, x, y);
			m_mTeleport.insert(index, teleport);
		}
		//如果类型是NPC对象
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

	//遍历Tilemap的所有图层
	for (size_t i = 0, count = childrenArray.size(); i < count; i++)
	{
		SpriteBatchNode* child = (SpriteBatchNode*)childrenArray.at(i);

		if (!child)
		{
			break;
		}

		//给图层的纹理开启抗锯齿
		child->getTexture()->setAntiAliasTexParameters();
	}
}