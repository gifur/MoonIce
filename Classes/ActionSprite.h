#pragma once
#include "sprite_nodes\ccsprite.h"
#include "cocos2d.h"

USING_NS_CC;

//枚举
typedef enum _ActionState{  
	kActionStateNone = 0,
	kActionStateIdel,
	kActionStateAttack,
	kActionStateWalk,
	kActionStateHurt,
	kActionStateDead
}ActionState;     //typedef 类型替换

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

	//五种动作的方法
	void idle(); //空闲
	void attack(); //攻击
	void hurtWithDamage(float damage); //受伤
	virtual void dead(); //死亡
	void walkWithDirection(cocos2d::CCPoint); //行走
	
	void updateDirection(float dt);

	BoundingBox createBoundingBoxWithOrigin(CCPoint origin,CCSize size);
	void transformBoxes();
	void setPosition(CCPoint point);

	//动作
	cocos2d::CCAction* _idleAction;
	cocos2d::CCAction* _attackAction;
	cocos2d::CCAction* _hurtAction;
	cocos2d::CCAction* _deadAction;
	cocos2d::CCAction* _walkAction;

	
	ActionState _actionState;//当前状态

	float walkSpeed; //行走速率

	float damage; //攻击力

	float hurtPoint; //生命值

	cocos2d::CCPoint velocity; // 移动方向

	cocos2d::CCPoint disertDirection; //下一位置

	float centerToSide; //精灵中心到边的距离
	float centerToBottom; //精灵中心到底部距离

	BoundingBox _hitBox;
	BoundingBox _attackBox;
};

