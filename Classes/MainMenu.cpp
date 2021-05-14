#include "MainMenu.h"
#include "Global.h"
#include "GameScene.h"
CMainMenu::CMainMenu()
{
}

CMainMenu::~CMainMenu()
{
}

bool CMainMenu::init()
{
	if (!Scene::init())
	{
		return false;
	}
	

	this->addBg();
	this->addLabelAndEvent();

	return true;
}

void CMainMenu::addBg()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	pCache->addSpriteFramesWithFile("image/Menu.plist");
	Sprite* pMenu = Sprite::createWithSpriteFrameName("main_bg.jpg");
	//pMenu->setScale(0.5);
	pMenu->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(pMenu);

	for (int i = 0; i <= 100;i+= 100)
	{
		Sprite* pItem = Sprite::createWithSpriteFrameName("button_bg.png");
		pItem->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + i);
		this->addChild(pItem);
	}
	
}

//添加文字和触摸事件
void CMainMenu::addLabelAndEvent()
{
	Label* pStartGame = Label::createWithTTF(CGlobal::getInstance()->FontToUTF8("开始游戏"), "fonts/simhei.ttf", 20);
	pStartGame->setPosition(208, 470);
	this->addChild(pStartGame);

	/*Label* pSetGame = Label::createWithTTF(CGlobal::getInstance()->FontToUTF8("设置"), "fonts/simhei.ttf", 20);
	pSetGame->setPosition(208, 370);
	this->addChild(pSetGame);*/

	Label* pExitGame = Label::createWithTTF(CGlobal::getInstance()->FontToUTF8("退出游戏"), "fonts/simhei.ttf", 20);
	pExitGame->setPosition(208, 370);
	this->addChild(pExitGame);
	
	auto pStart = Rect(168, 460, 80, 20);
	auto pExit = Rect(168, 360, 80, 20);
	EventListenerTouchOneByOne* eventListner = EventListenerTouchOneByOne::create();
	eventListner->onTouchBegan = [=](Touch* touch, Event* event) 
	{
		auto location =touch->getLocationInView();
		location = Director::getInstance()->convertToGL(location);
		if (pStart.containsPoint(location))
		{
			pStartGame->setColor(Color3B::RED);
		}
		else if (pExit.containsPoint(location))
		{
			pExitGame->setColor(Color3B::RED);
		}
		return true; // if you are consuming it
	};

	eventListner->onTouchMoved = [=](Touch* touch, Event* event) {
		
		/*auto location = touch->getLocationInView();
		location = Director::getInstance()->convertToGL(location);
		if (pStart.containsPoint(location))
		{
			pStartGame->setColor(Color3B::RED);
		}
		else if (pSet.containsPoint(location))
		{
			pSetGame->setColor(Color3B::RED);
		}
		else if (pExit.containsPoint(location))
		{
			pExitGame->setColor(Color3B::RED);
		}*/
			//? pStartGame->setColor(Color3B::RED) : nullptr;
	};

	// trigger when you let up
	eventListner->onTouchEnded = [=](Touch* touch, Event* event) {
		/*auto location = touch->getLocationInView();
		location = Director::getInstance()->convertToGL(location);
		if (pStart.containsPoint(location))
		{*/
			pStartGame->setColor(Color3B::WHITE);
		//}
		/*else if (pSet.containsPoint(location))
		{*/
			//pSetGame->setColor(Color3B::WHITE);
		//}
			pExitGame->setColor(Color3B::WHITE);


			auto location = touch->getLocationInView();
			location = Director::getInstance()->convertToGL(location);
			if (pStart.containsPoint(location))
			{
				Director::getInstance()->replaceScene(CGameScene::create());
			}
			/*else if (pSet.containsPoint(location))
			{
				pSetGame->setColor(Color3B::RED);
			}*/
			else if (pExit.containsPoint(location))
			{
				pExitGame->setColor(Color3B::RED);
			}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);
}


