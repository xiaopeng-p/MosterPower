#ifndef __MAINMENU_H__
#define __MAINMENU_H__
#include "cocos2d.h"

USING_NS_CC;
class CMainMenu :public Scene
{
public:
	CMainMenu();
	~CMainMenu();

	//��ʼ������
	virtual bool init();
	//��ӱ���
	void addBg();
	//����ť�������
	void addLabelAndEvent();

	CREATE_FUNC(CMainMenu);
};
#endif // !__MAINMENU_SCENE_H__

