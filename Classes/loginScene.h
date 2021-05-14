#ifndef __CLOGINSCENE_H__
#define __CLOGINSCENE_H__
#include "cocos2d.h"
#include "Header.h"
#include <cocos\ui\UIWidget.h>
#include <network\HttpClient.h>
#include <ui/CocosGUI.h>
USING_NS_CC;
using namespace ui;
using namespace cocos2d::network;
class CLoginScene :public Scene
{
public:
	CLoginScene();
	~CLoginScene();

	//初始化函数
	virtual bool init();
	void login();
	void regist();
	void httpResponse(HttpClient* client, HttpResponse* response);
	void httpResponse2(HttpClient* client, HttpResponse* response);
	////添加背景
	//void addBg();
	////给按钮添加文字
	//void addLabelAndEvent();
	void simulatePop(string str);
	void onShowDone(Ref* pRef);
	void addEventTouch();
	Sprite* login_btn;
	Sprite* register_btn;
	TextField* pName;
	TextField* pPassword;
	CREATE_FUNC(CLoginScene);
};
#endif 

