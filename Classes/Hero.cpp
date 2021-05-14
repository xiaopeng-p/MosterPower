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
	//根据向下行走动画的第一帧创建精灵spriteWithSpriteFrame
	m_pHero = Sprite::createWithSpriteFrame(AnimationMgr::getInstance()->getAnimation(E_STATE_DOWN)->getFrames().at(0)->getSpriteFrame());
	pButtonHero = m_pHero->getTexture();
	m_pHero->setAnchorPoint(Vec2::ZERO);
	this->addChild(m_pHero);

	//创建空的战斗精灵
	/*m_pFight = Sprite::create();
	this->addChild(m_pFight);*/

	return true;
}
//玩家移动
void CHero::move(HeroDirection direction)
{
	if (isHeroMoving)
	{
		return;
	}
	isHeroMoving = true;
	//移动的距离
	Point moveByPosition;

	//根据方向计算移动的距离
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
	//计算目标坐标，用当前勇士坐标加上移动距离
	m_targetPosition = this->getPosition() + moveByPosition;

	//调用checkCollision检测碰撞类型，如果是墙壁、怪物、门，则只需要设置勇士的朝向
	CollisionType collisionType = checkCollision(m_targetPosition);

	if (collisionType == E_COLIC_WALL
		|| collisionType == E_COLIC_ENEMY
		|| collisionType == E_COLIC_DOOR
		|| collisionType == E_COLIC_NPC)
	{
		setFaceDirection((HeroDirection)direction);
		return;
	}
	//播放行走动画
	m_pHero->runAction(AnimationMgr::getInstance()->createAnimate(direction));

	//主体进行位移，结束时调用onMoveDone方法 把方向信息传递给onMoveDone方法
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


//玩家移动结束
void CHero::onMoveDone(Node* pTarget, void* data)
{
	//将void*先转换为int，再从int转换到枚举类型
	int direction = (int)data;
	setFaceDirection((HeroDirection)direction);
	isHeroMoving = false;
	//场景滚动，但是没必要
	//sGlobal->gameLayer->setSceneScrollPosition(this->getPosition());

}

//设置玩家的朝向
void CHero::setFaceDirection(HeroDirection direction)
{
	isHeroMoving = false;
	m_pHero->setTextureRect(Rect(0, 32 * direction, 32, 32));

}

//战斗动画
void CHero::fight(int nID)
{
	//已经在战斗中，避免重复战斗
	if (isHeroFighting)
	{
		return;
	}

	isHeroFighting = true;
	CGlobal::getInstance()->m_pControlLayer->pKeyBoard->setEnabled(false);
	CGlobal::getInstance()->m_pGameLayer->showFight(nID);

	isHeroFighting = false;
}

//战斗结束的回调函数
void CHero::onFightDone(Node* pTarget)
{
	//删除怪物对应的图块，表示已经被消灭
	CGlobal::getInstance()->m_pGameMap->getEnemyLayer()->removeTileAt(m_targetTileCoord);
	isHeroFighting = false;
}

//捡物品
void CHero::pickUpItem(const char* tip)
{
	//显示提示消息
	CGlobal::getInstance()->m_pGameLayer->showTip(tip, this->getPosition());

	//将物品从地图上移除
	CGlobal::getInstance()->m_pGameMap->getItemLayer()->removeTileAt(m_targetTileCoord);
}

//开门动画
void CHero::openDoor(int targetDoorGID)
{
	//如果门正在被开启，则返回
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
	

	

	//保存正在被开启的门的初始GID
	m_nTargetDoorGID = targetDoorGID;
	isDoorOpening = true;

	
	//定时器更新门动画
	this->schedule(CC_CALLBACK_1(CHero::updateOpenDoorAnimation,this), 0.1f,"openDoor");

}

//更新开门动画
void CHero::updateOpenDoorAnimation(float time)
{

	//计算动画下一帧的图块ID，TileMap的图块编号方式是横向递增1，所以每列相同的位置的图块ID相差了每行图块的个数
	int nextGID = CGlobal::getInstance()->m_pGameMap->getDoorLayer()->getTileGIDAt(m_targetTileCoord) + 4;

	//如果超过了第四帧动画，就将当前位置的图块删除，并取消定时器
	if (nextGID - m_nTargetDoorGID > 4 * 3)
	{
		CGlobal::getInstance()->m_pGameMap->getDoorLayer()->removeTileAt(m_targetTileCoord);
		unschedule("openDoor");
		isDoorOpening = false;
	}
	else
	{
		//更新动画至下一帧
		CGlobal::getInstance()->m_pGameMap->getDoorLayer()->setTileGID(nextGID, m_targetTileCoord);
	}
}

//与NPC交互
void CHero::actWithNPC()
{
	CGlobal::getInstance()->m_pGameLayer->showTalk("勇士买点啥？");
	CGlobal::getInstance()->m_pControlLayer->addTalkEvent();
	
}

//传送门
void CHero::doTeleport(CTeleport* teleport)
{
	CGlobal::getInstance()->m_pGameLayer->saveMap();
	//从传送点的属性中后去目标地图的层数
	CGlobal::getInstance()->m_nCurrentLevel = teleport->targetMap;

	//获取勇士在新地图中的起始位置
	CGlobal::getInstance()->heroSpawnTileCoord = teleport->heroTileCoord;

	//开始切换游戏地图
	CGlobal::getInstance()->m_pGameLayer->getMap(0);
	CGlobal::getInstance()->m_pGameScene->switchMap();
	/*CGlobal::getInstance()->m_nCurrentLevel = 1;
	CGlobal::getInstance()->m_pGameLayer->initMap();*/
}


//检测碰撞
CollisionType CHero::checkCollision(Point heroPosition)
{
	CGameMap* pMap = CGlobal::getInstance()->m_pGameLayer->m_pMap;
	//cocos2d-x坐标转换为Tilemap坐标
	m_targetTileCoord = pMap->getTiledByPos(heroPosition);

	//如果勇士坐标超过地图边界，返回Wall类型，阻止其移动
	if (heroPosition.x < 0
		|| m_targetTileCoord.x >pMap->getMapSize().width - 1
		|| m_targetTileCoord.y < 0
		|| m_targetTileCoord.y > pMap->getMapSize().height - 1)
	{
		return E_COLIC_WALL;
	}
	//获取墙壁层对应坐标的图块ID
	int targetTileGID = pMap->getWallLayer()->getTileGIDAt(m_targetTileCoord);
	//int i = 0;
	//如果图块ID不为0，表示有墙  道路图快的ID为0，墙壁的ID为1
	if (targetTileGID > 0)
	{
		return E_COLIC_WALL;
	}

	
	//获取怪物层对应坐标的图块ID
	targetTileGID = pMap->m_pEnemyMgr->getEnemyLayer()->getTileGIDAt(m_targetTileCoord);

	//如果图块ID不为0，表示有怪物
	if (targetTileGID > 0)
	{
		//开始战斗
		fight(targetTileGID);
		return E_COLIC_ENEMY;
	}

	//获取物品层对应坐标的图块ID
	targetTileGID = pMap->getItemLayer()->getTileGIDAt(m_targetTileCoord);

	//如果图块ID不为0，表示有物品
	if (targetTileGID>0)
	{
		//拾取物品
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

	//获取门层对应坐标的图块ID
	targetTileGID = pMap->getDoorLayer()->getTileGIDAt(m_targetTileCoord);

	//如果图块ID不为0，表示有门
	if (targetTileGID>0)
	{
		//打开门
		openDoor(targetTileGID);
		return E_COLIC_DOOR;
	}

	int index = m_targetTileCoord.x + m_targetTileCoord.y * pMap->getMapSize().width;
	
	//从npc字典中查询
	CNPC* npc = pMap->m_mNpc.at(index);
	if (npc != NULL)
	{
		actWithNPC();
		return E_COLIC_NPC;
	}

	//从Teleport字典中查询
	CTeleport* teleport = pMap->m_mTeleport.at(index);
	if (teleport != NULL)
	{
		doTeleport(teleport);
		return E_COLIC_TELEPORT;
	}

	//可以通行
	return E_COLIC_NONE;
}


