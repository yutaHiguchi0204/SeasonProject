/* =====================================================================
//! @param		ゲームマネージャ
//! @create		樋口　裕太
//! @date		17/03/04
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "Consant.h"
#include "SoundManager.h"

// 共通関数をまとめたクラス
class GameManager
{
public:

	// ゲームマネージャの生成
	static GameManager& GetInstance()
	{
		static GameManager gm;
		return gm;
	};

	// 当たっているかどうか
	bool isCollision(cocos2d::Vec2 tileVec, cocos2d::Vec2 playerVec)
	{
		if ((playerVec.x - SIZE_PLAYER_COLLISION_HERF <= tileVec.x + SIZE_TILE) &&
			(playerVec.x + SIZE_PLAYER_COLLISION_HERF >= tileVec.x))
		{
			if ((playerVec.y - SIZE_PLAYER_HERF <= tileVec.y + SIZE_TILE) &&
				(playerVec.y + SIZE_PLAYER_HERF >= tileVec.y))
			{
				return true;
			}
		}

		return false;
	}

	// 全体の当たり判定
	COLLISION CheckCollision(cocos2d::Vec2 tileVec, cocos2d::Vec2 playerVec)
	{
		// 上下の当たり判定
		if ((playerVec.x - SIZE_PLAYER_COLLISION_HERF <= tileVec.x + SIZE_TILE) &&
			(playerVec.x + SIZE_PLAYER_COLLISION_HERF >= tileVec.x))
		{
			// 下の当たり判定
			if ((playerVec.y - SIZE_PLAYER_HERF >= tileVec.y + SIZE_TILE) &&
				(playerVec.y - SIZE_PLAYER_HERF - SIZE_COLLIDER <= tileVec.y + SIZE_TILE))
			{
				return COLLISION::DOWN;
			}

			// 上の当たり判定
			if ((playerVec.y + SIZE_PLAYER_HERF <= tileVec.y + SIZE_TILE) &&
				(playerVec.y + SIZE_PLAYER_HERF >= tileVec.y))
			{
				return COLLISION::UP;
			}
		}

		// 左右の当たり判定
		if ((playerVec.y - SIZE_PLAYER_HERF <= tileVec.y + SIZE_TILE) &&
			(playerVec.y + SIZE_PLAYER_HERF >= tileVec.y))
		{
			// 右の当たり判定
			if ((playerVec.x + SIZE_PLAYER_COLLISION_HERF >= tileVec.x) &&
				(playerVec.x - SIZE_PLAYER_COLLISION_HERF <= tileVec.x + SIZE_TILE))
			{
				return COLLISION::RIGHT;
			}

			// 左の当たり判定
			if ((playerVec.x - SIZE_PLAYER_COLLISION_HERF <= tileVec.x + SIZE_TILE) &&
				(playerVec.x + SIZE_PLAYER_COLLISION_HERF >= tileVec.x))
			{
				return COLLISION::LEFT;
			}
		}

		return COLLISION::NONE;
	};

private:
	GameManager() {};
};