/* =====================================================================
//! @param		「Item」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/05/26
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"

// ステージ、季節ごとのアイテム数
const int NUM_PLACE = NUM_SEASON * NUM_STAGE;
const int NUM_ITEM_PLACE[NUM_PLACE] = {
	6,		// 花の春
	6,		// 花の夏
	6,		// 花の秋
	7,		// 花の冬
	7,		// 鳥の春
	6,		// 鳥の夏
	5,		// 鳥の秋
	7,		// 鳥の冬
	0,		// 風の春
	0,		// 風の夏
	0,		// 風の秋
	0,		// 風の冬
	0,		// 月の春
	0,		// 月の夏
	0,		// 月の秋
	0,		// 月の冬
};

// クラスの定義
class Item : public cocos2d::Sprite
{
public:
	CREATE_FUNC(Item);
	virtual bool init();
};