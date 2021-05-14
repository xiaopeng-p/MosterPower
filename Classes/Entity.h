#ifndef __ENTITY_H__
#define __ENTITY_H__
#include "cocos2d.h"
USING_NS_CC;
class CEntity
{
public:
	CEntity();
	~CEntity();
	CC_SYNTHESIZE(int,m_nID,ID);
	CC_SYNTHESIZE(int, m_nAck, Ack);
	CC_SYNTHESIZE(int, m_nGrade, Grade);
	CC_SYNTHESIZE(int, m_nDef, Def);
	CC_SYNTHESIZE(int, m_nHp, Hp);
	CC_SYNTHESIZE(int, m_nMoney, Money);
private:

};

#endif // !__ENTITY_H__

