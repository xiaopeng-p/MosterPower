#ifndef __CONTROLLAYER_H__
#define __CONTROLLAYER_H__

#include "cocos2d.h"
USING_NS_CC;
class CControlLayer :public Layer
{
public:
	CControlLayer();
	~CControlLayer();

	//node��������ô˺���
	virtual bool init();

	void addKeyBoardEvent();
	//������̵���¼��Ļص�

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* pEvent);
	//void menuCallBackMove(Ref* pSender);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* pEvent);
	//�رհ�ť����¼��Ļص�
	//void menuCloseCallback(Ref* pSender);

	void addTalkEvent();
	void addLoginEvent();
	CREATE_FUNC(CControlLayer);

	EventListenerKeyboard* pKeyBoard;

};

#endif