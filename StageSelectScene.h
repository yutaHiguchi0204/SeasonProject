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
	cocos2d::Sprite* m_pSprPlayer;						// プレイヤー画像

	int m_touchID;										// タッチしたＩＤ
	
	int m_playerGrpX;									// 画像のx座標
	int m_time;											// 時間計測

	cocos2d::ui::Button* selectButton[NUM_STAGE];		// ステージボタン
	cocos2d::Sequence* m_move_action_sequence;			// Sequenceアクション

	cocos2d::Sprite* m_pStageName;						// ステージ名

	cocos2d::Sprite* m_pItemUIspr;						// アイテムＵＩの画像
	cocos2d::Label* m_pItemUInum;						// アイテムＵＩのアイテム所持数

	cocos2d::ui::Button* m_pSaveButton;					// セーブボタン
	cocos2d::ui::Button* m_pBackButton;					//タイトルに戻るボタン

public:
	CREATE_FUNC(StageSelectScene);
	virtual bool init();

	// シーンを作成する
	static cocos2d::Scene* createScene();

	void update(float delta);

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType)  { if (eventType == cocos2d::ui::Widget::TouchEventType::ENDED){ m_touchID = 0; CharactorMove();} }
	void onButtonTouch2(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType) { if (eventType == cocos2d::ui::Widget::TouchEventType::ENDED){ m_touchID = 1; CharactorMove();} }
	void onButtonTouch3(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType) { if (eventType == cocos2d::ui::Widget::TouchEventType::ENDED){ m_touchID = 2; CharactorMove();} }
	void onButtonTouch4(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType) { if (eventType == cocos2d::ui::Widget::TouchEventType::ENDED){ m_touchID = 3; CharactorMove();} }

	void animationPlayer();	// プレイヤーアニメーション

	void CharactorMove();	//プレイヤーの移動

	// 静的メンバ
	static int m_stageID;
};

