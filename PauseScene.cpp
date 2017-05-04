#include "PauseScene.h"
#include "PlayScene.h"

// 名前空間
USING_NS_CC;
using namespace std;

// シーン管理


//初期化
bool PauseScene::init()
{
	if (!Node::init())
	{
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(PauseScene::onTouchBegan, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	
}


void PauseScene::update(float delta)
{

}

