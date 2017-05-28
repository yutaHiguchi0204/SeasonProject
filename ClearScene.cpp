/* =====================================================================
//! @param		「ClearScene」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/05/05
===================================================================== */

// ヘッダファイルのインクルード
#include "ClearScene.h"
#include "StageSelectScene.h"

// 名前空間
USING_NS_CC;
using namespace std;

// メンバ関数の定義

// シーン管理
Scene* ClearScene::createScene()
{
	// シーンを作成する
	auto scene = Scene::create();

	// レイヤーを作成する
	auto layer = ClearScene::create();

	// レイヤーをシーンに追加する
	scene->addChild(layer);

	// シーンを返す
	return scene;
}

// 初期化
bool ClearScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// 背景
	m_pBack = Sprite::create("background/back_clear.png");
	m_pBack->setPosition(WINDOW_MIDDLE);
	this->addChild(m_pBack);

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ClearScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// クリアのBGM生成
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::BGM_CLEAR), false);

	return true;
}

/* =====================================================================
//! 内　容		タッチ処理
//! 引　数		タッチ情報（Touch）、イベント情報（Event）
//! 戻り値		タッチされたか否か（bool）
===================================================================== */
bool ClearScene::onTouchBegan(Touch* touch, Event* pEvent)
{
	// 次のシーンを作成する
	Scene* nextScene = StageSelectScene::create();

	// フェードトランジション
	nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

	// 次のシーンに移行
	_director->replaceScene(nextScene);

	return false;
}