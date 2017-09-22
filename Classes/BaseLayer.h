#pragma once
#include "layers_scenes_transitions_nodes\cclayer.h"
#include "cocos2d.h"

USING_NS_CC;
class BaseLayer : public CCLayer
{
public:
	BaseLayer(void);
	~BaseLayer(void);
	
	CCScene* welcomeScene;

	virtual bool init();
	CREATE_FUNC(BaseLayer);

	cocos2d::CCSize getWinSize();//得到当前可视窗口的大小
	cocos2d::CCPoint getWinOrigin();//得到当前可视窗口的起始点
	cocos2d::CCPoint getWinCenter();// 得到屏幕正中间的点
	cocos2d::CCPoint converSpritRel(float x, float y);
};

