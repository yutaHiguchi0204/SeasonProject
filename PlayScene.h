/* =====================================================================
//! @param		「PlayScene」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/03/04
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"
#include "Player.h"
#include "SeasonBook.h"
#include "Stage.h"
#include "ui/CocosGUI.h"

// クラスの定義
class PlayScene : public cocos2d::Scene
{
private:
	int m_mapInfo[NUM_ROW][NUM_COLUMN];					// マップ情報

	Stage* m_pStage;									// ステージ

	//cocos2d::Sprite* m_pSignBoard01;					// 看板１
	//cocos2d::Sprite* m_pBoard01;						// 説明盤１

	Player* m_pPlayer;						// プレイヤー
	//SeasonBook* m_pSeasonBook;				// 季節記

	cocos2d::ui::Button* m_pButton[NUM_BUTTON];			// ボタン

public:
	CREATE_FUNC(PlayScene);
	virtual bool init();

	// シーンを作成する
	static cocos2d::Scene* createScene();

	void update(float delta);				// 更新処理

	//bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	static int m_timeCnt;					// 時間計測
};