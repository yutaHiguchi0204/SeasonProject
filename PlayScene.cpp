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

	// 各データの初期設定
	m_pSeasonBook = nullptr;					// 季節記
	m_timeCnt = 0;								// 時間計測
	m_isChangeSeason = false;					// 季節を入れ替えてるかどうか

	// ステージ
	m_pStage = Stage::create();
	this->addChild(m_pStage);

	// ボタン生成
	m_pButton[static_cast<int>(BUTTON::LEFT)] = OperationButton::create(BUTTON::LEFT);
	m_pButton[static_cast<int>(BUTTON::RIGHT)] = OperationButton::create(BUTTON::RIGHT);
	m_pButton[static_cast<int>(BUTTON::ACTION)] = OperationButton::create(BUTTON::ACTION);

	// ボタンをシーンにつなぐ
	for (int i = 0; i < NUM_BUTTON; i++) this->addChild(m_pButton[i], 3);

	// プレイヤー
	m_pPlayer = Player::create();
	m_pPlayer->setPosition(Vec2(64.0f, 216.0f));
	this->addChild(m_pPlayer, 1);

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
	m_pStage->Scroll(m_pPlayer->getPositionX(), m_pButton);

	// アクションボタンの初期化（ジャンプボタン）
	m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::JUMP);

	// 当たり判定
	m_pStage->CheckCollision(m_pPlayer);

	// 時間計測
	m_timeCnt++;

	// ボタンが押されていたらプレイヤーを移動させる
	if (!m_isChangeSeason)
	{
		m_pStage->MoveButtonHighlighted(BUTTON::LEFT, m_pPlayer);
		m_pStage->MoveButtonHighlighted(BUTTON::RIGHT, m_pPlayer);

		// アクションボタンが押されたときの処理
		if (m_pButton[static_cast<int>(BUTTON::ACTION)]->isHighlighted() && !Player::m_isJump)
		{
			// ジャンプ処理
			if (m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::JUMP)
			{
				m_pPlayer->Jump();
				m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright(false);
			}
			// 季節記処理
			else
			{
				// 季節記の生成
				m_pSeasonBook = SeasonBook::create();
				m_pSeasonBook->setPosition(Vec2(m_pStage->GetCameraPosX(), WINDOW_HEIGHT_HERF));
				this->addChild(m_pSeasonBook, 4);

				// 明度を暗くする
				m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright(false);

				// 季節変化をしている状態にする
				m_isChangeSeason = true;
			}
		}
	}

	// アクションボタンの明度を戻す
	if ((!Player::m_isJump && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::JUMP) ||
		(!m_isChangeSeason && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::SEASON_BOOK))
	{
		m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright();
	}
}