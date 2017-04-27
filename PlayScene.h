/* =====================================================================
//! @param		「PlayScene」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/03/04
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"
#include "OperationButton.h"
#include "Stage.h"

// クラスの定義
class PlayScene : public cocos2d::Scene
{
private:
	Stage* m_pStage;									// ステージ

public:
	CREATE_FUNC(PlayScene);
	virtual bool init();

	// シーンを作成する
	static cocos2d::Scene* createScene();

	void update(float delta);				// 更新処理

	// 静的メンバ
	static int m_timeCnt;									// 時間計測
	static OperationButton* m_pButton[NUM_BUTTON];			// ボタン
};