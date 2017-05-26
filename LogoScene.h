/* =====================================================================
//! @param		「LogoScene」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/05/25
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"

// クラスの定義
class LogoScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* m_pLogo;
	int m_time;

public:
	CREATE_FUNC(LogoScene);
	virtual bool init();

	// シーンを作成する
	static cocos2d::Scene* createScene();

	void update(float delta);
};