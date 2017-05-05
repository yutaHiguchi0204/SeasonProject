/* =====================================================================
//! @param		「Pause」クラスのヘッダファイル
//! @create		木下　浩輝
//! @date		17/05/01
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"
#include "ui/CocosGUI.h"

class Pause : public cocos2d::Sprite
{
private:
	cocos2d::ui::Button* m_pPauseButtonBack;			// ゲームに戻るボタン
	cocos2d::ui::Button* m_pPauseButtonTitle;			// タイトルに戻るボタン

public:
	CREATE_FUNC(Pause);
	virtual bool init();

	void update(float delta);

	void ClosePause(bool sceneOut = false);				// ポーズ画面を閉じる
};