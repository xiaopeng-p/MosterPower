#include "Fight.h"
#include "Global.h"
CFight::CFight()
{
	//CGlobal::getInstance()->m_pFight = this;
	m_nHeroHp = CGlobal::getInstance()->m_pHero->getHp();

}

CFight::~CFight()
{
}

bool CFight::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	return true;
}

void CFight::createBg(int nID)
{
	
	pBg = Sprite::create("image/battle_bg.jpg");
	pBg->setPosition(208,208);
	this->addChild(pBg,1,"fightBg");
	
	pEnemy= this->addObject(nID);

	SpriteFrame*  pEnemyFrame=pEnemy->m_pImg->getSpriteFrame();
	Sprite* pEnemySprite = Sprite::createWithSpriteFrame(pEnemyFrame);//pEnemy->m_pImg;
	
	pEnemySprite->setPosition(Vec2(40,100));
	pEnemySprite->setAnchorPoint(Vec2(0.5, 0.5));
	pEnemySprite->setScale(1.5);
	pBg->addChild(pEnemySprite);

	m_nEnemyHp = pEnemy->getHp();

	Sprite* pHero = Sprite::create("image/hero.png", Rect(0, 0, 32, 32));
	pHero->setPosition(308, 100);
	pHero->setAnchorPoint(Vec2(0.5, 0.5));
	pHero->setScale(1.5);
	pBg->addChild(pHero);

	this->addItem();

	this->schedule(CC_CALLBACK_0(CFight::heroFight,this),0.7,"heroFight");
	this->schedule(CC_CALLBACK_0(CFight::enemyFight,this),0.7,100,0.5,"enemyFight");

	this->scheduleUpdate();
	
}

CEnemy* CFight::addObject(int nID)
{
	for (pair<int, CEnemy*>(pEnemy) :CGlobal::getInstance()->m_pGameLayer->m_pMap->m_pEnemyMgr->m_VecEnemy)
	{
		int nStartID = pEnemy.first;
		if (nStartID <= nID && nID <= nStartID + 3)
		{
			return pEnemy.second;
		}
	}
}



void CFight::update(float delta)
{
	if (pEnemy->getHp() < 1)
	{
		CGlobal::getInstance()->m_pGameLayer->m_pMap->getEnemyLayer()->removeTileAt(CGlobal::getInstance()->m_pHero->gettargetTileCoord());
		this->unscheduleUpdate();
		this->unschedule("heroFight");
		this->unschedule("enemyFight");

		
		CGlobal::getInstance()->m_pHero->addMoney(pEnemy->getMoney());
		CGlobal::getInstance()->m_pPlayInfo->refresh();
		CGlobal::getInstance()->m_pPlayInfo->updateInfo();
		//this->removeChildByName("fightBg");
		CGlobal::getInstance()->m_pGameLayer->destoryFight();
		CGlobal::getInstance()->m_pControlLayer->pKeyBoard->setEnabled(true);
	}
	else if (CGlobal::getInstance()->m_pHero->getHp() < 1)
	{
		this->unscheduleUpdate();
		this->unschedule("heroFight");
		this->unschedule("enemyFight");
		CGlobal::getInstance()->m_pControlLayer->pKeyBoard->setEnabled(true);
	}
}

void CFight::addItem()
{
	char szName[32] = {};
	sprintf_s(szName, "%d", pEnemy->getHp());
	Label* pHp = Label::createWithTTF(szName,"fonts/simhei.ttf",20);
	pHp->setAnchorPoint(Vec2(0, 0.5));
	pHp->setPosition(110,130);
	pBg->addChild(pHp,1,"enemyHp");

	sprintf_s(szName,"%d",pEnemy->getAck());
	Label* pAck = Label::createWithTTF(szName,"fonts/simhei.ttf",20);
	pAck->setAnchorPoint(Vec2(0, 0.5));
	pAck->setPosition(110, 96);
	pBg->addChild(pAck, 1, "enemyAck");

	sprintf_s(szName, "%d", pEnemy->getDef());
	Label* pDef = Label::createWithTTF(szName, "fonts/simhei.ttf", 20);
	pDef->setAnchorPoint(Vec2(0, 0.5));
	pDef->setPosition(110, 60);
	pBg->addChild(pDef, 1, "enemyDef");

	sprintf_s(szName, "%d", CGlobal::getInstance()->m_pHero->getHp());
	Label* pHeroHp = Label::createWithTTF(szName, "fonts/simhei.ttf", 20);
	pHeroHp->setAnchorPoint(Vec2(1, 0.5));
	pHeroHp->setPosition(230, 130);
	pBg->addChild(pHeroHp, 1, "heroHp");

	sprintf_s(szName, "%d", CGlobal::getInstance()->m_pHero->getAck());
	Label* pHeroAck = Label::createWithTTF(szName, "fonts/simhei.ttf", 20);
	pHeroAck->setAnchorPoint(Vec2(1, 0.5));
	pHeroAck->setPosition(230, 96);
	pBg->addChild(pHeroAck, 1, "heroAck");
	
	sprintf_s(szName, "%d", CGlobal::getInstance()->m_pHero->getDef());
	Label* pHeroDef = Label::createWithTTF(szName, "fonts/simhei.ttf", 20);
	pHeroDef->setAnchorPoint(Vec2(1, 0.5));
	pHeroDef->setPosition(230, 60);
	pBg->addChild(pHeroDef, 1, "heroDef");

}

void CFight::enemyFight()
{
	
	Label* pHeroHp = static_cast<Label*>(pBg->getChildByName("heroHp"));
	m_nHeroHp -= (pEnemy->getAck()- CGlobal::getInstance()->m_pHero->getDef());
	CGlobal::getInstance()->m_pHero->setHp(m_nHeroHp);
	sprintf_s(szName, "%d", CGlobal::getInstance()->m_pHero->getHp());
	pHeroHp->setString(szName);

}

void CFight::heroFight()
{
	Label* pEnemyHp = static_cast<Label*>(pBg->getChildByName("enemyHp"));
	m_nEnemyHp -= (CGlobal::getInstance()->m_pHero->getAck() - pEnemy->getDef());
	pEnemy->setHp(m_nEnemyHp);
	sprintf_s(szName, "%d", pEnemy->getHp());
	pEnemyHp->setString(szName);
}
