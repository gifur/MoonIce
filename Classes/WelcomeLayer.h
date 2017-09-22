#pragma once
#include "Baselayer.h"
class WelcomeLayer : public BaseLayer
{
public:
	WelcomeLayer(void);
	~WelcomeLayer(void);

	virtual bool init();
	void setMenuView();
	CCScene* scene();

	void goLoading(CCObject* pSender);

	CREATE_FUNC(WelcomeLayer);
};

