#ifndef __DYNAMICDATA_H__
#define __DYNAMICDATA_H__
#include "cocos2d.h"
//#include "GameMap.h"
USING_NS_CC;
class CDynamicData
{
public:
	CDynamicData();
	~CDynamicData();
	static CDynamicData* getInstance();
	CC_SYNTHESIZE(int , m_nCurMapID , CurMapID);
	//CC_SYNTHESIZE(CGameMap* , m_pMap , Map);
private:
	static CDynamicData* m_pInstance;

};

#endif // ! __DYNAMICDATA_H__

