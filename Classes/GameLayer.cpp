#include "GameLayer.h"
#include "HudLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

#define random_range(low, high) (rand() % (high - low + 1)) + low
#define UINT64_MAX	0xffffffffffffffffU
#define UINT64_C(x)		((x) + (UINT64_MAX - UINT64_MAX))
#define frandom (float)rand() / UINT64_C(0x100000000)
#define frandom_range(low, high) ((high - low) * frandom) + low
 
USING_NS_CC;

GameLayer::GameLayer(void)
{ 
	this->hero = NULL;
	this->_hudLayer = NULL;
}


GameLayer::~GameLayer(void)
{
}

bool GameLayer::init(){
	bool bRet = true;
	if(!CCLayer::init()){ //初始化父类
		bRet = false;
		return bRet;
	}
	initTiledMap();
	/* 声音注释 -Josephus 2014-2-24 20:58:48
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("123.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("123.mp3",true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pd_hit0.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pd_hit1.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pd_herodeath.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pd_botdeath.wav");
	*/
	//加载精灵表单
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist"); //缓冲Sprite帧到缓存 
	_actor = CCSpriteBatchNode::create("pd_sprites.pvr.ccz");
	_actor->getTexture()->setAliasTexParameters();
	this->addChild(_actor);

	initHero();
	initRobot();
	this->setTouchEnabled(true);
	this->scheduleUpdate();
	return bRet;
}

void GameLayer::initTiledMap(){
	this->pTiledMap = CCTMXTiledMap::create("pd_tilemap.tmx");
	
	CCObject* obj = NULL;
	CCARRAY_FOREACH(pTiledMap->getChildren(),obj){
		CCTMXLayer* _child = (CCTMXLayer*)obj;  //CCTMXLayer TMX图层
		_child->getTexture()->setAliasTexParameters(); //getTexture 得到纹理，关闭抗锯齿
	}
	this->addChild(pTiledMap);
}

void GameLayer::initHero(){
	this->hero = Hero::create();
	this->hero->setPosition(ccp(this->hero->centerToSide,160));
	this->hero->disertDirection = this->hero->getPosition();
	this->hero->velocity = CCPointZero;

	this->_actor->addChild(this->hero);

	this->hero->idle();
}

void GameLayer::initRobot(){

	this->robots = CCArray::create();
	this->robots->retain();

	for(int i = 0; i<5 ;i++){
		Robot* robot = Robot::create();
		this->_actor->addChild(robot);
		this->robots->addObject(robot);

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		//CCLOG("winSize.width = %d, winSize.height = %d, data frome initRobot", winSize.width, winSize.height);
		//CCLOG("pTileMap.width = %d, pTileMap.height = %d, data from initRobot", pTiledMap->getTileSize().width, pTiledMap->getTileSize().height);
		int minX = winSize.width + robot->centerToSide;
		int maxX = this->pTiledMap->getMapSize().width * this->pTiledMap->getTileSize().width - robot->centerToSide;
		int minY = robot->centerToBottom;
		int maxY = 8 * this->pTiledMap->getTileSize().height + robot->centerToBottom;

		robot->setScaleX(-1);
		robot->setPosition(ccp(minX + (rand()%(maxX - minX + 1)),minY + (rand()%(maxY - minY + 1))));
		robot->disertDirection = robot->getPosition();
		robot->idle();
	}
}

void GameLayer::registerWithTouchDispatcher(){
		CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
	this->hero->attack();

	CCObject* object;
	CCARRAY_FOREACH(this->robots,object){
		Robot* robot = (Robot*)object;
		if (robot->_actionState!=kActionStateDead)
		{
			if(fabsf(this->hero->getPositionY() - robot->getPositionY())<20){
				if(this->hero->_attackBox.actual.intersectsRect(robot->_hitBox.actual)){
					robot->hurtWithDamage(this->hero->damage);
				}
			}

		}	
	}
}

void GameLayer::didChangeDirectionTo(SimpleDPad* simpleDPad,CCPoint direction){
	CCLOG("%s","--------->didChangeDirectionTo");
	this->hero->walkWithDirection(direction);
}
void GameLayer::isHoldingDirector(SimpleDPad* simpleDPad,CCPoint direction){
	this->hero->walkWithDirection(direction);
}
void GameLayer::simpleDPadTouchEnded(SimpleDPad* simpleDPad){
			
	if(this->hero->_actionState == kActionStateWalk){
		this->hero->velocity = CCPointZero;
		this->hero->idle();
	}
}

