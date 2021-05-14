#ifndef __TELEPORT_H__
#define __TELEPORT_H__
#include "Header.h"
USING_NS_CC;
using namespace std;
class CTeleport :public Node
{
public:
	CTeleport(const ValueMap& dict, int x, int y);
	~CTeleport();
	//���͵�����λ��
	Vec2 tileCoord;

	//���͵�Ŀ������ʿ��������
	Vec2 heroTileCoord;

	//Ŀ���ͼ�Ĳ���
	int targetMap;

	//Ψһ��ID
	int index;

	//ͼƬ������ļ�·��
	string imagePath;

	Sprite* teleportSprite;
private:

};


#endif // !__TELEPORT_H__

