#include "SimpleDPad.h"
#include "GameScene.h"
#include "HudLayer.h"

SimpleDPad::SimpleDPad(void)
{
	this->_delegate = NULL;
}


SimpleDPad::~SimpleDPad(void)
{
}

SimpleDPad* SimpleDPad::dPadWithFile(cocos2d::CCString* fileName,float radius){
	SimpleDPad* pRet = new SimpleDPad();
	if(pRet && pRet->initWithFile(fileName,radius)){
		return pRet;
	}else{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool SimpleDPad::initWithFile(cocos2d::CCString* fileName,float radius){
	if(!CCSprite::initWithFile(fileName->getCString())){
		return false;
	}
	this->_radius = radius;
	this->_direction = CCPointZero;
	this->_isHold = false;
	this->scheduleUpdate(); //启动update定时器，每隔一帧

	return true;
}

void SimpleDPad::onEnterTransitionDidFinish(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true); //注册监听
}

void SimpleDPad::onExit(){
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this); //注销监听
}

void SimpleDPad::update(float dt){
	if(this->_isHold){
		this->_delegate->isHoldingDirector(this,this->_direction);
	}
}

bool SimpleDPad::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	float distanceSQ = ccpDistanceSQ(pTouch->getLocation(),this->getPosition());
	if(distanceSQ <= (this->_radius * this->_radius)){
		this->_isHold = true;
		this->updateDirectionForTouchLocation(pTouch->getLocation());
		return true;
	}
	return false;
} 

void SimpleDPad::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	this->ccTouchBegan(pTouch,pEvent);
}

void SimpleDPad::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
	this->_isHold = false;
	this->_direction = CCPointZero;
	this->_delegate->simpleDPadTouchEnded(this);
}

void SimpleDPad::updateDirectionForTouchLocation(CCPoint Location){
	float radians = ccpToAngle(ccpSub(Location,this->getPosition()));  //计算弧度
	float degrees = -1*CC_RADIANS_TO_DEGREES(radians);  //计算角度

	if(degrees >= -22.5 && degrees < 22.5){
		this->_direction = ccp(1,0);
	}else if(degrees >= 22.5 && degrees < 67.5){
		this->_direction = ccp(1,-1);
	}else if(degrees >= 67.5 && degrees < 112.5){
		this->_direction = ccp(0,-1);
	}else if(degrees >= 112.5 && degrees < 157.5){
		this->_direction = ccp(-1,-1);
	}else if(degrees >= 157.5 || degrees < -157.5){
		this->_direction = ccp(-1,0);
	}else if(degrees >= -157.5 && degrees < -112.5){
		this->_direction = ccp(-1,1);
	}else if(degrees >= -112.5 && degrees < -67.5){
		this->_direction = ccp(0,1);
	}else if(degrees >= -67.5 && degrees < -22.5){
		this->_direction = ccp(1,1);
	}

	if(this->_delegate == NULL){
		CCLOG("-->");
	}
	this->_delegate->didChangeDirectionTo(this,this->_direction);
}  

void SimpleDPad::setDelegate(SimpleDPadDelegate* _delegate){
	this->_delegate = _delegate;
}