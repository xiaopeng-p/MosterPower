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
	//��ʼ����������
	void CreateEnemy();
	//���¹��ﶯ��
	void updateEnemyAnimation(float time);
	CC_SYNTHESIZE(TMXLayer*, m_pEnemyLayer, EnemyLayer);
private:
	

};

#endif // !__ENEMYMGR_H__

