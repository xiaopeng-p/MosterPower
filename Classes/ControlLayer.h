#ifndef __CONTROLLAYER_H__
#define __CONTROLLAYER_H__

#include "cocos2d.h"
USING_NS_CC;
class CControlLayer :public Layer
{
public:
	CControlLayer();
	~CControlLayer();

	//node方法会调用此函数
	virtual bool init();

	void addKeyBoardEvent();
	//方向键盘点击事件的回调

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* pEvent);
	//void menuCallBackMove(Ref* pSender);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* pEvent);
	//关闭按钮点击事件的回调
	//void menuCloseCallback(Ref* pSender);

	void addTalkEvent();
	void addLoginEvent();
	CREATE_FUNC(CControlLayer);

	EventListenerKeyboard* pKeyBoard;

};

#endif