#pragma once
#include "layers_scenes_transitions_nodes\cclayer.h"
#include "cocos2d.h"
#include "Hero.h"
#include "SimpleDPad.h"
#include "Robot.h"
#include "HudLayer.h"

USING_NS_CC;

class GameLayer : public cocos2d::CCLayer, public SimpleDPadDelegate
{
public:
	GameLayer(void);
	~GameLayer(void);

	virtual bool init();
	virtual void initTiledMap();
	cocos2d::CCSpriteBatchNode* _actor; //CCSpriteBatchNode批处理，一次性渲染精灵批处理节点

	virtual void registerWithTouchDispatcher(void);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	//virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	//virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	void didChangeDirectionTo(SimpleDPad* simpleDPad,CCPoint direction); 
	void isHoldingDirector(SimpleDPad* simpleDPad,CCPoint direction);
	void simpleDPadTouchEnded(SimpleDPad* simpleDPad);

	CCTMXTiledMap* pTiledMap;

	HudLayer* _hudLayer;
	Hero* hero;
	virtual void initHero();

	CCArray* robots;
	void initRobot();

	void update(float dt);

	void updateRobot(float dt);

	void endGame();
	void startGame(CCObject *pSence);

	CREATE_FUNC(GameLayer);
};

