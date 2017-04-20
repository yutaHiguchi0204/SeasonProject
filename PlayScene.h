/* =====================================================================
//! @param		「PlayScene」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/03/04
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"
#include "OperationButton.h"
#include "Player.h"
#include "SeasonBook.h"
#include "Stage.h"

// クラスの定義
class PlayScene : public cocos2d::Scene
{
private:
	int m_mapInfo[NUM_ROW][NUM_COLUMN];					// マップ情報

	Stage* m_pStage;									// ステージ

	Player* m_pPlayer;									// プレイヤー

public:
	CREATE_FUNC(PlayScene);
	virtual bool init();

	// シーンを作成する
	static cocos2d::Scene* createScene();

	void update(float delta);				// 更新処理

	//bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	// 静的メンバ
	static int m_timeCnt;									// 時間計測
	static OperationButton* m_pButton[NUM_BUTTON];			// ボタン
};