#ifndef __NPC_H__
#define __NPC_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class CNPC :public Node
{
public:
	//���캯����Ҫ���ݴ��ݵ����Ա��ʼ����������
	CNPC(const ValueMap& dict, int x, int y);
	~CNPC();
	//������ʾnpc�ľ���
	CC_SYNTHESIZE(Sprite*, m_pNpcSprite, NpcSprite);
private:
	
	//Sprite* m_pNpcSprite;

	//������TileMap�����õ�name��
	//int m_nNpcId;

	//npc���ڵ�TileMap����
	Point tileCoord;

	//ͼƬ������ļ�·��
	string imagePath;

	//�����Rect
	Rect rect;

	//��Ӧ�����е�type��
	string type;
};


#endif // !__NPC_H__

