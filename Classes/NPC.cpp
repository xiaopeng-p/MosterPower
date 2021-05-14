#include "NPC.h"
#include "Global.h"
CNPC::CNPC(const ValueMap& dict, int x, int y)
{
	//获取名称
	std::string key = "";
	//m_nNpcId = dict.at(key).asInt();

	//获取类型
	key = "type";
	type = dict.at(key).asString();

	//获取image项
	key = "image";
	imagePath = dict.at(key).asString();

	//获取rectX和rectY
	key = "rectX";
	int x1 = dict.at(key).asInt();

	key = "rectY";
	int y1 = dict.at(key).asInt();

	rect = Rect(x1, y1, 32, 32);

	//position为cocos2d-x坐标，tileCoord为TileMap坐标
	Point position = Point(x, y);
	//tileCoord = CGlobal::getInstance()->m_pGameMap->getTiledByPos(position);

	//创建用于显示npc的精灵
	m_pNpcSprite = Sprite::create(imagePath, rect);
	m_pNpcSprite->setAnchorPoint(Point::ZERO);
	m_pNpcSprite->setPosition(position);

	CGlobal::getInstance()->m_pGameMap->addChild(m_pNpcSprite, E_ORDER_NPC);

	//从动画管理器中根据npcId获取动画，开始永久播放
	Animate* animation = AnimationMgr::getInstance()->createAnimate("npc0");
	if (animation != NULL)
	{
		ActionInterval* action = RepeatForever::create(animation);
		m_pNpcSprite->runAction(action);
	}
}

CNPC::~CNPC()
{
}
