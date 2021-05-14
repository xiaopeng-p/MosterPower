#include "GameScene.h"

CGameScene::CGameScene()
{
	CGlobal::getInstance()->m_pGameScene = this;
	pGamelayer = nullptr;
}

CGameScene::~CGameScene()
{
}

bool CGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//新建一个GameLayer实例
	pGamelayer = CGameLayer::create();
	pGamelayer->setPosition(0,324);
	//将GameLayer实例添加到场景中
	this->addChild(pGamelayer, E_ORDER_GAMELAYER, E_ORDER_GAMELAYER);

	//新建玩家信息实例
	CPlayInfo* pPlayInfo = CPlayInfo::create();
	this->addChild(pPlayInfo);

	//新建一个ControlLayer实例
	CControlLayer* pControlLayer = CControlLayer::create();

	//将ControlLayer实例添加到场景中
	this->addChild(pControlLayer, E_ORDER_CONTROLLAYER, E_ORDER_CONTROLLAYER);

	

	return true;
}

void CGameScene::switchMap()
{

	//创建一个遮罩层，用于地图切换时的显示淡入淡出效果
	LayerColor* fadeLayer = LayerColor::create(Color4B(0, 0, 0, 0));

	fadeLayer->setAnchorPoint(Point::ZERO);
	fadeLayer->setPosition(Point::ZERO);
	addChild(fadeLayer, E_ORDER_FADELAYER, E_ORDER_FADELAYER);

	//执行淡入动画，结束后调用resetGameLayer方法
	Action* action = Sequence::create(
		FadeIn::create(0.5f),
		CallFunc::create(CC_CALLBACK_0(CGameScene::resetMap, this)),
		NULL);

	fadeLayer->runAction(action);
}

void CGameScene::resetMap()
{
	pGamelayer->updataLayer();
	CGlobal::getInstance()->m_pGameLayer->getMap(0);
	//创建新的GameLayer
	/*pGamelayer = CGameLayer::create();
	pGamelayer->setPosition(0, 324);
	this->addChild(pGamelayer, E_ORDER_GAMELAYER, E_ORDER_GAMELAYER);*/
	

	//遮罩层执行淡出效果，结束后，调用removeFadeLayer方法删除遮罩层
	Action* action = Sequence::create(
		FadeOut::create(0.5f),
		CallFunc::create(CC_CALLBACK_0(CGameScene::removeFadeLayer, this)),
		NULL);

	this->getChildByTag(E_ORDER_FADELAYER)->runAction(action);
}

void CGameScene::removeFadeLayer()
{
	this->removeChildByTag(E_ORDER_FADELAYER, true);
}



