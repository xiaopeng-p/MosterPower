#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

class CEnemy :public CEntity
{
public:
	CEnemy();
	~CEnemy();

	//怪物在TileMap上的方位
	Point position;

	//怪物初始的图块ID
	int m_nStartGID;

	//怪物在字典中的index
	int m_nIndex;

	//怪物的图片
	Sprite* m_pImg;
	
};

#endif