#ifndef __FIGHT_H__
#define __FIGHT_H__
#include "cocos2d.h"
USING_NS_CC;
class CEnemy;
class CFight : public Node
{
public:
	CFight();
	~CFight();
	virtual bool init();
	void createBg(int nID);
	CEnemy* addObject(int nID);
	void update(float delta);

	void addItem();
	CREATE_FUNC(CFight);
private:
	CEnemy* pEnemy;
	Sprite* pBg;
	char szName[32];
	int m_nHeroHp;
	int m_nEnemyHp;
private:
	void enemyFight();

	void heroFight();
};
#endif // !__FIGHT_H__

