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

	setTexture("object/seasonBook.png");

	return true;
}

//フラグ管理
void SeasonBook::Setbookflag()
{
	bool setflag;

	if (setflag != 0)
	{
		setTexture("object/button_book.png");
	}
	else if (setflag == 0)
	{
		setTexture("object/button_action.png");
	}
}