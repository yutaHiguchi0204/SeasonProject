/* =====================================================================
//! @param		「TitleScene」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/05/01
===================================================================== */

// ヘッダファイルのインクルード
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "TwoOptionWindow.h"

// 名前空間
USING_NS_CC;
using namespace std;

// 定数
const int HERF_COLOR = 127;

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

	// メンバ変数の初期化
	m_time = 0;

	// 背景画像
	Sprite* back = Sprite::create("background/back_title.png");
	back->setPosition(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF);
	this->addChild(back);

	// ボタン画像
	m_pMsgTitle = Sprite::create("object/start.png");
	m_pMsgTitle->setPosition(Vec2(WINDOW_WIDTH - 192.0f, 64.0f));
	m_pMsgTitle->setScale(1.5f);
	m_pMsgTitle->setOpacity(0x80);
	this->addChild(m_pMsgTitle);

	// リセットボタン
	m_pResetButton = cocos2d::ui::Button::create("object/button_dataReset.png");
	m_pResetButton->setPosition(Vec2(WINDOW_WIDTH - 80.0f, WINDOW_HEIGHT - 32.0f));
	this->addChild(m_pResetButton);
	
	// データリセット
	m_pResetButton->addClickEventListener([&](Ref* ref) {

		// 決定音の生成
		SoundManager& sm = SoundManager::getInstance();
		sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);
		
		// ウインドウ表示
		TwoOptionWindow* window = TwoOptionWindow::create();
		window->setPosition(WINDOW_MIDDLE);
		window->setScale(0.0f);
		this->addChild(window);
		window->runAction(ScaleTo::create(0.5f, 1.0f));

	});

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(TitleScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// タイトルのBGM生成
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::BGM_TITLE), false);
	sm.UncacheGameSound(SOUND::BGM_OP);
	
	return true;
}

void TitleScene::update(float delta)
{
	// フェード
	if (m_time / HERF_COLOR % 2 == 0)	m_pMsgTitle->setOpacity(m_pMsgTitle->getOpacity() + 0x01);
	else								m_pMsgTitle->setOpacity(m_pMsgTitle->getOpacity() - 0x01);

	// 時間計測
	m_time++;
}

void TitleScene::onTouchEnded(Touch* touch, Event* event)
{
	if (!TwoOptionWindow::m_isResetCheck)
	{
		// 次のシーンを作成する
		Scene* nextScene = StageSelectScene::create();

		// フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// 次のシーンに移行
		_director->replaceScene(nextScene);
	}
}