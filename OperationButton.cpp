/* =====================================================================
//! @param		「OperationButton」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/04/20
===================================================================== */

// ヘッダファイルのインクルード
#include "OperationButton.h"
#include <fstream>
#include <sstream>
#include "PlayScene.h"

// 名前空間
USING_NS_CC;

// 定数
const Color3B FULL_COLOR = Color3B(255.0f, 255.0f, 255.0f);
const Color3B HERF_COLOR = Color3B(128.0f, 128.0f, 128.0f);

// メンバ関数の定義

// 初期化（デフォルト）
bool OperationButton::init()
{
	if (!cocos2d::ui::Button::init())
	{
		return false;
	}

	// アクションフラグをデフォルト状態にする（ジャンプボタン）
	m_actionFlg = ACTION::JUMP;

	return true;
}

// 初期化（ボタン指定）
bool OperationButton::init(BUTTON button)
{
	if (!cocos2d::ui::Button::init())
	{
		return false;
	}

	// 画像設定
	switch (button)
	{
	case BUTTON::LEFT:
		loadTextureNormal("object/button_arrow.png");
		setPosition(Vec2(96.0f, 96.0f));
		break;

	case BUTTON::RIGHT:
		loadTextureNormal("object/button_arrow.png");
		setPosition(Vec2(288.0f, 96.0f));
		setFlippedX(true);
		break;

	case BUTTON::ACTION:
		loadTextureNormal("object/button_action.png");
		setPosition(Vec2(WINDOW_WIDTH - 96.0f, 96.0f));
		break;

	case BUTTON::PAUSE:
		loadTextureNormal("object/button_pause.png");
		setPosition(Vec2(88.0f, WINDOW_HEIGHT - 48.0f));
		break;
	}

	// アクションフラグをデフォルト状態にする（ジャンプボタン）
	m_actionFlg = ACTION::JUMP;

	return true;
}

/* =====================================================================
//! 内　容		ボタン生成
//! 引　数		ボタン（BUTTON）
//! 戻り値		なし
===================================================================== */
OperationButton* OperationButton::create(BUTTON button)
{
	OperationButton* btn = new (std::nothrow) OperationButton;
	if (btn && btn->init(button))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

/* =====================================================================
//! 内　容		ボタンの明度設定
//! 引　数		ＭＡＸか暗めか（bool）
//! 戻り値		なし
===================================================================== */
void OperationButton::SetFullBright(bool full)
{
	if (full)	setColor(FULL_COLOR);			// ＭＡＸ
	else		setColor(HERF_COLOR);			// 暗め
}

/* =====================================================================
//! 内　容		アクションフラグの変更
//! 引　数		アクションID（ACTION）
//! 戻り値		なし
===================================================================== */
void OperationButton::ChangeActionFlg(ACTION action)
{
	// アクションフラグの変更
	m_actionFlg = action;

	// ボタンの画像の変更
	ChangeButtonTexture(action);
}

/* =====================================================================
//! 内　容		ボタンの画像を変える
//! 引　数		アクションID（ACTION）
//! 戻り値		なし
===================================================================== */
void OperationButton::ChangeButtonTexture(ACTION action)
{
	std::stringstream sFileName;
	sFileName << "object/button_" << ACTION_NAME[static_cast<int>(action)] << ".png";

	// 背景の変更
	loadTextureNormal(sFileName.str());
}

/* =====================================================================
//! 内　容		アクションフラグの取得
//! 引　数		なし
//! 戻り値		アクションフラグ（ACTION）
===================================================================== */
ACTION OperationButton::GetActionFlg()
{
	return m_actionFlg;
}