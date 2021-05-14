#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__

typedef enum 
{
	E_STATE_DOWN =  0,//���·���
	E_STATE_LEFT = 1,//������
	E_STATE_RIGHT= 2,//���ҷ���
	E_STATE_UP = 3,//���Ϸ���
	E_STATE_NORMAL,//ս��״̬
} HeroDirection;//��ʿ����

typedef enum
{
	E_COLIC_NONE = 1,//����ͨ��
	E_COLIC_WALL,//ǽ
	E_COLIC_ENEMY,//����
	E_COLIC_ITEM,//��Ʒ
	E_COLIC_DOOR,//��
	E_COLIC_NPC,//npc
	E_COLIC_TELEPORT,//���͵�
} CollisionType;//��ײ����

typedef enum
{
	E_KEY_DOWN = 0,//�������߶���
	E_KEY_LEFT,//�������߶���
	E_KEY_RIGHT,//�������߶���
	E_KEY_UP,//�������߶���
	E_KEY_FIGHT,//���⶯��
} AnimationKey;//����ģ���ֵ

enum
{
	E_ORDER_MAP = 0,//��ͼ��zOrder
	E_ORDER_NPC,//NPC��zOrder
	E_ORDER_TELEPORT,//�����ŵ�zOrder
	E_ORDER_HERO,//��ʿ�����zOrder
	E_ORDER_TALK,//�Ի����zOrder
	E_ORDER_TIP//��ʾ��Ϣ��zOrder
	
};//GameLayer�и����ֵ���ʾzOrder��tag

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