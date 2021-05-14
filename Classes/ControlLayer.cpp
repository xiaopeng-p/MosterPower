#include "ControlLayer.h"
#include "Global.h"
CControlLayer::CControlLayer()
{
	CGlobal::getInstance()->m_pControlLayer = this;
}

CControlLayer::~CControlLayer()
{
}

bool CControlLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->addKeyBoardEvent();
	return true;
}

void CControlLayer::addKeyBoardEvent()
{
	pKeyBoard = EventListenerKeyboard::create();
	pKeyBoard->onKeyPressed = CC_CALLBACK_2(CControlLayer::onKeyPressed,this);
	pKeyBoard->onKeyReleased = CC_CALLBACK_2(CControlLayer::onKeyReleased,this);
	
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(pKeyBoard,this);
	_eventDispatcher->addEventListenerWithFixedPriority(pKeyBoard,10);

	
}

void CControlLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* pEvent)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		CGlobal::getInstance()->m_pHero->move(E_STATE_DOWN);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		CGlobal::getInstance()->m_pHero->move(E_STATE_UP);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		CGlobal::getInstance()->m_pHero->move(E_STATE_RIGHT);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		CGlobal::getInstance()->m_pHero->move(E_STATE_LEFT);
		break;
	default:
		break;
	}
	
}

//void CControlLayer::menuCallBackMove(Ref* pSender)
//{
//}

void CControlLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* pEvent)
{
	//CGlobal::getInstance()->m_pHero->setHeroMoving(false);
}

void CControlLayer::addTalkEvent()
{
	EventListenerKeyboard* pTalk = EventListenerKeyboard::create();
	pTalk->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* pEvent) {
		 pKeyBoard->setEnabled(false);
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			////定义动画效果
			//Action* action = Sequence::create(
			//	/*MoveBy::create(0.5f, Point(0, 32)),*/
			//	DelayTime::create(0.5f), FadeOut::create(0.2f),
			//	CallFuncN::create(CC_CALLBACK_1(CGlobal::getInstance()->m_pGameLayer->onShowTalkDone,this)),
			//	NULL);

			//CGlobal::getInstance()->m_pGameLayer->runAction(action);
			CGlobal::getInstance()->m_pGameLayer->onShowTalkDone();
			CGlobal::getInstance()->m_pGameLayer->showStoreBg();
			CGlobal::getInstance()->m_pGameLayer->changeState(0);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			CGlobal::getInstance()->m_pGameLayer->onShowTalkDone();
			CGlobal::getInstance()->m_pGameLayer->removeChildByName("store");
			pTalk->setEnabled(false);
			pKeyBoard->setEnabled(true);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			CGlobal::getInstance()->m_pGameLayer->changeState(-1);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			CGlobal::getInstance()->m_pGameLayer->changeState(1);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			CGlobal::getInstance()->m_pGameLayer->shopping();
			CGlobal::getInstance()->m_pPlayInfo->refresh();
			CGlobal::getInstance()->m_pPlayInfo->updateInfo();
		}
	};
	pTalk->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* pEvent) {
		//pKeyBoard->setEnabled(false);
	};

	_eventDispatcher->addEventListenerWithFixedPriority(pTalk, 5);
}

