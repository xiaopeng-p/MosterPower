#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "NPC.h"
#include "Global.h"
#include "TelePort.h"
#include "EnemyMgr.h"
USING_NS_CC;

class CNPC;
class CTeleport;

class CGameMap :public TMXTiledMap
{
public:
	CGameMap();
	~CGameMap();
	
	//TiledMap和cocos2d-x坐标系相互转换的方法
	Vec2 getTiledByPos(Vec2& pos);
	Vec2 getPosByTiled(Vec2& tile);
	//把npc和传送门置空
	//static CGameMap* getInstance();

	//存放地图上怪物、传送门以及npc 
	//Vector<CEnemy*> m_vEnemy;
	Map<int, CTeleport*> m_mTeleport;
	Map<int, CNPC*> m_mNpc;
	CEnemyMgr* m_pEnemyMgr;
	static CGameMap* createMapWithTMXFile(const char* tmxFile);
	
	//只读变量，获取各图层CC_PROPERTY_READONLY
	CC_SYNTHESIZE(TMXLayer*, m_pFloorLayer, FloorLayer);
	CC_SYNTHESIZE(TMXLayer*, m_pWallLayer, WallLayer);
	CC_SYNTHESIZE(TMXLayer*, m_pEnemyLayer, EnemyLayer);
	CC_SYNTHESIZE(TMXLayer*, m_pItemLayer, ItemLayer);
	CC_SYNTHESIZE(TMXLayer*, m_pDoorLayer, DoorLayer);

private:
	//static CGameMap* m_pInstance;
	//临时保存战斗时的怪物
	Sprite* m_pFightingEnemy;

	//static CGameMap* m_pMap;
	

	//TiledMap额外的初始化方法
	void extraInit();
	//初始化怪物数组
	//void initEnemy();
	//初始化对象
	void initObject();

	//开启各图层的纹理抗锯齿
	void enableAnitiAliasForEachLayer();

	//更新怪物动画
	//void updateEnemyAnimation(float time);
};

#endif

