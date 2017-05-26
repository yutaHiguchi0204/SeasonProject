/* =====================================================================
//! @param		定数をまとめたヘッダファイル
//! @create		樋口　裕太
//! @date		17/05/22
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "cocos2d.h"

/* 複数のクラスで使用する定数をここで定義してください
// クラス内のみの場合はクラスのヘッダー内で定義してください
*/

// メイン関係
const float				WINDOW_WIDTH				= 960.0f;													// 画面の幅
const float				WINDOW_HEIGHT				= 540.0f;													// 画面の高さ
const float				WINDOW_WIDTH_HERF			= WINDOW_WIDTH / 2;											// 画面の幅の半分
const float				WINDOW_HEIGHT_HERF			= WINDOW_HEIGHT / 2;										// 画面の高さの半分
const cocos2d::Vec2		WINDOW_MIDDLE				= cocos2d::Vec2(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF);		// 画面の中心
const int				NUM_SECOND					= 60;														// １秒
const int				SPEED_ANIMATION				= 10;														// アニメーションスピード（コマ間隔）

// ステージ関係
const int				NUM_ROW						= 17;														// 行数
const int				NUM_COLUMN					= 120;														// 列数
const int				NUM_STAGE					= 4;														// ステージ数
const int				NUM_SEASON					= 4;														// 季節数
const int				NUM_BUTTON					= 5;														// ボタン数
const int				NUM_ITEM					= 100;														// アイテム数
const int				NUM_STAGE_ITEM				= 25;														// ステージのアイテム数
const float				STAGE_WIDTH					= WINDOW_WIDTH * 4;											// ステージサイズ
const float				STAGE_WIDTH_HERF			= STAGE_WIDTH / 2;											// ステージサイズの半分
const cocos2d::Vec2		STAGE_MIDDLE				= cocos2d::Vec2(STAGE_WIDTH_HERF, WINDOW_HEIGHT_HERF);		// ステージの中心
const float				SIZE_TILE					= 32.0f;													// タイルサイズ(32×32)
const float				SIZE_COLLIDER				= 10.0f;														// 当たり判定調整用
const float				NUM_GRAVITY					= 0.4f;														// 重力
const float				NUM_WATER_GRAVITY			= 0.05f;													// 浮力（水の重力）

// プレイヤー関係
const float				SIZE_PLAYER					= 48.0f;													// プレイヤーサイズ(48×48)
const float				SIZE_PLAYER_HERF			= SIZE_PLAYER / 2;											// プレイヤーの半分のサイズ
const float				SIZE_PLAYER_COLLISION		= 32.0f;													// プレイヤーの当たり判定
const float				SIZE_PLAYER_COLLISION_HERF	= SIZE_PLAYER_COLLISION / 2;								// プレイヤーの当たり判定の半分
const float				SPEED_MOVE_PLAYER			= 4.0f;														// 移動速度
const float				JUMP_PLAYER					= 10.0f;													// ジャンプの高さ

// 文字定数
const std::string STAGE_NAME[NUM_STAGE] = {				// ステージ名
	"flower",
	"bird",
	"wind",
	"moon"
};

const std::string SEASON_NAME[NUM_SEASON] = {			// 季節名
	"spring",
	"summer",
	"autumn",
	"winter"
};

// 列挙型
enum class STAGE			// ステージ
{
	FLOWER,
	BIRD,
	WIND,
	MOON
};

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
	POLLEN,
	ITEM
};

enum class COLLISION
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};