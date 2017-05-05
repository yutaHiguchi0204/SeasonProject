/* =====================================================================
//! @param		「OperationButton」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/04/20
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <string>
#include "GameManager.h"
#include "ui/CocosGUI.h"

// 定数
const int NUM_ACTION = 3;						// アクション数
const std::string ACTION_NAME[NUM_ACTION] =		// アクション名
{
	"jump",
	"book",
	"signBoard"
};

// 列挙型
enum class BUTTON			// ボタン
{
	LEFT,
	RIGHT,
	ACTION,
	PAUSE
};

enum class ACTION			// アクション
{
	JUMP,
	SEASON_BOOK,
	SIGN_BOARD
};

// クラスの定義
class OperationButton : public cocos2d::ui::Button
{
private:
	ACTION m_actionFlg;							// アクションフラグ（アクションボタンのときのみ変更有）

public:
	CREATE_FUNC(OperationButton);
	virtual bool init();
	bool init(BUTTON button);

	static OperationButton* create(BUTTON button);

	void SetFullBright(bool full = true);				// ボタンの明度設定（ＭＡＸか半透明）

	void ChangeActionFlg(ACTION action);				// アクションフラグの変更
	void ChangeButtonTexture(ACTION action);			// ボタンの画像を変える

	ACTION GetActionFlg();								// アクションフラグを取得する
};