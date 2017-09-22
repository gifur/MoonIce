#pragma once
#include "layers_scenes_transitions_nodes\ccscene.h"
#include "WelcomeLayer.h"

USING_NS_CC;

class WelcomeScene : public CCScene
{
public:
	WelcomeScene(void);
	~WelcomeScene(void);

	virtual bool init();
	WelcomeLayer* welcomeLayer;
	CREATE_FUNC(WelcomeScene);
};

