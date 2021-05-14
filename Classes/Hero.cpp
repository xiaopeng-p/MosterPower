#include "Hero.h"
#include "Global.h"
#include "Fight.h"
CHero::CHero()
	:isHeroMoving(false)
	,isHeroFighting(false)
	,isDoorOpening(false)
	/*,m_nAck(10)
	,m_nHp(900)
	,m_nDef(10)
	,m_nHpMax(900)
	,m_nMoney(0)
	,m_nExp(0)
	,m_nGrade(1)*/
{
	CGlobal::getInstance()->m_pHero = this;
	for (int i = 0; i < 3; i++)
	{
		m_arrBag[i] = 0;
	}

	m_nHp = 900;
	m_nDef = 10;
	m_nAck = 10;
	//m_nExp = 0;
	m_nGrade = 1;
	//m_nLvExp = m_nGrade * 20;
	m_nMoney = 0;
}

CHero::~CHero()
{
}

bool CHero::init()
{
	if (!Node::init())
	{
		return false;
	}
	//�����������߶����ĵ�һ֡��������spriteWithSpriteFrame
	m_pHero = Sprite::createWithSpriteFrame(AnimationMgr::getInstance()->getAnimation(E_STATE_DOWN)->getFrames().at(0)->getSpriteFrame());
	pButtonHero = m_pHero->getTexture();
	m_pHero->setAnchorPoint(Vec2::ZERO);
	this->addChild(m_pHero);

	//�����յ�ս������
	/*m_pFight = Sprite::create();
	this->addChild(m_pFight);*/

	return true;
}
//����ƶ�
void CHero::move(HeroDirection direction)
{
	if (isHeroMoving)
	{
		return;
	}
	isHeroMoving = true;
	//�ƶ��ľ���
	Point moveByPosition;

	//���ݷ�������ƶ��ľ���
	switch (direction)
	{
	case E_STATE_DOWN:
		moveByPosition = Point(0, -32);
		break;
	case E_STATE_LEFT:
		moveByPosition = Point(-32, 0);
		break;
	case E_STATE_RIGHT:
		moveByPosition = Point(32, 0);
		break;
	case E_STATE_UP:
		moveByPosition = Point(0, 32);
		break;

	}
	//����Ŀ�����꣬�õ�ǰ��ʿ��������ƶ�����
	m_targetPosition = this->getPosition() + moveByPosition;

	//����checkCollision�����ײ���ͣ������ǽ�ڡ�����ţ���ֻ��Ҫ������ʿ�ĳ���
	CollisionType collisionType = checkCollision(m_targetPosition);

	if (collisionType == E_COLIC_WALL
		|| collisionType == E_COLIC_ENEMY
		|| collisionType == E_COLIC_DOOR
		|| collisionType == E_COLIC_NPC)
	{
		setFaceDirection((HeroDirection)direction);
		return;
	}
	//�������߶���
	m_pHero->runAction(AnimationMgr::getInstance()->createAnimate(direction));

	//�������λ�ƣ�����ʱ����onMoveDone���� �ѷ�����Ϣ���ݸ�onMoveDone����
	Sequence* pSeq = Sequence::create(
		MoveBy::create(0.20f, moveByPosition),
		CallFuncN::create(CC_CALLBACK_1(CHero::onMoveDone, this, (void*)direction)),
		NULL);

	this->runAction(pSeq);


}

void CHero::updataSprite()
{
	m_pHero = Sprite::createWithTexture(pButtonHero);
}

void CHero::addAck(int nAdd)
{
	m_nAck += nAdd;
}

void CHero::addHp(int nAdd)
{
	m_nHp += nAdd;
}

void CHero::addDef(int nAdd)
{
	m_nDef += nAdd;
}

//void CHero::addExp(int nAdd)
//{
//	m_nExp += nAdd;
//}

void CHero::addMoney(int nAdd)
{
	m_nMoney += nAdd;
}


//����ƶ�����
void CHero::onMoveDone(Node* pTarget, void* data)
{
	//��void*��ת��Ϊint���ٴ�intת����ö������
	int direction = (int)data;
	setFaceDirection((HeroDirection)direction);
	isHeroMoving = false;
	//��������������û��Ҫ
	//sGlobal->gameLayer->setSceneScrollPosition(this->getPosition());

}

//������ҵĳ���
void CHero::setFaceDirection(HeroDirection direction)
{
	isHeroMoving = false;
	m_pHero->setTextureRect(Rect(0, 32 * direction, 32, 32));

}

