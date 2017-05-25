/* =====================================================================
//! @param		「Background」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/04/01
===================================================================== */

// ヘッダファイルのインクルード
#include "Background.h"

// 名前空間
USING_NS_CC;

// メンバ関数の定義

bool Background::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// 画像の初期設定
	setTexture("background/back_spring.png");

	// 位置の初期設定
	setPosition(STAGE_MIDDLE);

	return true;
}

/* =====================================================================
//! 内　容		背景の変更
//! 引　数		季節（int）
//! 戻り値		なし
===================================================================== */
void Background::Change(int season)
{
	std::stringstream sFileName;
	sFileName << "background/back_" << SEASON_NAME[season] << ".png";

	// 背景の変更
	setTexture(sFileName.str());
}