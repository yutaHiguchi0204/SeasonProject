/* =====================================================================
//! @param		「Player」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/03/06
===================================================================== */

// ヘッダファイルのインクルード
#include "Player.h"
#include "PlayScene.h"
#include "Stage.h"

// 名前空間
USING_NS_CC;

// メンバ関数の定義

bool Player::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// プレイヤーの画像設定
	setTexture("object/player.png");

	// メンバの初期設定
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_isJump = false;
	m_isDive = false;
	m_time = 0;

	return true;
}

/* =====================================================================
//! 内　容		更新処理
//! 引　数		ダミー引数（float）
//! 戻り値		なし
===================================================================== */
void Player::update(float delta)
{
	if (!Stage::m_isPause)
	{
		// 移動
		setPosition(getPosition() + Vec2(m_spdX, m_spdY));
		m_spdX = 0.0f;

		// 重力
		Gravity(m_isDive);

		// プレイヤーアニメーション
		if (m_time % SPEED_ANIMATION == 0) AnimationPlayer();

		// 画像の変更
		setTextureRect(Rect(m_grpX, 0, SIZE_PLAYER, SIZE_PLAYER));

		// 時間計測
		m_time++;
	}
}

/* =====================================================================
//! 内　容		重力付加
//! 引　数		水中か否か（bool）
//! 戻り値		なし
===================================================================== */
void Player::Gravity(bool dive)
{
	// 水中にいる場合
	if (dive)
	{
		// 水中での重力
		if (m_spdY > SPEED_MAX_FALL_WATER)
		{
			m_spdY -= NUM_WATER_GRAVITY;
		}

		m_isDive = false;
	}
	else
	{
		// 通常の重力
		if (m_spdY > SPEED_MAX_FALL)
		{
			m_spdY -= NUM_GRAVITY;
		}
	}
}

/* =====================================================================
//! 内　容		落下処理
//! 引　数		マップ情報（int）、季節（int）
//! 戻り値		なし
===================================================================== */
void Player::Fall(int mapInfo, int season)
{
	if (mapInfo == static_cast<int>(TILE::BLOCK))
	{
		// ブロックのとき
		m_spdY = 0.0f;
		m_isJump = false;
	}
	else if (mapInfo == static_cast<int>(TILE::WATER))
	{
		if (season == static_cast<int>(SEASON::WINTER))
		{
			// 氷のとき
			m_spdY = 0.0f;
		}
		else
		{
			m_isJump = false;
			m_isDive = true;

			// 泳ぐボタンに変わる
			PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeButtonTexture(ACTION::SWIM);
		}
	}
}

/* =====================================================================
//! 内　容		移動
//! 引　数		速度（float）
//! 戻り値		なし
===================================================================== */
void Player::Move(float speed)
{
	m_spdX = speed;
}

/* =====================================================================
//! 内　容		ジャンプ
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Player::Jump()
{
	if (m_isDive)
	{
		m_spdY = JUMP_WATER_PLAYER;
	}
	else
	{
		m_spdY = JUMP_PLAYER;
		m_isJump = true;
	}
}

/* =====================================================================
//! 内　容		タイルに対しての行動
//! 引　数		タイルID（int）、タイル座標（Vec2）、季節（int）
//! 戻り値		なし
===================================================================== */
void Player::Action(int tileID, Vec2 tileVec, int season)
{
	switch (tileID)
	{
	case static_cast<int>(TILE::BLOCK):		// ブロック

		// 調整
		setPositionY(tileVec.y + SIZE_TILE + SIZE_PLAYER_HERF);

		// 落下処理
		Fall(static_cast<int>(TILE::BLOCK), season);

		break;

	case static_cast<int>(TILE::WATER):		// 水

		// 落下処理
		Fall(static_cast<int>(TILE::WATER), season);

		break;
	}
}

/* =====================================================================
//! 内　容		プレイヤーアニメーション
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Player::AnimationPlayer()
{
	m_grpX += SIZE_PLAYER;
	if (m_grpX >= SIZE_PLAYER * 3)
	{
		m_grpX = 0;
	}
}