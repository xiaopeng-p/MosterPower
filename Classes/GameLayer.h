#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__
#include "cocos2d.h"
#include "EnemyMgr.h"

USING_NS_CC;
using namespace std;
class CGameMap;
class CHero;
class CFight;
class CGameLayer :public Layer
{
public:
	CGameLayer();
	~CGameLayer();

	virtual bool init();

	void initMap();
	//显示tip
	void showTip(const char* tip, Point position);
	void onShowTipDone(Node* pSender);
	
	void showTalk(const char* tip);
	void onShowTalkDone();
	void showStore();
	void showStoreBg();
	void changeState(int nAdd);
	void shopping();
	void saveMap();
	void showFight(int nID);
	//void refreshCount();
	CGameMap* getMap(int id);
	int getMapSize();
	//清除前一个地图
	void deletePreMap();
	void destoryFight();
	void updataLayer();
	CGameMap* m_pMap;
	CREATE_FUNC(CGameLayer);
	CC_SYNTHESIZE(int,m_nHpCount,HpCount);
	CC_SYNTHESIZE(int,m_nAckCount,AckCount);
	CC_SYNTHESIZE(int,m_nDefCount,DefCount);
	CC_SYNTHESIZE(int, m_nState,State);
private:
	
	CHero* m_pHero;
	CFight* m_pFight;
	Sprite* pBg;
	map<int, CGameMap*> mapData;
	
	int m_nAck;
	int m_nHp;
	int m_nDef;
	int m_nHpMoney;
	int m_nAckMoney;
	int m_nDefMoney;
	bool m_isNew;
};

#endif
