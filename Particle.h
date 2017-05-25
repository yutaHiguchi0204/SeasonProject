/* =====================================================================
//! @param		「Particle」クラスのヘッダファイル
//! @create		松丸　勇輝
//! @date		17/05/19
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GameManager.h"

// クラスの定義
class Particle : public cocos2d::Sprite
{
private:
	cocos2d::ParticleSystemQuad* m_pParticle;		// パーティクル

public:
	CREATE_FUNC(Particle);
	virtual bool init();

	void ParticleScroll(float cameraX);				// パーティクルのスクロール
};