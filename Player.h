/* =====================================================================
//! @param		「Player」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/03/06
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"

// 定数
const float		SPEED_MAX_FALL			= -10.0f;		// 最大落下速度
const float		SPEED_MAX_FALL_WATER	= -5.0f;		// 最大水中落下速度
const float		JUMP_WATER_PLAYER		= 3.0f;			// 水中ジャンプの高さ

// クラスの定義
class Player : public cocos2d::Sprite
{
private:
	int m_grpX;			// 画像のx座標
	float m_spdX;		// 移動速度x
	float m_spdY;		// 移動速度y

	bool m_isStand;		// 地面にたっているかどうか

	int m_time;			// 時間計測

public:
	CREATE_FUNC(Player);
	virtual bool init();

	void update(float delta);

	void Gravity(bool dive);										// 重力付加
	void Fall(int mapInfo, int season);								// 落下処理
	void Move(float speed);											// 左右に移動
	void Jump();													// ジャンプ処理

	void Action(int tile, cocos2d::Vec2 tileVec, int season);		// タイルに対しての行動

	void SetSpdY(float spdY);										// 上下のスピードを取得

	void AnimationPlayer();											// プレイヤーアニメーション

	// 静的メンバ変数
	static bool m_isJump;											// ジャンプをしているか
	static bool m_isDive;											// 水中にいるかどうか
};