//ս������
void CHero::fight(int nID)
{
	//�Ѿ���ս���У������ظ�ս��
	if (isHeroFighting)
	{
		return;
	}

	isHeroFighting = true;
	CGlobal::getInstance()->m_pControlLayer->pKeyBoard->setEnabled(false);
	CGlobal::getInstance()->m_pGameLayer->showFight(nID);

	isHeroFighting = false;
}

//ս�������Ļص�����
void CHero::onFightDone(Node* pTarget)
{
	//ɾ�������Ӧ��ͼ�飬��ʾ�Ѿ�������
	CGlobal::getInstance()->m_pGameMap->getEnemyLayer()->removeTileAt(m_targetTileCoord);
	isHeroFighting = false;
}

//����Ʒ
void CHero::pickUpItem(const char* tip)
{
	//��ʾ��ʾ��Ϣ
	CGlobal::getInstance()->m_pGameLayer->showTip(tip, this->getPosition());

	//����Ʒ�ӵ�ͼ���Ƴ�
	CGlobal::getInstance()->m_pGameMap->getItemLayer()->removeTileAt(m_targetTileCoord);
}

//���Ŷ���
void CHero::openDoor(int targetDoorGID)
{
	//��������ڱ��������򷵻�
	if (isDoorOpening)
	{
		return;
	}
	int currGID = CGlobal::getInstance()->m_pGameMap->getDoorLayer()->getTileGIDAt(m_targetTileCoord);

	if (323==currGID && m_arrBag[2]>0)
	{
		m_arrBag[2]--;
		CGlobal::getInstance()->m_pPlayInfo->refresh();
		CGlobal::getInstance()->m_pPlayInfo->updateInfo();
		pickUpItem("yellow key-1");
	}
	else if (324==currGID && m_arrBag[1]>0)
	{
		m_arrBag[1]--;
		CGlobal::getInstance()->m_pPlayInfo->refresh();
		CGlobal::getInstance()->m_pPlayInfo->updateInfo();
		pickUpItem("blue key-1");
	}
	else if (325==currGID && m_arrBag[0]>0)
	{
		m_arrBag[0]--;
		CGlobal::getInstance()->m_pPlayInfo->refresh();
		CGlobal::getInstance()->m_pPlayInfo->updateInfo();
		pickUpItem("red key-1");
	}
	else {
		return;
	}
	

	

	//�������ڱ��������ŵĳ�ʼGID
	m_nTargetDoorGID = targetDoorGID;
	isDoorOpening = true;

	
	//��ʱ�������Ŷ���
	this->schedule(CC_CALLBACK_1(CHero::updateOpenDoorAnimation,this), 0.1f,"openDoor");

}

//���¿��Ŷ���
void CHero::updateOpenDoorAnimation(float time)
{

	//���㶯����һ֡��ͼ��ID��TileMap��ͼ���ŷ�ʽ�Ǻ������1������ÿ����ͬ��λ�õ�ͼ��ID�����ÿ��ͼ��ĸ���
	int nextGID = CGlobal::getInstance()->m_pGameMap->getDoorLayer()->getTileGIDAt(m_targetTileCoord) + 4;

	//��������˵���֡�������ͽ���ǰλ�õ�ͼ��ɾ������ȡ����ʱ��
	if (nextGID - m_nTargetDoorGID > 4 * 3)
	{
		CGlobal::getInstance()->m_pGameMap->getDoorLayer()->removeTileAt(m_targetTileCoord);
		unschedule("openDoor");
		isDoorOpening = false;
	}
	else
	{
		//���¶�������һ֡
		CGlobal::getInstance()->m_pGameMap->getDoorLayer()->setTileGID(nextGID, m_targetTileCoord);
	}
}

//��NPC����
void CHero::actWithNPC()
{
	CGlobal::getInstance()->m_pGameLayer->showTalk("��ʿ���ɶ��");
	CGlobal::getInstance()->m_pControlLayer->addTalkEvent();
	
}

//������
void CHero::doTeleport(CTeleport* teleport)
{
	CGlobal::getInstance()->m_pGameLayer->saveMap();
	//�Ӵ��͵�������к�ȥĿ���ͼ�Ĳ���
	CGlobal::getInstance()->m_nCurrentLevel = teleport->targetMap;

	//��ȡ��ʿ���µ�ͼ�е���ʼλ��
	CGlobal::getInstance()->heroSpawnTileCoord = teleport->heroTileCoord;

	//��ʼ�л���Ϸ��ͼ
	CGlobal::getInstance()->m_pGameLayer->getMap(0);
	CGlobal::getInstance()->m_pGameScene->switchMap();
	/*CGlobal::getInstance()->m_nCurrentLevel = 1;
	CGlobal::getInstance()->m_pGameLayer->initMap();*/
}


