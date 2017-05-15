/* =====================================================================
//! @param		「StageSelectScene」クラスのヘッダファイル
//! @create		松丸　勇輝
//! @date		17/05/01
===================================================================== */
#pragma once

//ヘッダファイルのインクルード
#include "GameManager.h"
#include "ui/CocosGUI.h"

class StageSelectScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* m_pSprPlayer;
	
	int m_playerGrpX;	// 画像のx座標
	int m_time;			// 時間計測

public:
	CREATE_FUNC(StageSelectScene);
	virtual bool init();

	// シーンを作成する
	static cocos2d::Scene* createScene();

	void update(float delta);

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType);

	void animationPlayer();	// プレイヤーアニメーション

	// 静的メンバ
	static int m_stageID;


	/// デバッグ用メンバ変数
	cocos2d::EventListenerKeyboard* keyListener;
	cocos2d::Label* text;
};

