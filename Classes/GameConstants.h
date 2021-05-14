#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__

typedef enum 
{
	E_STATE_DOWN =  0,//向下方向
	E_STATE_LEFT = 1,//向左方向
	E_STATE_RIGHT= 2,//向右方向
	E_STATE_UP = 3,//向上方向
	E_STATE_NORMAL,//战立状态
} HeroDirection;//勇士方向

typedef enum
{
	E_COLIC_NONE = 1,//可以通行
	E_COLIC_WALL,//墙
	E_COLIC_ENEMY,//敌人
	E_COLIC_ITEM,//物品
	E_COLIC_DOOR,//门
	E_COLIC_NPC,//npc
	E_COLIC_TELEPORT,//传送点
} CollisionType;//碰撞类型

typedef enum
{
	E_KEY_DOWN = 0,//向下行走动画
	E_KEY_LEFT,//向左行走动画
	E_KEY_RIGHT,//向右行走动画
	E_KEY_UP,//向上行走动画
	E_KEY_FIGHT,//刀光动画
} AnimationKey;//动画模版键值

enum
{
	E_ORDER_MAP = 0,//地图的zOrder
	E_ORDER_NPC,//NPC的zOrder
	E_ORDER_TELEPORT,//传送门的zOrder
	E_ORDER_HERO,//勇士精灵的zOrder
	E_ORDER_TALK,//对话框的zOrder
	E_ORDER_TIP//提示信息的zOrder
	
};//GameLayer中各部分的显示zOrder及tag

enum 
{
	E_ORDER_GAMELAYER,
	E_ORDER_CONTROLLAYER,
	E_ORDER_FADELAYER,
};

enum
{
	E_KEY_RED,
	E_KEY_BLUE,
	E_KEY_YELLOW,
};

#endif