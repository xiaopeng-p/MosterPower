#include "NPC.h"
#include "Global.h"
CNPC::CNPC(const ValueMap& dict, int x, int y)
{
	//��ȡ����
	std::string key = "";
	//m_nNpcId = dict.at(key).asInt();

	//��ȡ����
	key = "type";
	type = dict.at(key).asString();

	//��ȡimage��
	key = "image";
	imagePath = dict.at(key).asString();

	//��ȡrectX��rectY
	key = "rectX";
	int x1 = dict.at(key).asInt();

	key = "rectY";
	int y1 = dict.at(key).asInt();

	rect = Rect(x1, y1, 32, 32);

	//positionΪcocos2d-x���꣬tileCoordΪTileMap����
	Point position = Point(x, y);
	//tileCoord = CGlobal::getInstance()->m_pGameMap->getTiledByPos(position);

	//����������ʾnpc�ľ���
	m_pNpcSprite = Sprite::create(imagePath, rect);
	m_pNpcSprite->setAnchorPoint(Point::ZERO);
	m_pNpcSprite->setPosition(position);

	CGlobal::getInstance()->m_pGameMap->addChild(m_pNpcSprite, E_ORDER_NPC);

	//�Ӷ����������и���npcId��ȡ��������ʼ���ò���
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
