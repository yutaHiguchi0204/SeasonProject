/* =====================================================================
//! @param		「ClearScene」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/05/05
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"

// クラスの定義
class ClearScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* m_pBack;			// 背景
	cocos2d::Sprite* m_pMsgBack;		// 戻るメッセージ

	int m_time;

public:
	CREATE_FUNC(ClearScene);
	virtual bool init();

	// シーンを作成する
	static cocos2d::Scene* createScene();

	// 更新処理
	void update(float delta);

	// タッチ処理
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* pEvent);
};