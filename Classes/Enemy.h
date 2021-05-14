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

	//������TileMap�ϵķ�λ
	Point position;

	//�����ʼ��ͼ��ID
	int m_nStartGID;

	//�������ֵ��е�index
	int m_nIndex;

	//�����ͼƬ
	Sprite* m_pImg;
	
};

#endif