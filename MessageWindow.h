/* =====================================================================
//! @param		「MessageWindow」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/05/28
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"
#include "ui/CocosGUI.h"

// クラスの定義
class MessageWindow : public cocos2d::Sprite
{
private:
	cocos2d::ui::Button* m_pButtonOK;

public:
	CREATE_FUNC(MessageWindow);
	virtual bool init();

	// 静的メンバ
	static bool m_isSaveCheck;
};