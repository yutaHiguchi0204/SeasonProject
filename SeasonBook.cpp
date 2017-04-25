/* =====================================================================
//! @param		「SeasonBook」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/03/19
===================================================================== */

// ヘッダファイルのインクルード
#include "SeasonBook.h"

// 名前空間
USING_NS_CC;

// メンバ関数の定義

bool SeasonBook::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// 季節換えのページを表示
	m_pBook = Sprite::create("object/seasonChanger.png");
	this->addChild(m_pBook, 4);

	return true;
}