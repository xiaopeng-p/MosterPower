#include "PlayInfo.h"
#include "Global.h"
#include <cocos\ui\UIScale9Sprite.h>
using namespace ui;
CPlayInfo::CPlayInfo()
{
	CGlobal::getInstance()->m_pPlayInfo = this;
}

CPlayInfo::~CPlayInfo()
{
}

bool CPlayInfo::init()
{
	if (!Layer::init())
	{
		return false;
	}


	Scale9Sprite* pInfo = Scale9Sprite::create(Rect(20,20,60,60),"image/playinfoNew.png");
	pInfo->setContentSize(Size(416,324));
	pInfo->setAnchorPoint(Vec2(0, 0));
	this->addChild(pInfo);

	Sprite* pHero = Sprite::create("image/hero.png",Rect(0,0,32,32));
	pHero->setScale(1.5);
	pHero->setAnchorPoint(Vec2(0, 0));
	pHero->setPosition(50,270);
	this->addChild(pHero);

	/*Sprite* pYellowKey = Sprite::create("image/yellowKey.PNG");
	pYellowKey->setPosition(0, 180);
	this->addChild(pYellowKey);*/
	SpriteFrameCache* keyCache = SpriteFrameCache::getInstance();
	keyCache->addSpriteFramesWithFile("image/key.plist");

	Sprite* redKey = Sprite::createWithSpriteFrameName("keyRed.png");
	redKey->setScale(1.5);
	redKey->setPosition(225,215);
	this->addChild(redKey);

	Sprite* blueKey = Sprite::createWithSpriteFrameName("keyBlue.png");
	blueKey->setScale(1.5);
	blueKey->setPosition(225, 175);
	this->addChild(blueKey);

	Sprite* yellowKey = Sprite::createWithSpriteFrameName("KeyYellow.png");
	yellowKey->setScale(1.5);
	yellowKey->setPosition(225, 135);
	this->addChild(yellowKey);

	this->refresh();
	this->info();
	
	return true;
}

void CPlayInfo::refresh()
{
	m_nAck = CGlobal::getInstance()->m_pHero->getAck();
	m_nHp = CGlobal::getInstance()->m_pHero->getHp();
	m_nDef = CGlobal::getInstance()->m_pHero->getDef();
	m_nMoney = CGlobal::getInstance()->m_pHero->getMoney();
	m_nRedKey = CGlobal::getInstance()->m_pHero->m_arrBag[0];
	m_nBlueKey = CGlobal::getInstance()->m_pHero->m_arrBag[1];
	m_nYellowKey = CGlobal::getInstance()->m_pHero->m_arrBag[2];
	
}

void CPlayInfo::info()
{
	char szName[32] = {};

	sprintf_s(szName, "HP: %d", m_nHp);
	Label* pHP = Label::createWithTTF(szName, "fonts/arial.ttf", 25);
	pHP->setTextColor(Color4B::BLACK);
	pHP->setAnchorPoint(Vec2(0, 0));
	pHP->setPosition(Vec2(50, 220));
	this->addChild(pHP, 1, "pHp");

	sprintf_s(szName, "ACK: %d", m_nAck);
	Label* pACK = Label::createWithTTF(szName, "fonts/arial.ttf", 25);
	pACK->setTextColor(Color4B::BLACK);
	pACK->setAnchorPoint(Vec2(0, 0));
	pACK->setPosition(Vec2(50, 180));
	this->addChild(pACK, 1, "pACK");

	sprintf_s(szName, "DEF: %d", m_nDef);
	Label* pDEF = Label::createWithTTF(szName, "fonts/arial.ttf", 25);
	pDEF->setTextColor(Color4B::BLACK);
	pDEF->setAnchorPoint(Vec2(0, 0));
	pDEF->setPosition(Vec2(50, 140));
	this->addChild(pDEF, 1, "pDEF");

	sprintf_s(szName, "Money: %d", m_nMoney);
	Label* pMoney = Label::createWithTTF(szName, "fonts/arial.ttf", 25);
	pMoney->setTextColor(Color4B::BLACK);
	pMoney->setAnchorPoint(Vec2(0, 0));
	pMoney->setPosition(Vec2(50, 100));
	this->addChild(pMoney, 1, "pMoney");


	sprintf_s(szName, "   x   %d", m_nRedKey);
	Label* pRed = Label::createWithTTF(szName, "fonts/arial.ttf", 25);
	pRed->setTextColor(Color4B::BLACK);
	pRed->setAnchorPoint(Vec2(0, 0));
	pRed->setPosition(Vec2(240, 200));
	this->addChild(pRed, 1, "pRed");


	sprintf_s(szName, "   x   %d", m_nBlueKey);
	Label* pBlue = Label::createWithTTF(szName, "fonts/arial.ttf", 25);
	pBlue->setTextColor(Color4B::BLACK);
	pBlue->setAnchorPoint(Vec2(0, 0));
	pBlue->setPosition(Vec2(240, 160));
	this->addChild(pBlue, 1, "pBlue");

	sprintf_s(szName, "   x   %d", m_nYellowKey);
	Label* pYellow = Label::createWithTTF(szName, "fonts/arial.ttf", 25);
	pYellow->setTextColor(Color4B::BLACK);
	pYellow->setAnchorPoint(Vec2(0, 0));
	pYellow->setPosition(Vec2(240, 120));
	this->addChild(pYellow, 1, "pYellow");
}

void CPlayInfo::updateInfo()
{
	char szName[32] = {};
	sprintf_s(szName, "   x   %d", m_nYellowKey);
	Label* pYellow = (Label*)getChildByName("pYellow");
	pYellow->setString(szName);

	sprintf_s(szName, "   x   %d", m_nBlueKey);
	Label* pBlue = (Label*)getChildByName("pBlue");
	pBlue->setString(szName);

	sprintf_s(szName, "   x   %d", m_nRedKey);
	Label* pRed = (Label*)getChildByName("pRed");
	pRed->setString(szName);

	sprintf_s(szName, "HP: %d", m_nHp);
	Label* pHp = (Label*)getChildByName("pHp");
	pHp->setString(szName);

	sprintf_s(szName, "ACK: %d", m_nAck);
	Label* pAck = (Label*)getChildByName("pACK");
	pAck->setString(szName);

	sprintf_s(szName, "DEF: %d", m_nDef);
	Label* pDef = (Label*)getChildByName("pDEF");
	pDef->setString(szName);

	sprintf_s(szName, "Money: %d", m_nMoney);
	Label* pMoney = (Label*)getChildByName("pMoney");
	pMoney->setString(szName);

	
}

