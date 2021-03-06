/* =====================================================================
//! @param		「TitleScene」クラスのヘッダファイル
//! @create		松丸　勇輝
//! @date		17/05/01
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"
#include "ui/CocosGUI.h"

class TitleScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* m_pMsgTitle;
	cocos2d::ui::Button* m_pResetButton;
	int m_time;

public:

	CREATE_FUNC(TitleScene);

	virtual bool init();

	// シーンを作成する
	static cocos2d::Scene* createScene();
	
	void update(float delta);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) { return true; };
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

