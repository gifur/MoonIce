#include "ActionSprite.h"
#include "SimpleAudioEngine.h"

#define random_range(low, high) (rand() % (high - low + 1)) + low
USING_NS_CC;


ActionSprite::ActionSprite(void)
{
}


ActionSprite::~ActionSprite(void)
{
}

bool ActionSprite::init(){
	if(!CCSprite::init()){
		return false;
	}
	this->_actionState = kActionStateNone;
	return true;
}

void ActionSprite::idle(){
	if(this->_actionState!=kActionStateIdel){
		this->stopAllActions();
		this->_actionState = kActionStateIdel;
		this->runAction(_idleAction);
		
	}
}

void ActionSprite::attack(){
	if(this->_actionState == kActionStateAttack || this->_actionState == kActionStateIdel || this->_actionState == kActionStateWalk){
		this->stopAllActions();
		this->_actionState = kActionStateAttack;
		this->runAction(_attackAction);

	}
}

void ActionSprite::walkWithDirection(cocos2d::CCPoint direction){
	if(this->_actionState == kActionStateIdel){
		this->stopAllActions();
		this->_actionState = kActionStateWalk;
		this->runAction(this->_walkAction);
	} 

	if(this->_actionState == kActionStateWalk){
		this->velocity = ccp(direction.x * this->walkSpeed,direction.y * this->walkSpeed);

		if(this->velocity.x >= 0){
			this->setScaleX(1.0);
		}else
			this->setScaleX(-1.0);
	}
}

void ActionSprite::hurtWithDamage(float damage){
	int randomSound = random_range(0, 1);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("pd_hit%d.wav", randomSound)->getCString());
	if(this->_actionState!= kActionStateDead){
		this->stopAllActions();
		this->_actionState = kActionStateHurt;
		this->runAction(this->_hurtAction);
		this->hurtPoint-=damage;
		if(this->hurtPoint<=0){
			this->dead();
		}
	}
}

void ActionSprite::dead(){
	this->stopAllActions();
	this->_actionState = kActionStateDead;
	this->runAction(this->_deadAction);
	this->hurtPoint = 0;
}

void ActionSprite::updateDirection(float dt){

	if(this->_actionState == kActionStateWalk){
		this->disertDirection = ccpAdd(this->getPosition(),ccpMult(this->velocity,dt));
	}
}

BoundingBox ActionSprite::createBoundingBoxWithOrigin(CCPoint origin,CCSize size){
	BoundingBox boundingBox ;
	boundingBox.original.origin = origin;
	boundingBox.original.size = size;
	boundingBox.actual.origin = ccpAdd(this->getPosition(),ccp(boundingBox.original.origin.x,boundingBox.original.origin.y));
	boundingBox.actual.size = size;

	return boundingBox;
}

void ActionSprite::transformBoxes(){
	this->_hitBox.actual.origin = ccpAdd(this->getPosition(),ccp(this->_hitBox.original.origin.x,this->_hitBox.original.origin.y));
	this->_attackBox.actual.origin = ccpAdd(this->getPosition(),ccp(this->_attackBox.original.origin.x + (this->getScaleX()==-1?(-this->_hitBox.original.size.width-this->_attackBox.original.size.width):0),this->_attackBox.original.origin.y));
}

void ActionSprite::setPosition(CCPoint point){
	CCSprite::setPosition(point);
	this->transformBoxes();
}