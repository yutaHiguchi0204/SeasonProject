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
int Stage::m_season;

// メンバ関数の定義

bool SeasonBook::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// 季節記の生成
	m_pBook = Sprite::create("object/seasonChanger.png");
	this->addChild(m_pBook);

	// 季節のページの生成
	std::stringstream sFileName;
	sFileName << "object/page_" << SEASON_NAME[Stage::m_season] << ".png";
	m_pPage = Sprite::create(sFileName.str());
	this->addChild(m_pPage);

	// 閉じるボタン
	m_pButtonClose = cocos2d::ui::Button::create("object/button_close.png");
	m_pButtonClose->setPositionY(176.0f);
	this->addChild(m_pButtonClose);

	// 矢印生成
	m_pButtonArrowLeft = cocos2d::ui::Button::create("object/page_arrow.png");
	m_pButtonArrowRight = cocos2d::ui::Button::create("object/page_arrow.png");
	m_pButtonArrowRight->setFlippedX(true);
	m_pButtonArrowLeft->setPositionX(-256.0f);
	m_pButtonArrowRight->setPositionX(256.0f);
	this->addChild(m_pButtonArrowLeft);
	this->addChild(m_pButtonArrowRight);

	// 閉じるボタンが押された時
	m_pButtonClose->addClickEventListener([&](Ref* ref)
	{
		removeFromParent();
		Stage::m_isShowObject = false;
	});

	// 季節記の矢印ボタンが押された時
	m_pButtonArrowLeft->addClickEventListener([&](Ref* ref) { Change(-1); });
	m_pButtonArrowRight->addClickEventListener([&](Ref* ref) { Change(1); });

	return true;
}

/* =====================================================================
//! 内　容		季節換え
//! 引　数		プラスかマイナス（int）
//! 戻り値		なし
===================================================================== */
void SeasonBook::Change(int num)
{
	Stage::m_season += num;

	// 調整
	if (Stage::m_season < static_cast<int>(SEASON::WINTER)) Stage::m_season = Player::m_numBookmark - 1;
	if (Stage::m_season > Player::m_numBookmark - 1)		Stage::m_season = static_cast<int>(SEASON::WINTER);

	// 季節のページを変える
	std::stringstream sFileName;
	sFileName << "object/page_" << SEASON_NAME[Stage::m_season] << ".png";
	m_pPage->setTexture(sFileName.str());
}