#pragma once
#include "layers_scenes_transitions_nodes\cclayer.h"
#include "cocos2d.h"
#include "SimpleDPad.h"

class HudLayer : public cocos2d::CCLayer
{
public:
	HudLayer(void);
	~HudLayer(void);

	virtual bool init();

	SimpleDPad* _simpleDPad;

	void update(float dt);

	CREATE_FUNC(HudLayer);
};

