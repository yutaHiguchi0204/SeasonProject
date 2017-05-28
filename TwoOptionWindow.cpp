/* =====================================================================
//! @param		「TwoOptionWindow」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/05/28
===================================================================== */

// ヘッダファイルのインクルード
#include "TwoOptionWindow.h"

// 名前空間
USING_NS_CC;

// 静的メンバ変数の初期化
bool TwoOptionWindow::m_isResetCheck;

// メンバ関数の定義

// 初期化
bool TwoOptionWindow::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// メンバ変数の初期化
	m_isResetCheck = true;

	// 基盤
	setTexture("object/resetCheck.png");

	// ＯＫボタン
	m_pButtonOK = cocos2d::ui::Button::create("object/button_ok.png");
	m_pButtonOK->setPosition(Vec2(160.0f, 96.0f));
	this->addChild(m_pButtonOK);

	// キャンセルボタン
	m_pButtonCancel = cocos2d::ui::Button::create("object/button_cancel.png");
	m_pButtonCancel->setPosition(Vec2(480.0f, 96.0f));
	this->addChild(m_pButtonCancel);

	// ＯＫボタンタップ
	m_pButtonOK->addClickEventListener([&](Ref* ref) {

		// リセット
		GameManager& gm = GameManager::GetInstance();
		gm.ResetPageInfo();

		// 後処理
		runAction(Sequence::create(
			ScaleTo::create(0.5f, 0.0f),
			CallFunc::create([&]() { m_isResetCheck = false; removeFromParent(); }),
			nullptr
		)
		);
	});

	// キャンセルボタンタップ
	m_pButtonCancel->addClickEventListener([&](Ref* ref) {

		// 後処理
		runAction(Sequence::create(
			ScaleTo::create(0.5f, 0.0f),
			CallFunc::create([&]() { m_isResetCheck = false; removeFromParent(); }),
			nullptr
		)
		);
	});

	return true;
}