#include "LoadLayer.h"


LoadLayer::LoadLayer(void)
{
	this->loadingNum=0;
	this->totalNum=33;
	this->gameScene = NULL;
}


LoadLayer::~LoadLayer(void)
{
}

bool LoadLayer::init(){
	bool isRet=false;
	do 
	{
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!this->setUpdateView());


		CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/gamebg.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 欢迎界面 背景图片

		CCTextureCache::sharedTextureCache()->addImageAsync("game/weapon.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 弓弩武器
		CCTextureCache::sharedTextureCache()->addImageAsync("game/wq0.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  弓箭子弹


		CCTextureCache::sharedTextureCache()->addImageAsync("game/monster_blood.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 血条背景
		CCTextureCache::sharedTextureCache()->addImageAsync("game/monster_blood_frame.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  血条


		CCTextureCache::sharedTextureCache()->addImageAsync("monster/dutu.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 赌徒怪物

		CCTextureCache::sharedTextureCache()->addImageAsync("game/zcblood.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 主城血条
		CCTextureCache::sharedTextureCache()->addImageAsync("game/magic.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  主城魔法条
		CCTextureCache::sharedTextureCache()->addImageAsync("game/panelblood.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  主城血条和魔法条的背景



		CCTextureCache::sharedTextureCache()->addImageAsync("game/jnl.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 魔法阵背景图片
		CCTextureCache::sharedTextureCache()->addImageAsync("game/jnzt.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 魔法阵CD 亮的图片


		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/pause_button.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图是游戏暂停按钮

		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/btn_home_down.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图是游戏家按钮
		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/btn_home_up.png",this,callfuncO_selector(LoadLayer::loadCallBack)); 
		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/btn_resume_down.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图是游戏继续按钮
		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/btn_resume_up.png",this,callfuncO_selector(LoadLayer::loadCallBack)); 
		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/btn_retry_down.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图是游戏重新开始按钮
		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/btn_rety_up.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图是游戏暂停按钮


		CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/pause_bg.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图是游戏暂停按钮


		CCTextureCache::sharedTextureCache()->addImageAsync("game/MagicMatrix.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图魔法阵的图片

		CCTextureCache::sharedTextureCache()->addImageAsync("specia/ligtht.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图闪电特效图片
		CCTextureCache::sharedTextureCache()->addImageAsync("specia/diyu.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图地狱石块特效图片
		CCTextureCache::sharedTextureCache()->addImageAsync("specia/long.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图二龙戏珠特效图片
		CCTextureCache::sharedTextureCache()->addImageAsync("specia/thumbnails.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图特效缩略图片



		CCTextureCache::sharedTextureCache()->addImageAsync("game/woniubj.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图地蜗牛进度条背景图片
		CCTextureCache::sharedTextureCache()->addImageAsync("game/woniujd.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // 此图蜗牛进度条图片
		CCTextureCache::sharedTextureCache()->addImageAsync("game/woniu.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  此图蜗牛图片

		CCTextureCache::sharedTextureCache()->addImageAsync("game/stage_title.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  此图等级的背景图


		CCTextureCache::sharedTextureCache()->addImageAsync("game/gameover.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  此图游戏结束标题图
		CCTextureCache::sharedTextureCache()->addImageAsync("game/gameovertips.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  此图游戏结束提示图
		CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/gameoverbg.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  此图游戏结背景图

		CCTextureCache::sharedTextureCache()->addImageAsync("game/coin.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  此图金币图标

		CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/stats_bg.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  胜利界面背景图片

		CCTextureCache::sharedTextureCache()->addImageAsync("game/statstip.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  胜利界面提示按钮

		isRet=true;
	} while (0);
	return isRet;
}



void LoadLayer::loadCallBack(CCObject* ped){
	loadingNum++;	 
	CCProgressTimer* pt=(CCProgressTimer*)this->getChildByTag(1);
	float now=pt->getPercentage();
	pt->setPercentage(100.0/totalNum+now);
	if(loadingNum<totalNum){

	}else{
		pt->setPercentage(100);
		CCLOG("loading over");
		startGame();
	}
}

bool LoadLayer::setUpdateView(){
	bool isRet=false;
	do 
	{
		CCSprite* loadbg=CCSprite::create("gmbg/welcomebg.png");
		CC_BREAK_IF(!loadbg);
		loadbg->setPosition(getWinCenter());
		this->addChild(loadbg,0);
		// 设置进度条的背景图片 我们把他放到屏幕下方的1/5处	
		CCSprite* loadbackimg=CCSprite::create("gmbg/lodingbg.png");
		CC_BREAK_IF(!loadbackimg);	
		loadbackimg->setPosition(ccp(getWinSize().width/2+getWinOrigin().x,getWinSize().height/5+getWinOrigin().y));
		this->addChild(loadbackimg,1);

		// 添加进度条
		CCSprite* loadimg=CCSprite::create("gmbg/longding.png");
		CC_BREAK_IF(!loadimg);	
		CCProgressTimer* pt = CCProgressTimer::create(loadimg);
		pt->setType(kCCProgressTimerTypeBar);// 设置成横向的
		//可以看作是按矩形显示效果的进度条类型
		pt->setMidpoint(ccp(0,0)); 
		//  用来设定进度条横向前进的方向从左向右或是从右向左
		pt->setBarChangeRate(ccp(1,0));
		//重新设置锚点
		float tex=getWinSize().width/2+getWinOrigin().x;
		float tey=getWinSize().height/5+getWinOrigin().y-5;
		pt->setPosition(ccp(tex,tey));
		pt->setPercentage(0);
		this->addChild(pt,2,1);

		isRet=true;
	} while (0);
	return isRet;
}

void LoadLayer::startGame(){
	
	this->gameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(1,this->gameScene));
}