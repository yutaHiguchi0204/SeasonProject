/* =====================================================================
//! @param		「Item」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/05/26
===================================================================== */

// ヘッダファイルのインクルード
#include "Item.h"

// 名前空間
USING_NS_CC;

// メンバ関数の定義

// 初期化
bool Item::init()
{
	// 基底クラスの初期化
	if (!Sprite::init())
	{
		// 基底クラスの初期化が失敗なら、異常終了
		return false;
	}

	// 画像設定
	setTexture("object/item_page.png");
	setAnchorPoint(Vec2(0.5f, 0.0f));

	// Ｙ軸で回転するアクションを設定
	runAction(RepeatForever::create(RotateBy::create(4.0f, Vec3(0.0f, 360.0f, 0.0f))));

	return true;
}