/* =====================================================================
//! @param		「TitleScene」クラスのヘッダファイル
//! @create		松丸　勇輝
//! @date		17/05/01
===================================================================== */
#pragma once

//ヘッダファイルのインクルード
#include "GameManager.h"
#include "ui/CocosGUI.h"

class TitleScene : public cocos2d::Scene
{
private:
public:

	CREATE_FUNC(TitleScene);

	virtual bool init();

	// シーンを作成する
	static cocos2d::Scene* createScene();
	
	void update(float delta);

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType);

	cocos2d::ui::Button* m_tButton; //ボタン

};