//�����ײ
CollisionType CHero::checkCollision(Point heroPosition)
{
	CGameMap* pMap = CGlobal::getInstance()->m_pGameLayer->m_pMap;
	//cocos2d-x����ת��ΪTilemap����
	m_targetTileCoord = pMap->getTiledByPos(heroPosition);

	//�����ʿ���곬����ͼ�߽磬����Wall���ͣ���ֹ���ƶ�
	if (heroPosition.x < 0
		|| m_targetTileCoord.x >pMap->getMapSize().width - 1
		|| m_targetTileCoord.y < 0
		|| m_targetTileCoord.y > pMap->getMapSize().height - 1)
	{
		return E_COLIC_WALL;
	}
	//��ȡǽ�ڲ��Ӧ�����ͼ��ID
	int targetTileGID = pMap->getWallLayer()->getTileGIDAt(m_targetTileCoord);
	//int i = 0;
	//���ͼ��ID��Ϊ0����ʾ��ǽ  ��·ͼ���IDΪ0��ǽ�ڵ�IDΪ1
	if (targetTileGID > 0)
	{
		return E_COLIC_WALL;
	}

	
	//��ȡ������Ӧ�����ͼ��ID
	targetTileGID = pMap->m_pEnemyMgr->getEnemyLayer()->getTileGIDAt(m_targetTileCoord);

	//���ͼ��ID��Ϊ0����ʾ�й���
	if (targetTileGID > 0)
	{
		//��ʼս��
		fight(targetTileGID);
		return E_COLIC_ENEMY;
	}

	//��ȡ��Ʒ���Ӧ�����ͼ��ID
	targetTileGID = pMap->getItemLayer()->getTileGIDAt(m_targetTileCoord);

	//���ͼ��ID��Ϊ0����ʾ����Ʒ
	if (targetTileGID>0)
	{
		//ʰȡ��Ʒ
		if (5== targetTileGID)
		{
			addHp(50);
			pickUpItem("Hp+50");
		}
		else if (2== targetTileGID)
		{
			addDef(1);
			pickUpItem("Def+1");
		}
		else if (1== targetTileGID)
		{
			addAck(1);
			pickUpItem("Ack+1");
		}
		else if (6== targetTileGID)
		{
			addHp(200);
			pickUpItem("HP+200");
		}
		/*else if (17== targetTileGID)
		{
			m_nAck++;
			pickUpItem("ACK+1");
		}
		else if (276== targetTileGID)
		{
			m_nDef++;
			pickUpItem("DEF+1");
		}*/
		else if (19== targetTileGID)
		{
			m_arrBag[0]++;
			pickUpItem("red key+1");
		}
		else if (18== targetTileGID)
		{
			m_arrBag[1]++;
			pickUpItem("blue key+1");
		}
		else if (17== targetTileGID)
		{
			m_arrBag[2]++;
			pickUpItem("yellow key+1");
		}
		CGlobal::getInstance()->m_pPlayInfo->refresh();
		CGlobal::getInstance()->m_pPlayInfo->updateInfo();
		
		return E_COLIC_ITEM;
	}

	//��ȡ�Ų��Ӧ�����ͼ��ID
	targetTileGID = pMap->getDoorLayer()->getTileGIDAt(m_targetTileCoord);

	//���ͼ��ID��Ϊ0����ʾ����
	if (targetTileGID>0)
	{
		//����
		openDoor(targetTileGID);
		return E_COLIC_DOOR;
	}

	int index = m_targetTileCoord.x + m_targetTileCoord.y * pMap->getMapSize().width;
	
	//��npc�ֵ��в�ѯ
	CNPC* npc = pMap->m_mNpc.at(index);
	if (npc != NULL)
	{
		actWithNPC();
		return E_COLIC_NPC;
	}

	//��Teleport�ֵ��в�ѯ
	CTeleport* teleport = pMap->m_mTeleport.at(index);
	if (teleport != NULL)
	{
		doTeleport(teleport);
		return E_COLIC_TELEPORT;
	}

	//����ͨ��
	return E_COLIC_NONE;
}


