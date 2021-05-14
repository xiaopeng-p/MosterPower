#ifndef _ANIMATION_MANAGER_H_
#define _ANIMATION_MANAGER_H_

#include "Header.h"
USING_NS_CC;

class AnimationMgr 
{
public:
	AnimationMgr();
	~AnimationMgr();

	//初始化动画模版缓存表
	bool initAnimationMap();

	static AnimationMgr* getInstance();
	//根据名字得到一个动画模板
	Animation* getAnimation(int nkey);

	//创建一个动画实例
	Animate* createAnimate(int nkey);

	//停止一个动画
	void stopAnimate(int nKey);
	//创建一个动画实例
	Animate* createAnimate(const char* pkey);

protected:
	static AnimationMgr* m_pInstance;
	//加载勇士行走动画模版
	Animation* createHeroMovingAnimationByDirection(HeroDirection direction);
	Animation* createFightAnimation();
	Animation* createNPCAnimation();
	
};

//定义动画管理器实例的别名
//#define sAnimationMgr AnimationMgr::getInstance()

#endif
