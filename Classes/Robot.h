#pragma once
#include "actionsprite.h"
class Robot : public ActionSprite
{
public:
	Robot(void);
	~Robot(void);

	virtual bool init();
	virtual void dead();
	float _nextDecisionTime; 

	CREATE_FUNC(Robot);
};

