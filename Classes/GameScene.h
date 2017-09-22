#pragma once
#include "layers_scenes_transitions_nodes\ccscene.h"
#include "cocos2d.h"
#include "GameLayer.h"
#include "HudLayer.h"
USING_NS_CC;

class GameScene : public cocos2d::CCScene
{
public:
	GameScene(void);
	~GameScene(void);

	virtual bool init();

	GameLayer* _gameLayer;
	HudLayer* _hudLayer ;

	CREATE_FUNC(GameScene);
};

