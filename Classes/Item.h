#ifndef _ITEM_H_
#define _ITEM_H_
#include "cocos2d.h"
USING_NS_CC;

class CItem
{
public:
	CItem();
	~CItem();

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
