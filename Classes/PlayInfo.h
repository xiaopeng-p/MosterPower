#ifndef __PLAYINFO_H__
#define __PLAYINFO_H__
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
class CPlayInfo :public Layer
{
public:
	CPlayInfo();
	~CPlayInfo();

	virtual bool init();

	void refresh();

	void updateInfo();
	void info();
	CREATE_FUNC(CPlayInfo);
private:
	int m_nHp;
	int m_nAck;
	int m_nDef;
	int m_nMoney;
	int m_nRedKey;
	int m_nYellowKey;
	int m_nBlueKey;
};

#endif // !__PLAYINFO_H__

