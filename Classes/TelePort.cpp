#include "TelePort.h"

CTeleport::CTeleport(const ValueMap& dict, int x, int y)
{
	Point position = Point(x, y);

	//���͵����ڵ�TileMapλ��
	tileCoord = CGlobal::getInstance()->m_pGameMap->getTiledByPos(Vec2(x, y));

	//�ó���ʿ��Ŀ������ʼλ��
	string key = "heroTileCoordX";
	int x1 = dict.at(key).asInt();

	key = "heroTileCoordY";
	int y1 = dict.at(key).asInt();

	heroTileCoord = CGlobal::getInstance()->m_pGameMap->getPosByTiled(Point(x1, y1));

	//ȡ��Ŀ���ͼ�Ĳ���
	key = "targetMap";
	targetMap = dict.at(key).asInt();
	int i = 0;
	//��ȡimage��
	key = "image";
	imagePath = dict.at(key).asString();

	//����������ʾTeleport�ľ���
	teleportSprite = Sprite::create(imagePath);
	teleportSprite->setAnchorPoint(Point::ZERO);
	teleportSprite->setPosition(position);
	
	CGlobal::getInstance()->m_pGameMap->addChild(teleportSprite,E_ORDER_TELEPORT);
}

CTeleport::~CTeleport()
{
}
