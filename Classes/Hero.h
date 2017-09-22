#pragma once
#include "actionsprite.h"
class Hero : public ActionSprite
{
public:
	Hero(void);
	~Hero(void);

	virtual bool init();
	virtual void dead();

	CREATE_FUNC(Hero);
};

