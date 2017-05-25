/* =====================================================================
//! @param		「Particle」クラスのソースファイル
//! @create		松丸　勇輝
//! @date		17/05/19
===================================================================== */
// ヘッダファイルのインクルード
#include "Particle.h"
#include "Stage.h"

// 名前空間
USING_NS_CC;

// メンバ関数の定義

bool Particle::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// プリセットの初期設定
	std::stringstream sFileName;
	sFileName << "particle/particle_" << SEASON_NAME[Stage::m_season] << ".plist";
	m_pParticle = ParticleSystemQuad::create(sFileName.str());

	// パーティクルの座標設定（左上）
	m_pParticle->setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT);

	// パーティクルのメモリリーク回避
	m_pParticle->setAutoRemoveOnFinish(true);

	// パーティクル開始
	m_pParticle->resetSystem();

	// パーティクルをノードにつなぐ
	this->addChild(m_pParticle);

	return true;
}

/* =====================================================================
//! 内　容		パーティクルのスクロール
//! 引　数		カメラの座標x（float）
//! 戻り値		なし
===================================================================== */
void Particle::ParticleScroll(float cameraX)
{
	m_pParticle->setPositionX(cameraX);
}