#ifndef _ANIMATION_MANAGER_H_
#define _ANIMATION_MANAGER_H_

#include "Header.h"
USING_NS_CC;

class AnimationMgr 
{
public:
	AnimationMgr();
	~AnimationMgr();

	//��ʼ������ģ�滺���
	bool initAnimationMap();

	static AnimationMgr* getInstance();
	//�������ֵõ�һ������ģ��
	Animation* getAnimation(int nkey);

	//����һ������ʵ��
	Animate* createAnimate(int nkey);

	//ֹͣһ������
	void stopAnimate(int nKey);
	//����һ������ʵ��
	Animate* createAnimate(const char* pkey);

protected:
	static AnimationMgr* m_pInstance;
	//������ʿ���߶���ģ��
	Animation* createHeroMovingAnimationByDirection(HeroDirection direction);
	Animation* createFightAnimation();
	Animation* createNPCAnimation();
	
};

//���嶯��������ʵ���ı���
//#define sAnimationMgr AnimationMgr::getInstance()

#endif
