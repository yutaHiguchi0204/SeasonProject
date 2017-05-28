/* =====================================================================
//! @param		「MessageWindow」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/05/28
===================================================================== */

// ヘッダファイルのインクルード
#include "MessageWindow.h"

// 名前空間
USING_NS_CC;

// 静的メンバ変数の初期化
bool MessageWindow::m_isSaveCheck;

// メンバ関数の定義

// 初期化
bool MessageWindow::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// メンバ変数の初期化
	m_isSaveCheck = true;

	// 基盤
	setTexture("object/saveMsg.png");

	// ＯＫボタン
	m_pButtonOK = cocos2d::ui::Button::create("object/button_ok.png");
	m_pButtonOK->setPosition(Vec2(320.0f, 96.0f));
	this->addChild(m_pButtonOK);

	// ＯＫボタン確認
	m_pButtonOK->addClickEventListener([&](Ref* ref) {

		// 決定音の生成
		SoundManager& sm = SoundManager::getInstance();
		sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);

		runAction(Sequence::create(
			ScaleTo::create(0.5f, 0.0f),
			CallFunc::create([&]() { m_isSaveCheck = false; removeFromParent(); }),
			nullptr
		)
		);

	});

	return true;
}