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
	//��Ϸ��ͼ��
	CGameLayer* m_pGameLayer;

	CControlLayer* m_pControlLayer;

	//��Ϸ��ͼ
	CGameMap* m_pGameMap;

	CEnemyMgr* m_pEnemyMgr;
	//��ʿ
	CHero* m_pHero;

	CPlayInfo* m_pPlayInfo;
	//Ŀ���ͼ�Ĳ���
	int m_nCurrentLevel;
	int m_nPreLevel;
	void updateLevel();
	//CFight* m_pFight;
	//��ʿ���ֵ���ʼλ��
	Point heroSpawnTileCoord;
};

#define sGlobal Global::instance()

#endif