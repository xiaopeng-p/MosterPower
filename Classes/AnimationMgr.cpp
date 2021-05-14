#include "AnimationMgr.h"

AnimationMgr* AnimationMgr::m_pInstance = nullptr;

AnimationMgr::AnimationMgr()
{
	
}

AnimationMgr::~AnimationMgr()
{
}

AnimationMgr* AnimationMgr::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new AnimationMgr();
	}
	return m_pInstance;
}

bool AnimationMgr::initAnimationMap()
{
	char temp[20];
	//加载勇士向下走的动画
	sprintf(temp, "%d", E_KEY_DOWN);
	AnimationCache::getInstance()->addAnimation(createHeroMovingAnimationByDirection(E_STATE_DOWN), temp);

	//加载勇士向右走的动画
	sprintf(temp, "%d", E_KEY_RIGHT);
	AnimationCache::getInstance()->addAnimation(createHeroMovingAnimationByDirection(E_STATE_RIGHT), temp);

	//加载勇士向左走的动画
	sprintf(temp, "%d", E_KEY_LEFT);
	AnimationCache::getInstance()->addAnimation(createHeroMovingAnimationByDirection(E_STATE_LEFT), temp);

	//加载勇士向上走的动画
	sprintf(temp, "%d", E_KEY_UP);
	AnimationCache::getInstance()->addAnimation(createHeroMovingAnimationByDirection(E_STATE_UP), temp);

	//加载战斗动画
	sprintf(temp, "%d", E_KEY_FIGHT);
	AnimationCache::getInstance()->addAnimation(createFightAnimation(), temp);

	//加载NPC动画
	AnimationCache::getInstance()->addAnimation(createNPCAnimation(), "npc0");

	return true;


}

Animation* AnimationMgr::getAnimation(int nkey)
{
	char temp[20];
	sprintf(temp, "%d", nkey);
	return AnimationCache::getInstance()->getAnimation(temp);
}

Animate* AnimationMgr::createAnimate(int nkey)
{
	//获取指定动画模版
	Animation* anim = getAnimation(nkey);

	if (anim == NULL)
	{
		return NULL;
	}

	//根据动画模版生成一个动画实例
	return Animate::create(anim);

}

void AnimationMgr::stopAnimate(int nKey)
{
	
}

Animate* AnimationMgr::createAnimate(const char* pkey)
{
	//获取指定动画模版
	Animation* anim = AnimationCache::getInstance()->getAnimation(pkey);

	if (anim == NULL)
	{
		return NULL;
	}

	//根据动画模版生成一个动画实例
	return Animate::create(anim);

}

Animation* AnimationMgr::createHeroMovingAnimationByDirection(HeroDirection direction)
{
	Texture2D* heroTexture = Director::getInstance()->getTextureCache()->addImage("image/hero.png");
	//第二个参数表示显示区域的x, y, width, height，根据direction来确定显示的y坐标	拿到所有英雄单张图片
	SpriteFrame* frame0 = SpriteFrame::createWithTexture(heroTexture, Rect(32 * 0, 32 * direction, 32, 32));
	SpriteFrame* frame1 = SpriteFrame::createWithTexture(heroTexture, Rect(32 * 1, 32 * direction, 32, 32));
	SpriteFrame* frame2 = SpriteFrame::createWithTexture(heroTexture, Rect(32 * 2, 32 * direction, 32, 32));
	SpriteFrame* frame3 = SpriteFrame::createWithTexture(heroTexture, Rect(32 * 3, 32 * direction, 32, 32));

	Vector<SpriteFrame*> animFrames;

	animFrames.pushBack(frame0);
	animFrames.pushBack(frame1);
	animFrames.pushBack(frame2);
	animFrames.pushBack(frame3);

	//0.05f表示每帧动画间的间隔
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.05f);

	return animation;


}

//创建战斗动画
Animation* AnimationMgr::createFightAnimation()
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("image/sword.png");

	//定义每帧的序号
	int fightAnim[] =
	{
		4,6,8,10,13,15,17,19,20,22
	};

	Vector<SpriteFrame*> animFrames;

	int x, y;
	for (int i = 0; i < 10; i++)
	{
		//计算每帧在整个纹理中的偏移量
		x = fightAnim[i] % 5 - 1;
		y = fightAnim[i] / 5;

		SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(192 * x, 192 * y, 192, 192));
		
		//第17和19帧在y方向上有-8的偏移
		if (fightAnim[i] == 17 || fightAnim[i] == 19)
		{
			frame->setOffsetInPixels(Point(0, -8));
		}

		animFrames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	return animation;


}

Animation* AnimationMgr::createNPCAnimation()
{
	Texture2D* heroTexture = Director::getInstance()->getTextureCache()->addImage("image/npc.png");

	//第二个参数表示显示区域的x, y, width, height，根据direction来确定显示的y坐标
	SpriteFrame* frame0 = SpriteFrame::createWithTexture(heroTexture, Rect(32 * 0, 0, 32, 32));
	SpriteFrame* frame1 = SpriteFrame::createWithTexture(heroTexture, Rect(32 * 1, 0, 32, 32));
	SpriteFrame* frame2 = SpriteFrame::createWithTexture(heroTexture, Rect(32 * 2, 0, 32, 32));
	SpriteFrame* frame3 = SpriteFrame::createWithTexture(heroTexture, Rect(32 * 3, 0, 32, 32));

	Vector<SpriteFrame*> animFrames;

	animFrames.pushBack(frame0);
	animFrames.pushBack(frame1);
	animFrames.pushBack(frame2);
	animFrames.pushBack(frame3);

	//0.05f表示每帧动画间的间隔
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);

	return animation;

}
