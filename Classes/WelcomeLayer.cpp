#include "WelcomeLayer.h"
#include "LoadLayer.h"

USING_NS_CC;

WelcomeLayer::WelcomeLayer(void)
{
}


WelcomeLayer::~WelcomeLayer(void)
{
}

bool WelcomeLayer::init(){
	if(!BaseLayer::init()){
		return false;
	}
	CCSprite* sprite = CCSprite::create("gmbg/welcomebg.png");
	sprite->setPosition(getWinCenter());
	this->addChild(sprite);
	this->setMenuView();
	return true;
}

void WelcomeLayer::setMenuView(){
	CCSprite* sprite_up = CCSprite::create("gmme/star_up.png");
	CCSprite* sprite_down = CCSprite::create("gmme/star_down.png");
	CCMenuItemSprite* pStar=CCMenuItemSprite::create(sprite_up,sprite_down,NULL,this,menu_selector(WelcomeLayer::goLoading));
	pStar->setPosition(ccp(getWinSize().width*0.86f,getWinSize().height*0.75f));

	CCMenu* pMenu=CCMenu::create(pStar,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,2);
}

CCScene* WelcomeLayer::scene(){
	CCScene* scene=CCScene::create();
	LoadLayer* layer=LoadLayer::create();
	scene->addChild(layer);
	return scene;
}
void WelcomeLayer::goLoading(CCObject* pSender){
	CCScene* se=this->scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(0.5,se));

}

