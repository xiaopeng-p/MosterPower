#include "GameLayer.h"
#include "GameMap.h"
#include "Hero.h"
//CGameLayer* CGameLayer::m_pInstance = nullptr;
CGameLayer::CGameLayer()
{
	CGlobal::getInstance()->m_pGameLayer = this;
	m_nAckCount = 1;
	m_nHpCount = 1;
	m_nDefCount = 1;
	m_nAck = m_nAckCount * 2;
	m_nAckMoney = m_nAckCount * 4;
	m_nDef = m_nDefCount * 2;
	m_nDefMoney = m_nDefCount * 4;
	m_nHp = m_nHpCount * 10;
	m_nHpMoney = m_nHpCount * 4;
	m_nState = 1;
	m_isNew = true;
}

CGameLayer::~CGameLayer()
{
}



bool CGameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_pHero = CHero::create();
	this->addChild(m_pHero, E_ORDER_HERO, E_ORDER_HERO);

	this->updataLayer();

	

	return true;
}

void CGameLayer::updataLayer()
{
	if (getMap(CGlobal::getInstance()->m_nCurrentLevel) != nullptr)
	{
		/*CGameMap* newMap = this->getMap(CGlobal::getInstance()->m_nCurrentLevel);
		this->addChild(newMap, E_ORDER_MAP, "map");*/
		m_pMap = getMap(CGlobal::getInstance()->m_nCurrentLevel);
		m_pMap->setVisible(true);
		m_isNew = false;
		//this->addChild(Map);
		//deletePreMap();
	}
	else
	{
		char temp[20];
		sprintf(temp, "image/%d.tmx", CGlobal::getInstance()->m_nCurrentLevel);
		m_pMap = CGameMap::createMapWithTMXFile(temp);
		m_isNew = true;
		this->addChild(m_pMap);
	}
	//m_pHero->updataSprite();
	m_pHero->setPosition(CGlobal::getInstance()->heroSpawnTileCoord);
}


void CGameLayer::initMap()
{
	//解析tmx地图
	char temp[20];
	sprintf(temp, "image/%d.tmx", CGlobal::getInstance()->m_nCurrentLevel);
	m_pMap = CGameMap::createMapWithTMXFile(temp);
	this->addChild(m_pMap, E_ORDER_MAP, E_ORDER_MAP);
}

void CGameLayer::saveMap()
{
	if (m_isNew == true)
	{
		m_pMap->setVisible(false);
		mapData[CGlobal::getInstance()->m_nCurrentLevel] = m_pMap;
	}
	else
	{
		mapData[CGlobal::getInstance()->m_nCurrentLevel]->setVisible(false);
	}
}

CGameMap* CGameLayer::getMap(int id)
{
	for (auto iter : mapData)
	{
		if (iter.first == id)
		{
			return iter.second;
		}
	}
	return nullptr;
}

int CGameLayer::getMapSize()
{
	return mapData.size();
}


void CGameLayer::showTip(const char* tip, Point position)
{
	//新建一个文本标签
	Label* tipLabel = Label::createWithTTF(tip, "fonts/arial.ttf", 20);

	tipLabel->setPosition(position + Point(16, 16));


	this->addChild(tipLabel, E_ORDER_TIP, E_ORDER_TIP);

	//定义动画效果
	Action* action = Sequence::create(
		MoveBy::create(0.5f, Point(0, 32)),
		DelayTime::create(0.5f), FadeOut::create(0.2f),
		CallFuncN::create(CC_CALLBACK_1(CGameLayer::onShowTipDone, this)),
		NULL);

	tipLabel->runAction(action);
}

void CGameLayer::onShowTipDone(Node* pSender)
{
	//删掉文本标签
	this->getChildByTag(E_ORDER_TIP)->removeFromParentAndCleanup(true);

}


void CGameLayer::showTalk(const char* tip)
{


	Sprite* pTalk = Sprite::create("image/dialog_bg.png");
	//pTalk->setAnchorPoint(Vec2(1, 0));
	pTalk->setPosition(Vec2(208,208));
	this->addChild(pTalk, E_ORDER_TALK, "talk");


	//新建一个文本标签
	Label* tipLabel = Label::createWithTTF(CGlobal::getInstance()->FontToUTF8(tip), "fonts/simhei.ttf", 20);
	//tipLabel->setAnchorPoint(Vec2(0,0.5));
	tipLabel->setPosition(pTalk->getContentSize().width / 2, 50);

	pTalk->addChild(tipLabel, E_ORDER_TALK);



}

void CGameLayer::onShowTalkDone()
{
	//CCLOG("%d",this->getChildByTag(E_ORDER_TALK));
	if (this->getChildByName("talk"))
	{
		this->removeChildByName("talk");
	}
}


