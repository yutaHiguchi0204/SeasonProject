/* =====================================================================
//! @param		「SeasonBook」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/03/19
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"

// クラスの定義
class SeasonBook : public cocos2d::Sprite
{
public:
	CREATE_FUNC(SeasonBook);
	virtual bool init();
	void Setbookflag();
};