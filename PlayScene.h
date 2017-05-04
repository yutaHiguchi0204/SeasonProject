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
	// ステージ
	Stage* m_pStage;

	cocos2d::Sprite* Pauseback;
	cocos2d::ui::Button* m_pTitleButton;
	cocos2d::ui::Button* m_pGameBackButton;


public:
	CREATE_FUNC(PlayScene);
	virtual bool init();

	// シーンを作成する
	static cocos2d::Scene* createScene();

	void update(float delta);				// 更新処理

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType);

	// 静的メンバ
	static int m_timeCnt;									// 時間計測
	static OperationButton* m_pButton[NUM_BUTTON];			// ボタン
	//ポーズボタン
	cocos2d::ui::Button* m_pPauseButton;
	//カメラ
	cocos2d::Camera* m_pCamera;
	
	void EnabledPauseback(bool TorF);
};