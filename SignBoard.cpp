/* =====================================================================
//! @param		「SignBoard」クラスのソースファイル
//! @create		木下　浩暉
//! @date		17/04/27
===================================================================== */

#include "SignBoard.h"
#include "Stage.h"

USING_NS_CC;

//オブジェクト番号の取得
int SignBoard::GetObjectNumber()
{
	return m_objNumber;
}

//オブジェクト番号の追加(int)
void SignBoard::SetObjectNumber(int SetObj)
{
	//取得した番号を追加する
	m_objNumber = SetObj;
}

/* =====================================================================
//! 内　容		オブジェクト情報の添字と一致している説明盤を表示
//! 引　数		オブジェクト情報ＩＤ（int）
//! 戻り値		なし
===================================================================== */
void SignBoard::DrawBlackBoard(int objNum)
{
	if (GetObjectNumber() == objNum)
	{
		EnabledBlackBoard(true);
	}
}

//説明盤の表示非表示(bool)
void SignBoard::EnabledBlackBoard(bool TorF)
{
	m_blackBoard->setVisible(TorF);
	m_pButtonClose->setVisible(TorF);
}

//説明盤の画像を追加する(int)
void SignBoard::SetBlackBoardTexture(int num)
{
	std::stringstream sFileName;
	sFileName << "object/blackBoard_" << num + 1 << ".png";

	//看板のファイルを追加
	m_blackBoard->setTexture(sFileName.str());
}

bool SignBoard::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// 説明盤の生成
	m_blackBoard = Sprite::create();
	m_blackBoard->setVisible(false);
	this->addChild(m_blackBoard);

	// 閉じるボタンの生成
	m_pButtonClose = cocos2d::ui::Button::create("object/button_close.png");
	m_pButtonClose->setPositionY(160.0f);
	m_pButtonClose->setVisible(false);
	this->addChild(m_pButtonClose);

	// 閉じるボタンが押された時
	m_pButtonClose->addClickEventListener([&](Ref* ref)
	{
		EnabledBlackBoard(false);
		Stage::m_isShowObject = false;
	});

	return true;
}

