/* =====================================================================
//! @param		「PlayScene」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/03/04
===================================================================== */

// ヘッダファイルのインクルード
#include "PlayScene.h"

// 名前空間
USING_NS_CC;
using namespace std;

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

// 初期化
bool PlayScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// ステージ
	m_pStage = Stage::create();
	this->addChild(m_pStage);

	// ボタン生成
	m_pButton[static_cast<int>(BUTTON::LEFT)]			= OperationButton::create(BUTTON::LEFT);
	m_pButton[static_cast<int>(BUTTON::RIGHT)]			= OperationButton::create(BUTTON::RIGHT);
	m_pButton[static_cast<int>(BUTTON::ACTION)]			= OperationButton::create(BUTTON::ACTION);
	m_pButton[static_cast<int>(BUTTON::PAUSE)]			= OperationButton::create(BUTTON::PAUSE);
	m_pButton[static_cast<int>(BUTTON::SEASON_BOOK)]	= OperationButton::create(BUTTON::SEASON_BOOK);

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

	// ボタンの明るさ
	m_pButton[static_cast<int>(BUTTON::LEFT)]->SetFullBright();
	m_pButton[static_cast<int>(BUTTON::RIGHT)]->SetFullBright();

	// アクションボタンの初期化（ジャンプボタン）
	m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::JUMP);

	// 当たり判定
	m_pStage->CheckCollision();

	// ポーズ中でなければ
	if (!Stage::m_isPause)
	{
		// ボタンが押されていたらプレイヤーを移動させる
		if (!Stage::m_isShowObject)
		{
			// 移動ボタンが押されたときの処理
			m_pStage->CheckButtonHighlighted(BUTTON::LEFT);
			m_pStage->CheckButtonHighlighted(BUTTON::RIGHT);

			// アクションボタンが押されたときの処理
			m_pStage->CheckButtonHighlighted(BUTTON::ACTION);
		}

		// ポーズボタンが押されたらポーズ画面を出す
		CheckPauseButtonHighlighted();

		// 季節記ボタンが押されたら季節を変えられる
		m_pStage->CheckButtonHighlighted(BUTTON::SEASON_BOOK);
	}

	// 左右で進めない場合はその時に応じてボタンの明度を変える
	if (Stage::m_isLeftCollision)	m_pButton[static_cast<int>(BUTTON::LEFT)]->SetFullBright(false);
	if (Stage::m_isRightCollision)	m_pButton[static_cast<int>(BUTTON::RIGHT)]->SetFullBright(false);

	// アクションボタンの明度を戻す
	if (!Player::m_isJump && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::JUMP)
	{
		m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright();
	}
}

/* =====================================================================
//! 内　容		ポーズボタンが押された時の処理
//! 引　数		ダミー引数（float）
//! 戻り値		なし
===================================================================== */
void PlayScene::CheckPauseButtonHighlighted()
{
	// ポーズボタン
	if (m_pButton[static_cast<int>(BUTTON::PAUSE)]->isHighlighted())
	{
		if (!Stage::m_isPause && !Stage::m_isShowObject)
		{
			// ポーズ画面の生成
			m_pPause = Pause::create();
			m_pPause->setPosition(Vec2(m_pStage->GetCameraPosX(), WINDOW_HEIGHT_HERF));
			this->addChild(m_pPause, 2);

			// ポーズ
			Stage::m_isPause = true;
		}
	}
}