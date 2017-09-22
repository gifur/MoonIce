#include "GameScene.h"


GameScene::GameScene(void)
{
	this->_gameLayer = NULL;
	this->_hudLayer = NULL;
}


GameScene::~GameScene(void)
{
}



bool GameScene::init()
{
	bool bRet = true;
	do 
	{
		if(!CCScene::init())
		{ 
			bRet = false;
			return bRet;
		}
		this->_gameLayer = GameLayer::create();
		this->addChild(this->_gameLayer);

		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer);

	} while (0);
	
	return bRet;
}

