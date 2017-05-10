/* =====================================================================
//! @param		「StageSelectScene」クラスのソースファイル
//! @create		松丸　勇輝
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

	Sprite* back = Sprite::create("background/back_spring.png");
	back->setPosition(480, 270);
	this->addChild(back);

	// ボタン画像
	cocos2d::ui::Button* selectButton = cocos2d::ui::Button::create("object/selectButton.png");
	selectButton->setPosition(Vec2(128.0f, 96.0f));
	this->addChild(selectButton);

	cocos2d::ui::Button* notSelectButton1 = cocos2d::ui::Button::create("object/Not_selectButton.png");
	notSelectButton1->setPosition(Vec2(WINDOW_WIDTH - 128.0f, 192.0f));
	this->addChild(notSelectButton1);

	cocos2d::ui::Button* notSelectButton2 = cocos2d::ui::Button::create("object/Not_selectButton.png");
	notSelectButton2->setPosition(Vec2(128.0f, WINDOW_HEIGHT - 192.0f));
	this->addChild(notSelectButton2);

	cocos2d::ui::Button* notSelectButton3 = cocos2d::ui::Button::create("object/Not_selectButton.png");
	notSelectButton3->setPosition(Vec2(WINDOW_WIDTH - 128.0f, WINDOW_HEIGHT - 96.0f));
	this->addChild(notSelectButton3);

	// プレイヤー
	m_pSprPlayer = Sprite::create("object/player.png");
	m_pSprPlayer->setPosition(selectButton->getPosition());
	this->addChild(m_pSprPlayer);

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	selectButton->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch, this));

	return true;
}

void StageSelectScene::update(float delta)
{
	// プレイヤーアニメーション
	if (m_time % SPEED_ANIMATION == 0) animationPlayer();

	// 画像の変更
	m_pSprPlayer->setTextureRect(Rect(m_playerGrpX, 0, SIZE_PLAYER, SIZE_PLAYER));

	// 時間計測
	m_time++;

}

void StageSelectScene::onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType)
{
	if (eventType == ui::Widget::TouchEventType::ENDED)
	{
		// 次のシーンを作成する
		Scene* nextScene = PlayScene::create();

		//フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// 次のシーンに移行
		_director->replaceScene(nextScene);
	}
}

void StageSelectScene::animationPlayer()
{
	m_playerGrpX += SIZE_PLAYER;
	if (m_playerGrpX >= SIZE_PLAYER * 3)
	{
		m_playerGrpX = 0;
	}
}