void CGameLayer::showStore()
{

	char szName[64] = {};

	Label* pTip1 = Label::createWithTTF(CGlobal::getInstance()->FontToUTF8("属性 加成 金币"), "fonts/simhei.ttf", 16);
	pTip1->setPosition(66, 170);
	pTip1->setColor(Color3B::WHITE);
	pBg->addChild(pTip1, 10);

	sprintf_s(szName, "HP + %d   %d", m_nHp, m_nHpMoney);
	Label* pTip2 = Label::createWithTTF(szName, "fonts/simhei.ttf", 16);
	pTip2->setPosition(66, 140);
	pTip2->setColor(Color3B::WHITE);
	pBg->addChild(pTip2, 10, "Hp");

	sprintf_s(szName, "ACK + %d   %d", m_nAck, m_nAckMoney);
	Label* pTip3 = Label::createWithTTF(szName, "fonts/simhei.ttf", 16);
	pTip3->setColor(Color3B::WHITE);
	pTip3->setPosition(66, 110);

	pBg->addChild(pTip3, 10, "Ack");



	sprintf_s(szName, "DEF + %d   %d", m_nDef, m_nDefMoney);
	Label* pTip4 = Label::createWithTTF(szName, "fonts/simhei.ttf", 16);
	pTip4->setPosition(66, 80);
	pTip4->setColor(Color3B::WHITE);
	pBg->addChild(pTip4, 10, "Def");
}

void CGameLayer::showStoreBg()
{
	pBg = Sprite::create("image/store.PNG");
	pBg->setPosition(208, 208);
	this->addChild(pBg, E_ORDER_TALK, "store");

	this->showStore();
}

void CGameLayer::changeState(int nAdd)
{
	m_nState -= nAdd;
	if (m_nState < 1)
	{
		m_nState = 3;
	}
	else if (m_nState > 3)
	{
		m_nState = 1;
	}

	if (1 == m_nState)
	{
		pBg->getChildByName("Ack")->setColor(Color3B::WHITE);
		pBg->getChildByName("Hp")->setColor(Color3B::RED);
		pBg->getChildByName("Def")->setColor(Color3B::WHITE);
	}
	else if (2 == m_nState)
	{
		pBg->getChildByName("Hp")->setColor(Color3B::WHITE);
		pBg->getChildByName("Ack")->setColor(Color3B::RED);
		pBg->getChildByName("Def")->setColor(Color3B::WHITE);
	}
	else if (3 == m_nState)
	{
		pBg->getChildByName("Ack")->setColor(Color3B::WHITE);
		pBg->getChildByName("Hp")->setColor(Color3B::WHITE);
		pBg->getChildByName("Def")->setColor(Color3B::RED);
	}
}

void CGameLayer::shopping()
{
	char szName[42] = {};
	if (1 == m_nState)
	{
		CGlobal::getInstance()->m_pHero->addHp(m_nHp);
		m_nHpCount++;
		m_nHp = m_nHpCount * 10;
		m_nHpMoney += m_nHpCount * 4;
		sprintf_s(szName, "HP + %d   %d", m_nHp, m_nHpMoney);
		Label* pHp = static_cast<Label*>(pBg->getChildByName("Hp"));
		pHp->setString(szName);
	}
	else if (2 == m_nState)
	{
		CGlobal::getInstance()->m_pHero->addAck(m_nAck);
		m_nAckCount++;
		m_nAck = m_nAckCount * 2;
		m_nAckMoney += m_nAckCount * 4;
		sprintf_s(szName, "ACK + %d   %d", m_nAck, m_nAckMoney);
		Label* pAck = static_cast<Label*>(pBg->getChildByName("Ack"));
		pAck->setString(szName);
	}
	else if (3 == m_nState)
	{
		CGlobal::getInstance()->m_pHero->addDef(m_nDef);
		m_nDefCount++;
		m_nDef = m_nDefCount * 2;
		m_nDefMoney += m_nDefCount * 4;
		sprintf_s(szName, "DEF + %d   %d", m_nDef, m_nDefMoney);
		Label* pDef = static_cast<Label*>(pBg->getChildByName("Def"));
		pDef->setString(szName);
	}
}


void CGameLayer::showFight(int nID)
{
	m_pFight = CFight::create();
	this->addChild(m_pFight, 10, "Fight");
	m_pFight->createBg(nID);

}

void CGameLayer::deletePreMap()
{
	this->removeChildByTag(E_ORDER_MAP);
}

void CGameLayer::destoryFight()
{
	this->removeChildByName("Fight");
}



