#include "Robot.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Robot::Robot(void)
{
	this->_nextDecisionTime = 0;
}


Robot::~Robot(void)
{
}

bool Robot::init(){
	if(!ActionSprite::initWithSpriteFrameName("robot_idle_00.png")){
		return false;
	}
	
	int i;

	CCArray* idleFrame = CCArray::create();  //创建空闲动作的帧数组
	idleFrame->retain();   //防止函数返回时数组被释放

	for(i = 0;i < 5;i++ ){
		CCSpriteFrame* _frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("robot_idle_%02d.png",i)->getCString());    //从内存中获得精灵帧
		idleFrame->addObject(_frame);
	}

	CCAnimation* idleAnimation = CCAnimation::createWithSpriteFrames(idleFrame,0.1f);
	CCAnimate* idleAnimate = CCAnimate::create(idleAnimation);
	this->_idleAction = CCRepeatForever::create(idleAnimate);
	this->_idleAction->retain();

	CCArray* attackFrame = CCArray::create();
	attackFrame->retain();

	for(i = 0;i < 5;i++ ){
		CCSpriteFrame* _frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("robot_attack_%02d.png",i)->getCString());    //从内存中获得精灵帧
		attackFrame->addObject(_frame);
	}

	CCAnimation* attackAnimation = CCAnimation::createWithSpriteFrames(attackFrame,0.05f);
	CCAnimate* attackAnimate = CCAnimate::create(attackAnimation);
	this->_attackAction = CCSequence::create(attackAnimate,CCCallFunc::create(this,callfunc_selector(ActionSprite::idle)),NULL);
	this->_attackAction->retain();

	//行走动作
	CCArray* walkFrame = CCArray::createWithCapacity(8);
	walkFrame->retain();

	for(i=0;i<6;i++){
		CCSpriteFrame* _frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("robot_walk_%02d.png",i)->getCString());
		walkFrame->addObject(_frame);
	}

	CCAnimation* walkAnimation = CCAnimation::createWithSpriteFrames(walkFrame,0.1f);
	CCAnimate* walkAnimate = CCAnimate::create(walkAnimation);
	this->_walkAction =  CCRepeatForever::create(walkAnimate);
	this->_walkAction->retain();

	//受伤动作
	CCArray* hurtFrame = CCArray::createWithCapacity(3);
	hurtFrame->retain();

	for(i=0;i<3;i++){
		CCSpriteFrame* _frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("robot_hurt_%02d.png",i)->getCString());
		hurtFrame->addObject(_frame);
	}

	CCAnimation*  hurtAnimation = CCAnimation::createWithSpriteFrames( hurtFrame,0.1f);
	CCAnimate*  hurtAnimate = CCAnimate::create( hurtAnimation);
	this->_hurtAction =  CCSequence::create(hurtAnimate,CCCallFunc::create(this,callfunc_selector(ActionSprite::idle)),NULL);
	this->_hurtAction->retain();

	//死亡动作
	CCArray* deadFrame = CCArray::createWithCapacity(5);
	deadFrame->retain();

	for(i=0;i<5;i++){
		CCSpriteFrame* _frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("robot_knockout_%02d.png",i)->getCString());
		deadFrame->addObject(_frame);
	}

	CCAnimation*  deadAnimation = CCAnimation::createWithSpriteFrames( deadFrame,0.1f);
	CCAnimate*  deadAnimate = CCAnimate::create( deadAnimation);
	this->_deadAction =  CCSequence::create(deadAnimate,CCBlink::create(1.0,10.0),NULL);
	this->_deadAction->retain();

	this->centerToSide = 39.0f;
	this->centerToBottom = 29.f;
	this->hurtPoint = 100;
	this->damage = 20;
	this->walkSpeed = 60;

	this->_hitBox = this->createBoundingBoxWithOrigin(ccp(-this->centerToSide,-this->centerToBottom),CCSizeMake(this->centerToSide*2,this->centerToBottom*2));
	this->_attackBox = this->createBoundingBoxWithOrigin(ccp(this->centerToSide,-5),CCSizeMake(25,20));

	return true;
}

void Robot::dead(){
	ActionSprite::dead();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pd_herodeath.wav");
}