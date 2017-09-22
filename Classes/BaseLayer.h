#pragma once
#include "layers_scenes_transitions_nodes\cclayer.h"
#include "cocos2d.h"

USING_NS_CC;
class BaseLayer : public CCLayer
{
public:
	BaseLayer(void);
	~BaseLayer(void);
	
	CCScene* welcomeScene;

	virtual bool init();
	CREATE_FUNC(BaseLayer);

	cocos2d::CCSize getWinSize();//�õ���ǰ���Ӵ��ڵĴ�С
	cocos2d::CCPoint getWinOrigin();//�õ���ǰ���Ӵ��ڵ���ʼ��
	cocos2d::CCPoint getWinCenter();// �õ���Ļ���м�ĵ�
	cocos2d::CCPoint converSpritRel(float x, float y);
};

