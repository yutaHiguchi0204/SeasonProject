/* =====================================================================
//! @param		「TitleScene」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/05/01
===================================================================== */

// ヘッダファイルのインクルード
#include "TitleScene.h"
#include "StageSelectScene.h"

// 名前空間
USING_NS_CC;
using namespace std;

// シーン管理
Scene* TitleScene::createScene()
{
	// シーンを作成する
	auto scene = Scene::create();

	// レイヤーを作成する
	auto layer = TitleScene::create();

	// レイヤーをシーンに追加する
	scene->addChild(layer);

	// シーンを返す
	return scene;
}

// 初期化
bool TitleScene::init()
{
	// 基底クラスの初期化
	if (!Scene::init())
	{
		// 基底クラスの初期化が失敗なら、異常終了
		return false;
	}
	
	// 更新処理準備
	scheduleUpdate();

	// 背景画像
	Sprite* back = Sprite::create("title.png");
	back->setPosition(480, 270);
	this->addChild(back);

	//ボタン画像
	ui::Button* m_tButton = ui::Button::create("start.png");
	m_tButton->setPosition(Vec2(480, 100));
	m_tButton->setScale(1.5f);
	this->addChild(m_tButton);

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	m_tButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::onButtonTouch, this));

	return true;
}

void TitleScene::update(float delta)
{

}

void TitleScene::onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType)
{
	if (eventType == ui::Widget::TouchEventType::ENDED)
	{
		// 次のシーンを作成する
		Scene* nextScene = StageSelectScene::createScene();

		//フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// 次のシーンに移行
		_director->replaceScene(nextScene);
	}
}
