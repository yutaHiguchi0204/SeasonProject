/* =====================================================================
//! @param		「SeasonBook」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/03/19
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"
#include "ui/CocosGUI.h"

// クラスの定義
class SeasonBook : public cocos2d::Sprite
{
private:
	cocos2d::Sprite* m_pBook;					// 本体
	cocos2d::Sprite* m_pPage;					// 季節のページ

	cocos2d::ui::Button* m_pButtonClose;		// 閉じるボタン
	cocos2d::ui::Button* m_pButtonArrowLeft;	// 左矢印
	cocos2d::ui::Button* m_pButtonArrowRight;	// 右矢印

	int m_time;									// 時間計測

public:
	CREATE_FUNC(SeasonBook);
	virtual bool init();

	void update(float delta);					// 更新処理

	void Change(int num);						// 季節変え
	void OpacityAnimation();					// 季節記の透明度アニメーション
};