#include "BaseLayer.h"


BaseLayer::BaseLayer(void)
{
}


BaseLayer::~BaseLayer(void)
{
}

bool BaseLayer::init(){
	if(!CCLayer::init()){
		return false;
	}
	return true;
}

CCSize BaseLayer::getWinSize(){
	return CCDirector::sharedDirector()->getVisibleSize();
}

CCPoint BaseLayer::getWinOrigin(){
	return CCDirector::sharedDirector()->getVisibleOrigin();
}

CCPoint BaseLayer::getWinCenter(){
	return	ccp(getWinSize().width/2+getWinOrigin().x,getWinSize().height/2+getWinOrigin().y);
}

CCPoint BaseLayer::converSpritRel(float x, float y){
	return ccp(x+getWinOrigin().x,y+getWinOrigin().y);
}