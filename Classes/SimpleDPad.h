#pragma once
#include "sprite_nodes\ccsprite.h"
#include "cocos2d.h"

USING_NS_CC;

class SimpleDPad;


class SimpleDPadDelegate   //委托模式：委托类
{
public:
	virtual void didChangeDirectionTo(SimpleDPad* simpleDPad,CCPoint direction)=0; //纯虚函数
	virtual void isHoldingDirector(SimpleDPad* simpleDPad,CCPoint direction)=0;
	virtual void simpleDPadTouchEnded(SimpleDPad* simpleDPad)=0;
protected:
private:
};

class SimpleDPad : public cocos2d::CCSprite,public cocos2d::CCTargetedTouchDelegate
{
public:
	SimpleDPad(void);
	~SimpleDPad(void);

	static SimpleDPad* dPadWithFile(cocos2d::CCString* fileName,float radius);
	bool initWithFile(cocos2d::CCString* fileName,float radius);

	void onExit(); 
	void onEnterTransitionDidFinish();  

	void update(float dt); //update 定时器

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void updateDirectionForTouchLocation(CCPoint Location);  //根据坐标算方向向量

	SimpleDPadDelegate* _delegate;  //委托

	bool _isHold;
	float _radius;
	CCPoint _direction;  //方向向量

	void setDelegate(SimpleDPadDelegate* _delegate);
	
};

