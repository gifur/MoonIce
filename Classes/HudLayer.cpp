#include "HudLayer.h"
#include "GameScene.h"

USING_NS_CC;

HudLayer::HudLayer(void)
{
	this->_simpleDPad = NULL;
}


HudLayer::~HudLayer(void)
{
}

bool HudLayer::init(){
	if(!CCLayer::init()){
		return false;
	}
	this->scheduleUpdate();
	this->_simpleDPad = SimpleDPad::dPadWithFile(CCString::create("pd_dpad.png"),64.0);
	this->_simpleDPad->setPosition(ccp(64,64));
	this->_simpleDPad->setOpacity(100); //ÉèÖÃÍ¸Ã÷¶È
	this->addChild(this->_simpleDPad);
	return true;
}

void HudLayer::update(float dt){
	GameScene* _gameSence =(GameScene* )this->getParent();
	if(_gameSence == NULL){
		CCLOG("_gameSence------->");
		return;
	}else{
		this->unscheduleUpdate();

		this->_simpleDPad->_delegate = _gameSence->_gameLayer;
		if(this->_simpleDPad->_delegate != NULL){
			this->_simpleDPad->setDelegate(this->_simpleDPad->_delegate);
		}
		
	}
}