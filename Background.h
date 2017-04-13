/* =====================================================================
//! @param		「Background」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/04/01
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"

// クラスの定義
class Background : public cocos2d::Sprite
{
public:
	CREATE_FUNC(Background);
	virtual bool init();

	void Change(int season);		// 背景の変更
};