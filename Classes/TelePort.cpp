#include "TelePort.h"

CTeleport::CTeleport(const ValueMap& dict, int x, int y)
{
	Point position = Point(x, y);

	//传送点所在的TileMap位置
	tileCoord = CGlobal::getInstance()->m_pGameMap->getTiledByPos(Vec2(x, y));

	//得出勇士在目标层的起始位置
	string key = "heroTileCoordX";
	int x1 = dict.at(key).asInt();

	key = "heroTileCoordY";
	int y1 = dict.at(key).asInt();

	heroTileCoord = CGlobal::getInstance()->m_pGameMap->getPosByTiled(Point(x1, y1));

	//取得目标地图的层数
	key = "targetMap";
	targetMap = dict.at(key).asInt();
	int i = 0;
	//获取image项
	key = "image";
	imagePath = dict.at(key).asString();

	//创建用于显示Teleport的精灵
	teleportSprite = Sprite::create(imagePath);
	teleportSprite->setAnchorPoint(Point::ZERO);
	teleportSprite->setPosition(position);
	
	CGlobal::getInstance()->m_pGameMap->addChild(teleportSprite,E_ORDER_TELEPORT);
}

CTeleport::~CTeleport()
{
}
