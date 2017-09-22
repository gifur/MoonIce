#pragma once
#include "Baselayer.h"
#include "GameScene.h"

class LoadLayer : public BaseLayer
{
public:
	LoadLayer(void);
	~LoadLayer(void);

	virtual bool init();
	CREATE_FUNC(LoadLayer);

	GameScene* gameScene;
	void startGame();
	static cocos2d::CCScene* scene();
	void loadCallBack(cocos2d::CCObject* ped);// �첽����ͼƬʱ �Ļص�����
	int loadingNum;//������¼��ǰ�ļ���ͼƬ������
	int totalNum;// һ��Ҫ���ص�ͼƬ����
	bool setUpdateView();// ������ʼ��ҳ��� ����������
};

