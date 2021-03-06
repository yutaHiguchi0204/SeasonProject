/* =====================================================================
//! @param		「Pause」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/05/01
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"
#include "ui/CocosGUI.h"

class Pause : public cocos2d::Sprite
{
private:
	cocos2d::Sprite* m_pPauseMain;						// ポーズのメイン画面
	cocos2d::ui::Button* m_pPauseButtonBack;			// ゲームに戻るボタン
	cocos2d::ui::Button* m_pPauseButtonTitle;			// タイトルに戻るボタン
	cocos2d::ui::Button* m_pPauseButtonSelect;			// ステージ選択画面に戻るボタン

	cocos2d::Sprite* m_pBookmarkIcon[NUM_SEASON];		// しおりアイコン

	cocos2d::Sprite* m_pItemUIspr;						// アイテムＵＩの画像
	cocos2d::Label* m_pItemUInum;						// アイテムＵＩのアイテム所持数

public:
	CREATE_FUNC(Pause);
	virtual bool init();

	void update(float delta);
};