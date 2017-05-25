/* =====================================================================
//! @param		「Pollen」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/05/02
===================================================================== */

// ヘッダファイルのインクルード
#include "Pollen.h"

// 名前空間
USING_NS_CC;

// 静的メンバの定義
bool Pollen::m_isPollenFlg;

// メンバ関数の定義

// 初期設定
bool Pollen::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// メンバの初期設定
	m_isPollenFlg = true;
	m_time = 0;

	// 花粉画像
	setTexture("object/pollen.png");

	// 画像の初期設定
	setOpacity(0x00);
	
	//音の読み込み
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::SE_KAFUN), false);

	return true;
}

/* =====================================================================
//! 内　容		更新処理
//! 引　数		ダミー引数（float）
//! 戻り値		なし
===================================================================== */
void Pollen::update(float delta)
{
	if (m_time / NUM_SECOND < TIME_POLLEN)
	{
		// フェードイン
		if (getOpacity() < 0xff)
		{
			setOpacity(getOpacity() + 0x01);
		}
	}
	else
	{
		// フェードアウト
		if (getOpacity() > 0x00)
		{
			setOpacity(getOpacity() - 0x01);
		}
		else
		{
			m_isPollenFlg = false;
			removeFromParent();
		}
	}
	
	// 時間計測
	m_time++;
}