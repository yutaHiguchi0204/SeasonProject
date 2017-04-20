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

	//// プリセットの初期設定
	//m_pParticle = ParticleSystemQuad::create("background/particle_spring.plist");

	//// パーティクルのメモリリーク回避
	//m_pParticle->setAutoRemoveOnFinish(true);

	//// パーティクル開始
	//m_pParticle->resetSystem();

	//// パーティクルの座標設定（左上）
	//m_pParticle->setPosition(Vec2(0.0f, WINDOW_HEIGHT));

	//// パーティクルをノードにつなぐ
	//this->addChild(m_pParticle);

	// 位置の初期設定
	setPosition(Vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f));

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

	//// ファイル名のリセット
	//sFileName.str("");
	//sFileName.clear();

	//sFileName << "background/particle_" << SEASON_NAME[season] << ".png";

	//// パーティクルの変更
	//m_pParticle->initWithFile(sFileName.str());
}