#pragma once
#include "sprite_nodes\ccsprite.h"
#include "cocos2d.h"

USING_NS_CC;

//ö��
typedef enum _ActionState{  
	kActionStateNone = 0,
	kActionStateIdel,
	kActionStateAttack,
	kActionStateWalk,
	kActionStateHurt,
	kActionStateDead
}ActionState;     //typedef �����滻

typedef struct{
	cocos2d::CCRect actual;
	cocos2d::CCRect original;
}BoundingBox;

class ActionSprite : public cocos2d::CCSprite
{
public:
	ActionSprite(void);
	~ActionSprite(void);
	virtual bool init();

	CREATE_FUNC(ActionSprite);

	//���ֶ����ķ���
	void idle(); //����
	void attack(); //����
	void hurtWithDamage(float damage); //����
	virtual void dead(); //����
	void walkWithDirection(cocos2d::CCPoint); //����
	
	void updateDirection(float dt);

	BoundingBox createBoundingBoxWithOrigin(CCPoint origin,CCSize size);
	void transformBoxes();
	void setPosition(CCPoint point);

	//����
	cocos2d::CCAction* _idleAction;
	cocos2d::CCAction* _attackAction;
	cocos2d::CCAction* _hurtAction;
	cocos2d::CCAction* _deadAction;
	cocos2d::CCAction* _walkAction;

	
	ActionState _actionState;//��ǰ״̬

	float walkSpeed; //��������

	float damage; //������

	float hurtPoint; //����ֵ

	cocos2d::CCPoint velocity; // �ƶ�����

	cocos2d::CCPoint disertDirection; //��һλ��

	float centerToSide; //�������ĵ��ߵľ���
	float centerToBottom; //�������ĵ��ײ�����

	BoundingBox _hitBox;
	BoundingBox _attackBox;
};

