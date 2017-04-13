/* =====================================================================
//! @param		「Player」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/03/06
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"

// 定数
const float SPEED_MOVE_PLAYER		= 4.0f;		// 移動速度
const float SPEED_MAX_FALL			= -10.0f;	// 最大落下速度
const float SPEED_MAX_FALL_WATER	= -5.0f;	// 最大水中落下速度
const float JUMP_PLAYER				= 10.0f;	// ジャンプの高さ
const float JUMP_WATER_PLAYER		= 3.0f;		// 水中ジャンプの高さ

// クラスの定義
class Player : public cocos2d::Sprite
{
private:
	int m_grpX;			// 画像のx座標
	float m_spdX;		// 移動速度x
	float m_spdY;		// 移動速度y

	bool m_isDive;		// 水中にいるかどうか

public:
	CREATE_FUNC(Player);
	virtual bool init();

	void update(float delta);

	void Fall(int mapInfo, int season);
	void Move(float speed);
	void Jump();

	void AnimationPlayer();

	static bool m_isJump;				// ジャンプをしているか
};