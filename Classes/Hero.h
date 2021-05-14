#ifndef __HERO_H__
#define __HERO_H__
#include "cocos2d.h"
#include "TelePort.h"
#include "Entity.h"
#include "GameConstants.h"
USING_NS_CC;
using namespace std;
class CTeleport;

//��ʿ��̳���CCNode
class CHero : public Node,public CEntity
{
public:
	CHero();
	~CHero();

	//��ʼ������
	virtual bool init();

	CREATE_FUNC(CHero);

	//����ʿ��ָ�������ƶ�һ��
	void move(HeroDirection direction);

	void updataSprite();
	//��ʿ�ı����������洢Կ��
	int m_arrBag[3] = {};
	void addAck(int nAdd);
	void addHp(int nAdd);
	void addDef(int nAdd);
	void addMoney(int nAdd);
	//��ʱ����Ŀ���Tilemap����
	CC_SYNTHESIZE(Point, m_targetTileCoord, targetTileCoord);
private:
	//������ʾ��ʿ����ľ���
	Sprite* m_pHero;

	
	Texture2D* pButtonHero;

	//��ʱ����Ŀ���cocos2d-x����
	Point m_targetPosition;

	//��ʶ��ʿ�Ƿ���ս��״̬
	bool isHeroFighting;

	//��ʶ��ʿ�Ƿ��ڿ���״̬
	bool isDoorOpening;

	//��ʱ��������ʼ��ͼ��ID
	int m_nTargetDoorGID;

	//��ʾս�������ľ���
	Sprite* m_pFight;

	//��ʿ�Ĺ�����
	/*CC_SYNTHESIZE(int, m_nAck, Ack);
	CC_SYNTHESIZE(int,m_nGrade,Grade);
	CC_SYNTHESIZE(int, m_nDef, Def);
	CC_SYNTHESIZE(int, m_nHp, Hp);
	CC_SYNTHESIZE(int, m_nMoney,Money);
	CC_SYNTHESIZE(int, m_nExp, Exp);
	CC_SYNTHESIZE(int, m_nLvExp,LvExp);
	CC_SYNTHESIZE(int, m_nHpMax, HpMax);*/

	//��ʶ��ʿ�Ƿ����ƶ�״̬
	CC_SYNTHESIZE(bool, isHeroMoving, HeroMoving);
private:
	//ս����ɺ�Ļص�����
	void onFightDone(Node* pTarget);
	
	//��ײ��ⷽ��
	CollisionType checkCollision(Point heroPosition);

	//�ƶ���ɺ�Ļص�����
	void onMoveDone(Node* pTarget, void* data);

	//���¿��Ŷ���
	void updateOpenDoorAnimation(float time);

	//������ʿ����
	void setFaceDirection(HeroDirection direction);

	//��ʼս���߼�
	void fight(int nID);

	//ʰȡ��Ʒ
	void pickUpItem(const char* tip);

	//����
	void openDoor(int nTargetDoorGID);

	//��NPC����
	void actWithNPC();

	//����
	void doTeleport(CTeleport* pTeleport);
};

#endif
