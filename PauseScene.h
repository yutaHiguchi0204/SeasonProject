/* =====================================================================
//! @param		「PauseScene」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/05/01
===================================================================== */
#pragma once

//ヘッダファイルのインクルード
#include "GameManager.h"
#include "OperationButton.h"
#include"PlayScene.h"

class PauseScene :cocos2d::Scene
{
private:


public:
	CREATE_FUNC(PauseScene);
	virtual bool init();


	void update(float delta);

	void onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType);


	static OperationButton* m_pButton[NUM_BUTTON];

	
	


};

