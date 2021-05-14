#ifndef __MAINMENU_H__
#define __MAINMENU_H__
#include "cocos2d.h"

USING_NS_CC;
class CMainMenu :public Scene
{
public:
	CMainMenu();
	~CMainMenu();

	//初始化函数
	virtual bool init();
	//添加背景
	void addBg();
	//给按钮添加文字
	void addLabelAndEvent();

	CREATE_FUNC(CMainMenu);
};
#endif // !__MAINMENU_SCENE_H__

