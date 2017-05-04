/* =====================================================================
//! @param		「PlayScene」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/03/04
===================================================================== */

// ヘッダファイルのインクルード
#include "PlayScene.h"
#include "PauseScene.h"
#include "TitleScene.h"



// 名前空間
USING_NS_CC;
using namespace std;

// 静的メンバの定義
bool Stage::m_isShowObject;

// メンバ関数の定義

// シーン管理
Scene* PlayScene::createScene()
{
	// シーンを作成する
	auto scene = Scene::create();

	// レイヤーを作成する
	auto layer = PlayScene::create();

	// レイヤーをシーンに追加する
	scene->addChild(layer);

	// シーンを返す
	return scene;
}

//ポーズ画面表示非表示(bool)
void PlayScene::EnabledPauseback(bool TorF)
{
	Pauseback->setVisible(TorF);
	m_pTitleButton->setVisible(TorF);
	m_pGameBackButton->setVisible(TorF);
}


// 初期化
bool PlayScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// 各データの初期設定
	m_timeCnt = 0;								// 時間計測

	// ステージ
	m_pStage = Stage::create();
	this->addChild(m_pStage);

	// ボタン生成
	m_pButton[static_cast<int>(BUTTON::LEFT)] = OperationButton::create(BUTTON::LEFT);
	m_pButton[static_cast<int>(BUTTON::RIGHT)] = OperationButton::create(BUTTON::RIGHT);
	m_pButton[static_cast<int>(BUTTON::ACTION)] = OperationButton::create(BUTTON::ACTION);

	//Pauseボタンの作成
	m_pPauseButton = ui::Button::create("object/PauseButton.png");
	m_pPauseButton->setPosition(Vec2(70,500));
	m_pPauseButton->setVisible(true);
	this->addChild(m_pPauseButton);

	//ポーズ画面の作成
	Pauseback = Sprite::create("object/Pause.png");
	Pauseback->setPosition(480, 270);
	Pauseback->setVisible(false);
	this->addChild(Pauseback);

	//タイトルに戻るボタンの作成
	m_pTitleButton = ui::Button::create("object/TitleButton.png");
	m_pTitleButton->setPosition(Vec2(480, 250));
	m_pTitleButton->setVisible(false);
	this->addChild(m_pTitleButton);


	//ゲームに戻るボタンの作成
	m_pGameBackButton = ui::Button::create("object/GameBackButton.png");
	m_pGameBackButton->setPosition(Vec2(480, 100));
	m_pGameBackButton->setVisible(false);
	this->addChild(m_pGameBackButton);
	
	

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	m_pPauseButton->addTouchEventListener(CC_CALLBACK_2(PlayScene::onButtonTouch, this));

	// ボタンをシーンにつなぐ
	for (int i = 0; i < NUM_BUTTON; i++) this->addChild(m_pButton[i]);

	return true;
}

/* =====================================================================
//! 内　容		更新処理
//! 引　数		ダミー引数（float）
//! 戻り値		なし
===================================================================== */
void PlayScene::update(float delta)
{
	// スクロール
	m_pStage->Scroll();

	// アクションボタンの初期化（ジャンプボタン）
	m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::JUMP);

	// 当たり判定
	m_pStage->CheckCollision();

	// 時間計測
	m_timeCnt++;

	// ボタンが押されていたらプレイヤーを移動させる
	if (!Stage::m_isShowObject)
	{
		// 移動ボタンが押されたときの処理
		m_pStage->CheckButtonHighlighted(BUTTON::LEFT);
		m_pStage->CheckButtonHighlighted(BUTTON::RIGHT);

		// アクションボタンが押されたときの処理
		m_pStage->CheckButtonHighlighted(BUTTON::ACTION);
	}

	// アクションボタンの明度を戻す
	if ((!Player::m_isJump && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::JUMP)				||
		(!Stage::m_isShowObject && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::SEASON_BOOK)	||
		(!Stage::m_isShowObject && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::SIGN_BOARD))
	{
		m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright();
	}
}

//ポーズ関連
void PlayScene::onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType)
{
	if (eventType == ui::Widget::TouchEventType::ENDED)
	{
		
		//ポーズボタンが押された時
		m_pPauseButton->addClickEventListener([&](Ref* ref)
		{
			EnabledPauseback(true);

		});

		// ゲームに戻るボタンが押された時
		m_pGameBackButton->addClickEventListener([&](Ref* ref)
		{
			EnabledPauseback(false);

		});

		//タイトルに戻るが押されたとき
		m_pTitleButton->addClickEventListener([&](Ref* ref)
		{

			// 次のシーンを作成する
			Scene* nextScene = TitleScene::createScene();

			//フェードトランジション
			nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

			// 次のシーンに移行
			_director->replaceScene(nextScene);

		});
	}
}


