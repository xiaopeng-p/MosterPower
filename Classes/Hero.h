#ifndef __HERO_H__
#define __HERO_H__
#include "cocos2d.h"
#include "TelePort.h"
#include "Entity.h"
#include "GameConstants.h"
USING_NS_CC;
using namespace std;
class CTeleport;

//勇士类继承自CCNode
class CHero : public Node,public CEntity
{
public:
	CHero();
	~CHero();

	//初始化方法
	virtual bool init();

	CREATE_FUNC(CHero);

	//让勇士向指定方向移动一格
	void move(HeroDirection direction);

	void updataSprite();
	//勇士的背包，用来存储钥匙
	int m_arrBag[3] = {};
	void addAck(int nAdd);
	void addHp(int nAdd);
	void addDef(int nAdd);
	void addMoney(int nAdd);
	//临时保存目标的Tilemap坐标
	CC_SYNTHESIZE(Point, m_targetTileCoord, targetTileCoord);
private:
	//用于显示勇士形象的精灵
	Sprite* m_pHero;

	
	Texture2D* pButtonHero;

	//临时保存目标的cocos2d-x坐标
	Point m_targetPosition;

	//标识勇士是否在战斗状态
	bool isHeroFighting;

	//标识勇士是否在开门状态
	bool isDoorOpening;

	//临时保存门起始的图块ID
	int m_nTargetDoorGID;

	//显示战斗动画的精灵
	Sprite* m_pFight;

	//勇士的攻击力
	/*CC_SYNTHESIZE(int, m_nAck, Ack);
	CC_SYNTHESIZE(int,m_nGrade,Grade);
	CC_SYNTHESIZE(int, m_nDef, Def);
	CC_SYNTHESIZE(int, m_nHp, Hp);
	CC_SYNTHESIZE(int, m_nMoney,Money);
	CC_SYNTHESIZE(int, m_nExp, Exp);
	CC_SYNTHESIZE(int, m_nLvExp,LvExp);
	CC_SYNTHESIZE(int, m_nHpMax, HpMax);*/

	//标识勇士是否在移动状态
	CC_SYNTHESIZE(bool, isHeroMoving, HeroMoving);
private:
	//战斗完成后的回调函数
	void onFightDone(Node* pTarget);
	
	//碰撞检测方法
	CollisionType checkCollision(Point heroPosition);

	//移动完成后的回调函数
	void onMoveDone(Node* pTarget, void* data);

	//更新开门动画
	void updateOpenDoorAnimation(float time);

	//设置勇士朝向
	void setFaceDirection(HeroDirection direction);

	//开始战斗逻辑
	void fight(int nID);

	//拾取物品
	void pickUpItem(const char* tip);

	//开门
	void openDoor(int nTargetDoorGID);

	//对NPC交互
	void actWithNPC();

	//传送
	void doTeleport(CTeleport* pTeleport);
};

#endif
