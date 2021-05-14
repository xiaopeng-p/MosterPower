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
	//传送点所在位置
	Vec2 tileCoord;

	//传送到目标层后，勇士所在坐标
	Vec2 heroTileCoord;

	//目标地图的层数
	int targetMap;

	//唯一的ID
	int index;

	//图片纹理的文件路径
	string imagePath;

	Sprite* teleportSprite;
private:

};


#endif // !__TELEPORT_H__

