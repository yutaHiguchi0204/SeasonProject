/* =====================================================================
//! @param		「GameManager」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/04/03
===================================================================== */

// ヘッダファイルのインクルード
#include "GameManager.h"
#include "PlayScene.h"

// 名前空間
USING_NS_CC;

// メンバ関数の定義

/* =====================================================================
//! 内　容		当たり判定チェック
//! 引　数		タイル座標（Vec2）、プレイヤー座標（Vec2）
//! 戻り値		なし
===================================================================== */
bool GameManager::isCollision(Vec2 tileVec, Vec2 playerVec)
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
}
/* =====================================================================
//! 内　容		衝突判定チェック
//! 引　数		タイル座標（Vec2）、プレイヤー座標（Vec2）
//! 戻り値		なし
===================================================================== */
int GameManager::decisionCollision(Vec2 tileVec, Vec2 playerVec)
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

	return static_cast<int>(COLLISION::NONE);
}
