/* =====================================================================
//! @param		「StageSelectScene」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/05/01
===================================================================== */

// ヘッダファイルのインクルード
#include "StageSelectScene.h"
#include "PlayScene.h"

// 名前空間
USING_NS_CC;
using namespace std;

// シーン管理
Scene* StageSelectScene::createScene()
{
	// シーンを作成する
	auto scene = Scene::create();

	// レイヤーを作成する
	auto layer = StageSelectScene::create();

	// レイヤーをシーンに追加する
	scene->addChild(layer);

	// シーンを返す
	return scene;
}

// 初期化
bool StageSelectScene::init()
{
	// 基底クラスの初期化
	if (!Scene::init())
	{
		// 基底クラスの初期化が失敗なら、異常終了
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	Sprite* back = Sprite::create("Stageselect.png");
	back->setPosition(480, 270);
	this->addChild(back);

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(StageSelectScene::onTouchBegan, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void StageSelectScene::update(float delta)
{

}

bool StageSelectScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent)
{
	// 次のシーンを作成する
	Scene* nextScene = PlayScene::create();

	//フェードトランジション
	nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

	// 次のシーンに移行
	_director->replaceScene(nextScene);

	return false;
}
