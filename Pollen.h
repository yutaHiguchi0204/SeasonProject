/* =====================================================================
//! @param		「Pollen」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/05/02
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"

// 定数
const int TIME_POLLEN = 20;			// 花粉に侵されている時間

// クラスの定義
class Pollen : public cocos2d::Sprite
{
private:
	int m_time;

public:
	CREATE_FUNC(Pollen);
	virtual bool init();

	void update(float delta);

	// 静的メンバ変数
	static bool m_isPollenFlg;
};