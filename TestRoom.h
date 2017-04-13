/* =====================================================================
//! @param		デバッグ用
//! @create		樋口　裕太
//! @date		17/03/05
===================================================================== */
#pragma once

#include "GameManager.h"
#include "Player.h"
#include "ui/CocosGUI.h"

class Test : public cocos2d::Scene
{
private:
	int m_season;										// 季節
	int m_map[NUM_ROW][NUM_COLUMN];						// マップ

	cocos2d::Sprite* m_pBack;							// 背景
	cocos2d::Sprite* m_pTip[NUM_ROW][NUM_COLUMN];		// マップチップ
	cocos2d::Sprite* m_pSignBoard;						// 看板
	cocos2d::Sprite* m_pBoard;							// 説明盤

	Player* m_pPlayer;									// プレイヤー
	cocos2d::ui::Button* m_pButtonLeft;					// 左ボタン
	cocos2d::ui::Button* m_pButtonRight;				// 右ボタン
	cocos2d::ui::Button* m_pButtonAction;				// アクションボタン

public:
	CREATE_FUNC(Test);
	virtual bool init();

	void update(float delta);

	// 関数の遅延実行
	void CallFuncAfter(const float& delay, const std::function<void()>& func)
	{
		runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(delay), cocos2d::CallFunc::create(func), nullptr));
	}

	void TestRoom();
	void ChangeSeason();

	void Import();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	//static int m_timeCnt;							// タイマー計測
};