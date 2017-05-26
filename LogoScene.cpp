/* =====================================================================
//! @param		「LogoScene」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/05/23
===================================================================== */

// ヘッダファイルのインクルード
#include "LogoScene.h"
#include "TitleScene.h"

// 名前空間
USING_NS_CC;

// シーン管理
Scene* LogoScene::createScene()
{
	// シーンを作成する
	auto scene = Scene::create();

	// レイヤーを作成する
	auto layer = LogoScene::create();

	// レイヤーをシーンに追加する
	scene->addChild(layer);

	// シーンを返す
	return scene;
}

// 初期化
bool LogoScene::init()
{
	// 基底クラスの初期化
	if (!Scene::init())
	{
		// 基底クラスの初期化が失敗なら、異常終了
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// メンバ変数の初期化
	m_time = 0;

	// ロゴ画像
	m_pLogo = Sprite::create("background/back_logo.png");
	m_pLogo->setPosition(WINDOW_MIDDLE);
	m_pLogo->setOpacity(0x00);
	this->addChild(m_pLogo);

	// フェード
	m_pLogo->runAction(Sequence::create(
		FadeIn::create(2.0f),
		FadeOut::create(2.0f),
		CallFunc::create([&]() {
			// 次のシーンを作成する
			Scene* nextScene = TitleScene::create();
			// 次のシーンに移行
			_director->replaceScene(nextScene);
		}),
		nullptr
		)
	);

	return true;
}