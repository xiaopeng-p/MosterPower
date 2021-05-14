#ifndef __NPC_H__
#define __NPC_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class CNPC :public Node
{
public:
	//构造函数中要根据传递的属性表初始化各个变量
	CNPC(const ValueMap& dict, int x, int y);
	~CNPC();
	//用于显示npc的精灵
	CC_SYNTHESIZE(Sprite*, m_pNpcSprite, NpcSprite);
private:
	
	//Sprite* m_pNpcSprite;

	//保存在TileMap中配置的name项
	//int m_nNpcId;

	//npc所在的TileMap坐标
	Point tileCoord;

	//图片纹理的文件路径
	string imagePath;

	//纹理的Rect
	Rect rect;

	//对应配置中的type项
	string type;
};


#endif // !__NPC_H__

