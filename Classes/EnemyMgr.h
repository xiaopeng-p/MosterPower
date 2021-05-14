#ifndef __ENEMYMGR_H__
#define __ENEMYMGR_H__
#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;
using namespace std;
class CEnemyMgr :public Node
{
public:
	CEnemyMgr();
	~CEnemyMgr();
	virtual bool init();
	CREATE_FUNC(CEnemyMgr);

	multimap<int,CEnemy*> m_VecEnemy;
	//初始化怪物数组
	void CreateEnemy();
	//更新怪物动画
	void updateEnemyAnimation(float time);
	CC_SYNTHESIZE(TMXLayer*, m_pEnemyLayer, EnemyLayer);
private:
	

};

#endif // !__ENEMYMGR_H__

