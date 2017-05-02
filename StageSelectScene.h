/* =====================================================================
//! @param		「StageSelectScene」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/05/01
===================================================================== */
#pragma once

//ヘッダファイルのインクルード
#include "GameManager.h"

class StageSelectScene :cocos2d::Scene
{
public:
	CREATE_FUNC(StageSelectScene);
	virtual bool init();

	// シーンを作成する
	static cocos2d::Scene* createScene();

	void update(float delta);

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);

};

