/* =====================================================================
//! @param		「Background」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/04/01
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"

// クラスの定義
class Background : public cocos2d::Sprite
{
private:
	cocos2d::ParticleSystemQuad* m_pParticle;		// パーティクル

public:
	CREATE_FUNC(Background);
	virtual bool init();

	void Change(int season);						// 背景の変更
	void ParticleScroll(float cameraX);				// パーティクルのスクロール
};