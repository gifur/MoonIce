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


		CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/gamebg.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ӭ���� ����ͼƬ

		CCTextureCache::sharedTextureCache()->addImageAsync("game/weapon.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��������
		CCTextureCache::sharedTextureCache()->addImageAsync("game/wq0.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  �����ӵ�


		CCTextureCache::sharedTextureCache()->addImageAsync("game/monster_blood.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // Ѫ������
		CCTextureCache::sharedTextureCache()->addImageAsync("game/monster_blood_frame.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  Ѫ��


		CCTextureCache::sharedTextureCache()->addImageAsync("monster/dutu.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͽ����

		CCTextureCache::sharedTextureCache()->addImageAsync("game/zcblood.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ����Ѫ��
		CCTextureCache::sharedTextureCache()->addImageAsync("game/magic.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  ����ħ����
		CCTextureCache::sharedTextureCache()->addImageAsync("game/panelblood.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  ����Ѫ����ħ�����ı���



		CCTextureCache::sharedTextureCache()->addImageAsync("game/jnl.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ħ���󱳾�ͼƬ
		CCTextureCache::sharedTextureCache()->addImageAsync("game/jnzt.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ħ����CD ����ͼƬ


		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/pause_button.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼ����Ϸ��ͣ��ť

		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/btn_home_down.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼ����Ϸ�Ұ�ť
		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/btn_home_up.png",this,callfuncO_selector(LoadLayer::loadCallBack)); 
		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/btn_resume_down.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼ����Ϸ������ť
		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/btn_resume_up.png",this,callfuncO_selector(LoadLayer::loadCallBack)); 
		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/btn_retry_down.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼ����Ϸ���¿�ʼ��ť
		CCTextureCache::sharedTextureCache()->addImageAsync("gmme/btn_rety_up.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼ����Ϸ��ͣ��ť


		CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/pause_bg.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼ����Ϸ��ͣ��ť


		CCTextureCache::sharedTextureCache()->addImageAsync("game/MagicMatrix.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼħ�����ͼƬ

		CCTextureCache::sharedTextureCache()->addImageAsync("specia/ligtht.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼ������ЧͼƬ
		CCTextureCache::sharedTextureCache()->addImageAsync("specia/diyu.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼ����ʯ����ЧͼƬ
		CCTextureCache::sharedTextureCache()->addImageAsync("specia/long.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼ����Ϸ����ЧͼƬ
		CCTextureCache::sharedTextureCache()->addImageAsync("specia/thumbnails.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼ��Ч����ͼƬ



		CCTextureCache::sharedTextureCache()->addImageAsync("game/woniubj.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼ����ţ����������ͼƬ
		CCTextureCache::sharedTextureCache()->addImageAsync("game/woniujd.png",this,callfuncO_selector(LoadLayer::loadCallBack)); // ��ͼ��ţ������ͼƬ
		CCTextureCache::sharedTextureCache()->addImageAsync("game/woniu.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  ��ͼ��ţͼƬ

		CCTextureCache::sharedTextureCache()->addImageAsync("game/stage_title.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  ��ͼ�ȼ��ı���ͼ


		CCTextureCache::sharedTextureCache()->addImageAsync("game/gameover.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  ��ͼ��Ϸ��������ͼ
		CCTextureCache::sharedTextureCache()->addImageAsync("game/gameovertips.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  ��ͼ��Ϸ������ʾͼ
		CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/gameoverbg.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  ��ͼ��Ϸ�ᱳ��ͼ

		CCTextureCache::sharedTextureCache()->addImageAsync("game/coin.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  ��ͼ���ͼ��

		CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/stats_bg.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  ʤ�����汳��ͼƬ

		CCTextureCache::sharedTextureCache()->addImageAsync("game/statstip.png",this,callfuncO_selector(LoadLayer::loadCallBack)); //  ʤ��������ʾ��ť

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
		// ���ý������ı���ͼƬ ���ǰ����ŵ���Ļ�·���1/5��	
		CCSprite* loadbackimg=CCSprite::create("gmbg/lodingbg.png");
		CC_BREAK_IF(!loadbackimg);	
		loadbackimg->setPosition(ccp(getWinSize().width/2+getWinOrigin().x,getWinSize().height/5+getWinOrigin().y));
		this->addChild(loadbackimg,1);

		// ��ӽ�����
		CCSprite* loadimg=CCSprite::create("gmbg/longding.png");
		CC_BREAK_IF(!loadimg);	
		CCProgressTimer* pt = CCProgressTimer::create(loadimg);
		pt->setType(kCCProgressTimerTypeBar);// ���óɺ����
		//���Կ����ǰ�������ʾЧ���Ľ���������
		pt->setMidpoint(ccp(0,0)); 
		//  �����趨����������ǰ���ķ���������һ��Ǵ�������
		pt->setBarChangeRate(ccp(1,0));
		//��������ê��
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