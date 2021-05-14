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
	
	//TiledMap��cocos2d-x����ϵ�໥ת���ķ���
	Vec2 getTiledByPos(Vec2& pos);
	Vec2 getPosByTiled(Vec2& tile);
	//��npc�ʹ������ÿ�
	//static CGameMap* getInstance();

	//��ŵ�ͼ�Ϲ���������Լ�npc 
	//Vector<CEnemy*> m_vEnemy;
	Map<int, CTeleport*> m_mTeleport;
	Map<int, CNPC*> m_mNpc;
	CEnemyMgr* m_pEnemyMgr;
	static CGameMap* createMapWithTMXFile(const char* tmxFile);
	
	//ֻ����������ȡ��ͼ��CC_PROPERTY_READONLY
	CC_SYNTHESIZE(TMXLayer*, m_pFloorLayer, FloorLayer);
	CC_SYNTHESIZE(TMXLayer*, m_pWallLayer, WallLayer);
	CC_SYNTHESIZE(TMXLayer*, m_pEnemyLayer, EnemyLayer);
	CC_SYNTHESIZE(TMXLayer*, m_pItemLayer, ItemLayer);
	CC_SYNTHESIZE(TMXLayer*, m_pDoorLayer, DoorLayer);

private:
	//static CGameMap* m_pInstance;
	//��ʱ����ս��ʱ�Ĺ���
	Sprite* m_pFightingEnemy;

	//static CGameMap* m_pMap;
	

	//TiledMap����ĳ�ʼ������
	void extraInit();
	//��ʼ����������
	//void initEnemy();
	//��ʼ������
	void initObject();

	//������ͼ����������
	void enableAnitiAliasForEachLayer();

	//���¹��ﶯ��
	//void updateEnemyAnimation(float time);
};

#endif

