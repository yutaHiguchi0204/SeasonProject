/* =====================================================================
//! @param		「Background」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/04/01
===================================================================== */

// ヘッダファイルのインクルード
#include "Background.h"

// 名前空間
USING_NS_CC;

// メンバ関数の定義

bool Background::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// 画像の初期設定
	setTexture("background/back_spring.png");

	// プリセットの初期設定
	m_pParticle = ParticleSystemQuad::create("particle/particle_spring.plist");

	// パーティクルのメモリリーク回避
	m_pParticle->setAutoRemoveOnFinish(true);

	// パーティクル開始
	m_pParticle->resetSystem();

	// パーティクルの座標設定（左上）
	m_pParticle->setPosition(WINDOW_WIDTH / 3, WINDOW_HEIGHT);

	// パーティクルをノードにつなぐ
	this->addChild(m_pParticle);

	// 位置の初期設定
	setPosition(WINDOW_MIDDLE);

	return true;
}

/* =====================================================================
//! 内　容		背景の変更
//! 引　数		季節（int）
//! 戻り値		なし
===================================================================== */
void Background::Change(int season)
{
	std::stringstream sFileName;
	sFileName << "background/back_" << SEASON_NAME[season] << ".png";

	// 背景の変更
	setTexture(sFileName.str());

	//夏の季節だけ非表示
	if (season == static_cast<int>(SEASON::SUMMER))
	{
		m_pParticle->setVisible(false);
	}

	// 夏以外はパーティクルを出す
	if (season != static_cast<int>(SEASON::SUMMER))
	{
		// ファイル名のリセット
		sFileName.str("");
		sFileName.clear();

		//パーティクルの表示
		m_pParticle->setVisible(true);

		sFileName << "particle/particle_" << SEASON_NAME[season] << ".plist";

		// パーティクルの変更
		m_pParticle->initWithFile(sFileName.str());
	}
}