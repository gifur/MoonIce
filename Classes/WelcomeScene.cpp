#include "WelcomeScene.h"


WelcomeScene::WelcomeScene(void)
{
	this->welcomeLayer = NULL;
}


WelcomeScene::~WelcomeScene(void)
{
}

bool WelcomeScene::init(){
	if(!CCScene::init()){
		return false;
	}
	this->welcomeLayer = WelcomeLayer::create();
	this->addChild(this->welcomeLayer);
	return true;
}