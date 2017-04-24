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
	m_timeCnt = 0;										// 時間計測

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
	if (m_pButton[static_cast<int>(BUTTON::LEFT)]->isHighlighted())
	{
		// プレイヤーの向きを設定
		m_pPlayer->setFlippedX(true);

		// プレイヤーの移動
		if (m_pPlayer->getPositionX() > SIZE_PLAYER / 2)
		{
			m_pPlayer->Move(-SPEED_MOVE_PLAYER);
		}
	}
	else if (m_pButton[static_cast<int>(BUTTON::RIGHT)]->isHighlighted())
	{
		// プレイヤーの向きを設定
		m_pPlayer->setFlippedX(false);

		// プレイヤーの移動
		if (m_pPlayer->getPositionX() < STAGE_WIDTH - SIZE_PLAYER / 2)
		{
			m_pPlayer->Move(SPEED_MOVE_PLAYER);
		}
	}

	// アクションボタンが押されたらプレイヤーをジャンプさせる
	if (m_pButton[static_cast<int>(BUTTON::ACTION)]->isHighlighted() && !Player::m_isJump)
	{
		if (m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::JUMP)
		{
			m_pPlayer->Jump();
			m_pButton[static_cast<int>(BUTTON::ACTION)]->setColor(Color3B(128.0f, 128.0f, 128.0f));
		}
	}

	// アクションボタン設定
	if (!Player::m_isJump)
	{
		m_pButton[static_cast<int>(BUTTON::ACTION)]->setColor(Color3B(255.0f, 255.0f, 255.0f));
	}
}