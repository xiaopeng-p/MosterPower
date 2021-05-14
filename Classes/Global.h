#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "Header.h"
USING_NS_CC;

class CGameScene;
class CGameLayer;
class CGameMap;
class CHero;
class CControlLayer;
class CEnemyMgr;
class CPlayInfo;
//class CFight;
class CGlobal 
{
public:
	CGlobal();
	~CGlobal();

	static CGlobal* getInstance();
	static CGlobal* m_pInstance;
	CGameScene* m_pGameScene;
	char* FontToUTF8(const char* font);
	//游戏主图层
	CGameLayer* m_pGameLayer;

	CControlLayer* m_pControlLayer;

	//游戏地图
	CGameMap* m_pGameMap;

	CEnemyMgr* m_pEnemyMgr;
	//勇士
	CHero* m_pHero;

	CPlayInfo* m_pPlayInfo;
	//目标地图的层数
	int m_nCurrentLevel;
	int m_nPreLevel;
	void updateLevel();
	//CFight* m_pFight;
	//勇士出现的起始位置
	Point heroSpawnTileCoord;
};

#define sGlobal Global::instance()

#endif