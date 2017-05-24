/* =====================================================================
//! @param		ゲームマネージャ
//! @create		樋口　裕太
//! @date		17/03/04
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "Consant.h"

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

	// 着地判定（全体の当たり判定）
	static bool isCollision(cocos2d::Vec2 tileVec, cocos2d::Vec2 playerVec)
	{
		if ((tileVec.x <= playerVec.x + SIZE_PLAYER_HERF) &&
			(tileVec.x + SIZE_TILE >= playerVec.x - SIZE_PLAYER_HERF))
		{
			if ((tileVec.y <= playerVec.y + SIZE_PLAYER_HERF) &&
				(tileVec.y + SIZE_TILE >= playerVec.y - SIZE_PLAYER_HERF))
			{
				return true;
			}
		}

		return false;
	};

	// 左右の当たり判定
	static int decisionCollision(cocos2d::Vec2 tileVec, cocos2d::Vec2 playerVec)
	{
		if (playerVec.y - tileVec.y <= SIZE_TILE)
		{
			// 右のあたり判定
			if (playerVec.x + SIZE_PLAYER_HERF + SPEED_MOVE_PLAYER >= tileVec.x &&
				playerVec.x - SIZE_PLAYER_HERF <= tileVec.x + SIZE_TILE)
			{
				return static_cast<int>(COLLISION::RIGHT);
			}
			// 左のあたり判定
			else if (playerVec.x - SIZE_PLAYER_HERF - SPEED_MOVE_PLAYER <= tileVec.x + SIZE_TILE &&
				playerVec.x + SIZE_PLAYER_HERF >= tileVec.x)
			{
				return static_cast<int>(COLLISION::LEFT);
			}
		}
	};

private:
	GameManager() {};
};