void GameLayer::update(float dt){
	this->hero->updateDirection(dt);

	float directionX = MIN(this->pTiledMap->getMapSize().width * this->pTiledMap->getTileSize().width - this->hero->centerToSide,
					       MAX(this->hero->centerToSide,this->hero->disertDirection.x));
	float directionY = MIN(8 * this->pTiledMap->getTileSize().height + this->hero->centerToBottom,
						   MAX(this->hero->centerToBottom,this->hero->disertDirection.y));
	this->hero->setPosition(ccp(directionX,directionY));

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float x = MAX(winSize.width/2,this->hero->getPosition().x);
	float y = MAX(winSize.height/2,this->hero->getPosition().y);

	x = MIN(this->pTiledMap->getMapSize().width * this->pTiledMap->getTileSize().width - winSize.width/2,x);
	y = MIN(this->pTiledMap->getMapSize().height * this->pTiledMap->getTileSize().height - winSize.height/2,y);

	CCPoint actualPosition = ccp(x,y);
	CCPoint centerOfView = ccp(winSize.width/2,winSize.height/2);
	CCPoint viewPoint = ccpSub(centerOfView,actualPosition);

	this->setPosition(viewPoint);

	CCObject* spriteObject = NULL;
	CCARRAY_FOREACH(this->_actor->getChildren(),spriteObject){
		ActionSprite* sprite = (ActionSprite*)spriteObject;
		this->_actor->reorderChild(sprite,this->pTiledMap->getMapSize().height*this->pTiledMap->getTileSize().height - sprite->getPosition().y );
	}

	if(this->_hudLayer == NULL){
		this->_hudLayer = ((GameScene*)this->getParent())->_hudLayer;
	}
	
	this->updateRobot(dt);

}

static float getCurTime(){
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (float)millisecs;
	
}

void GameLayer::updateRobot(float dt){
	int alive = 0;
	int randomChoice = 0;
	CCObject* object = NULL;
	CCARRAY_FOREACH(this->robots,object){
		Robot* robot = (Robot*)object;
		int DirectionSQ;
		if(robot->_actionState != kActionStateDead){
			alive++;

			if(::getCurTime() > robot->_nextDecisionTime){
				DirectionSQ = ccpDistanceSQ(this->hero->getPosition(),robot->getPosition());
				if(DirectionSQ <= 50*50){
					robot->_nextDecisionTime = ::getCurTime() + frandom_range(0.1,0.5)*5000;
					randomChoice = random_range(0,1);
					if(randomChoice == 0){
						if(this->hero->getPosition().x > robot->getPosition().x){
							robot->setScaleX(1.0);
						}else
						{
							robot->setScaleX(-1.0);
						}
						robot->_nextDecisionTime = ::getCurTime() + frandom_range(0.1, 0.5) * 3000;
						robot->attack(); 
						if(robot->_attackBox.actual.intersectsRect(this->hero->_hitBox.actual)){
							this->hero->hurtWithDamage(robot->damage);
							if(this->hero->_actionState == kActionStateDead &&  _hudLayer->getChildByTag(5)==NULL){
								this->endGame();
							}
						}
					}else{
						robot->idle();
					}					
				}else if(DirectionSQ < CCDirector::sharedDirector()->getWinSize().width * CCDirector::sharedDirector()->getWinSize().height){
						robot->_nextDecisionTime = ::getCurTime() + frandom_range(0.1,0.5)*4000;
						randomChoice = random_range(0,10);
						if(randomChoice != 0){
							CCPoint point = ccpNormalize(ccpSub(this->hero->getPosition(), robot->getPosition()));//返回v的标准化向量，就是长度为1
							robot->walkWithDirection(point);
							robot->updateDirection(dt*20);
							float directionX = MIN(this->pTiledMap->getMapSize().width * this->pTiledMap->getTileSize().width - robot->centerToSide,
								MAX(robot->centerToSide,robot->disertDirection.x));
							float directionY = MIN(8 * this->pTiledMap->getTileSize().height + robot->centerToBottom,
								MAX(robot->centerToBottom,robot->disertDirection.y));
							robot->setPosition(CCPoint(directionX,directionY));
						}else {
							robot->idle();
						}
					}
			}

		}

	}
	if(alive == 0 && _hudLayer->getChildByTag(5)==NULL){
		this->endGame();
	}
}



void GameLayer::endGame(){
	CCPoint point = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	CCLabelTTF* label = CCLabelTTF::create("restart","Arial",40);
	CCMenuItemLabel* item = CCMenuItemLabel::create(label,this,menu_selector(GameLayer::startGame));
	CCMenu* menu = CCMenu::create(item,NULL);
	menu->setPosition(ccp(point.x+size.width/2,point.y+size.height/2));
	menu->setTag(5);

	if(_hudLayer != NULL ){
		_hudLayer->addChild(menu);
	}
}
void GameLayer::startGame(CCObject *pSence){
	_hudLayer->getChildByTag(5)->removeFromParentAndCleanup(true); 
	CCDirector::sharedDirector()->replaceScene((CCScene*)GameScene::create());
}