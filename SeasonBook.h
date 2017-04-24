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
private:
	cocos2d::Sprite* m_pBook;			// 本体
	bool m_isChange;					// 季節記を開いて季節を変えてる途中かどうか

public:
	CREATE_FUNC(SeasonBook);
	virtual bool init();

	void Change();						// 季節入れ替え画面を表示
};