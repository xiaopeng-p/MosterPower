#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "Header.h"

USING_NS_CC;
class CGameScene :public Scene
{
public:
	CGameScene();
	~CGameScene();

	//³õÊ¼»¯º¯Êý
	virtual bool init();


	void switchMap();

	void resetMap();

	void removeFadeLayer();

	CGameLayer* pGamelayer;

	CREATE_FUNC(CGameScene);
	
};
#endif // !__GAMESCENE_H__

