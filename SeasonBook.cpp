/* =====================================================================
//! @param		「SeasonBook」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/03/19
===================================================================== */

// ヘッダファイルのインクルード
#include "SeasonBook.h"
#include "PlayScene.h"

// 名前空間
USING_NS_CC;

// 静的メンバの定義
bool PlayScene::m_isChangeSeason;

// メンバ関数の定義

bool SeasonBook::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// 季節換えのページを表示
	m_pBook = Sprite::create("object/seasonChanger.png");
	this->addChild(m_pBook);

	// 閉じるボタン
	m_pButtonClose = cocos2d::ui::Button::create("object/button_close.png");
	m_pButtonClose->setPositionY(160.0f);
	this->addChild(m_pButtonClose);

	// 矢印生成
	m_pButtonArrowLeft = cocos2d::ui::Button::create("object/page_arrow.png");
	m_pButtonArrowRight = cocos2d::ui::Button::create("object/page_arrow.png");
	m_pButtonArrowRight->setFlippedX(true);
	m_pButtonArrowLeft->setPositionX(-256.0f);
	m_pButtonArrowRight->setPositionX(256.0f);
	this->addChild(m_pButtonArrowLeft);
	this->addChild(m_pButtonArrowRight);

	return true;
}

/* =====================================================================
//! 内　容		更新処理
//! 引　数		ダミー引数（float）
//! 戻り値		なし
===================================================================== */
void SeasonBook::update(float delta)
{
	// 閉じるボタンが押されてたら本を閉じる
	if (m_pButtonClose->isHighlighted())
	{
		removeFromParent();
		PlayScene::m_isChangeSeason = false;
	}
}