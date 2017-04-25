/* =====================================================================
//! @param		「SeasonBook」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/03/19
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"
#include "SeasonBook.h"
#include "ui/CocosGUI.h"

// クラスの定義
class SeasonBook : public cocos2d::Sprite
{
private:
	cocos2d::Sprite* m_pBook;					// 本体

	cocos2d::ui::Button* m_pButtonClose;		// 閉じるボタン
	cocos2d::ui::Button* m_pButtonArrowLeft;	// 左矢印
	cocos2d::ui::Button* m_pButtonArrowRight;	// 右矢印

public:
	CREATE_FUNC(SeasonBook);
	virtual bool init();

	void update(float delta);
};