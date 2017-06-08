/* =====================================================================
//! @param		「OpeningScene」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/06/07
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"

// クラスの定義
class OpeningScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* m_pButtonSkip;			// スキップボタン
	int m_time;								// 時間

public:
	CREATE_FUNC(OpeningScene);
	virtual bool init();

	// シーンを作成する
	static cocos2d::Scene* createScene();

	void update(float delta);

	void DrawLines();						// セリフを表示

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) { return true; };
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	// 関数の遅延実行
	void CallFuncAfter(const float& delay, const std::function<void()>& func)
	{
		runAction(cocos2d::Sequence::create
		(cocos2d::DelayTime::create(delay), cocos2d::CallFunc::create(func), nullptr));
	}
};