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
	//�½�һ��GameLayerʵ��
	pGamelayer = CGameLayer::create();
	pGamelayer->setPosition(0,324);
	//��GameLayerʵ����ӵ�������
	this->addChild(pGamelayer, E_ORDER_GAMELAYER, E_ORDER_GAMELAYER);

	//�½������Ϣʵ��
	CPlayInfo* pPlayInfo = CPlayInfo::create();
	this->addChild(pPlayInfo);

	//�½�һ��ControlLayerʵ��
	CControlLayer* pControlLayer = CControlLayer::create();

	//��ControlLayerʵ����ӵ�������
	this->addChild(pControlLayer, E_ORDER_CONTROLLAYER, E_ORDER_CONTROLLAYER);

	

	return true;
}

void CGameScene::switchMap()
{

	//����һ�����ֲ㣬���ڵ�ͼ�л�ʱ����ʾ���뵭��Ч��
	LayerColor* fadeLayer = LayerColor::create(Color4B(0, 0, 0, 0));

	fadeLayer->setAnchorPoint(Point::ZERO);
	fadeLayer->setPosition(Point::ZERO);
	addChild(fadeLayer, E_ORDER_FADELAYER, E_ORDER_FADELAYER);

	//ִ�е��붯�������������resetGameLayer����
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
	//�����µ�GameLayer
	/*pGamelayer = CGameLayer::create();
	pGamelayer->setPosition(0, 324);
	this->addChild(pGamelayer, E_ORDER_GAMELAYER, E_ORDER_GAMELAYER);*/
	

	//���ֲ�ִ�е���Ч���������󣬵���removeFadeLayer����ɾ�����ֲ�
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



