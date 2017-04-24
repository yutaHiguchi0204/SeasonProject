/* =====================================================================
//! @param		「GameManager」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/03/04
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "cocos2d.h"

// 定数
const int				NUM_ROW					= 17;														// 行数
const int				NUM_COLUMN				= 120;														// 列数
const int				NUM_BUTTON				= 3;														// ボタン数
const int				NUM_SEASON				= 4;														// 季節
const int				NUM_SECOND				= 60;														// １秒
const float				WINDOW_WIDTH			= 960.0f;													// 画面の幅
const float				WINDOW_HEIGHT			= 540.0f;													// 画面の高さ
const float				WINDOW_WIDTH_HERF		= WINDOW_WIDTH / 2;											// 画面の幅の半分
const float				WINDOW_HEIGHT_HERF		= WINDOW_HEIGHT / 2;										// 画面の高さの半分
const float				STAGE_WIDTH				= WINDOW_WIDTH * 4;											// ステージサイズ
const float				SIZE_TILE				= 32.0f;													// タイルサイズ(32×32)
const float				SIZE_PLAYER				= 48.0f;													// プレイヤーサイズ(48×48)
const float				NUM_GRAVITY				= 0.4f;														// 重力
const float				NUM_WATER_GRAVITY		= 0.05f;													// 浮力（水の重力）
const cocos2d::Vec2		WINDOW_MIDDLE			= cocos2d::Vec2(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF);		// 画面の中心

const std::string SEASON_NAME[NUM_SEASON] = {			// 季節名
	"spring",
	"summer",
	"autumn",
	"winter"
};

// 列挙型
enum class SEASON			// 季節
{
	SPRING,
	SUMMER,
	AUTUMN,
	WINTER
};

enum class TILE				// タイル
{
	NONE = -1,
	BLOCK,
	WATER,
	SIGN_BOARD,
	SEASON_BOOK
};

// 共通関数をまとめたクラス
class GameManager
{
public:

	static bool isCollision(cocos2d::Vec2 tileVec, cocos2d::Vec2 playerVec);		// 着地判定
};