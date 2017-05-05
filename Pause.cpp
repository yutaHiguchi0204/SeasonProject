/* =====================================================================
//! @param		「Pause」クラスのソースファイル
//! @create		木下　浩輝
//! @date		17/05/01
===================================================================== */

// ヘッダファイルのインクルード
#include "Pause.h"
#include "Stage.h"
#include "TitleScene.h"

// 名前空間
USING_NS_CC;
using namespace std;

// メンバ関数の定義

// 初期化
bool Pause::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// ポーズ画面の設定
	setTexture("pause/pauseBack.png");

	// メイン画面の設定
	m_pPauseMain = Sprite::create("pause/pause.png");
	m_pPauseMain->setPosition(Vec2(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF));
	this->addChild(m_pPauseMain);

	// ゲームに戻るボタンの生成
	m_pPauseButtonBack = cocos2d::ui::Button::create("pause/button_backGame.png");
	m_pPauseButtonBack->setPosition(Vec2(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF + 16.0f));
	this->addChild(m_pPauseButtonBack);

	// タイトルに戻るボタンの生成
	m_pPauseButtonTitle = cocos2d::ui::Button::create("pause/button_backTitle.png");
	m_pPauseButtonTitle->setPosition(Vec2(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF - 112.0f));
	this->addChild(m_pPauseButtonTitle);

	return true;
}

/* =====================================================================
//! 内　容		更新処理
//! 引　数		ダミー引数（float）
//! 戻り値		なし
===================================================================== */
void Pause::update(float delta)
{
	// ゲームに戻るボタンが押されたら
	if (m_pPauseButtonBack->isHighlighted())
	{
		ClosePause();
	}
	// タイトルに戻るボタンが押されたら
	else if (m_pPauseButtonTitle->isHighlighted())
	{
		ClosePause(true);
	}
}

/* =====================================================================
//! 内　容		ポーズ画面を閉じる
//! 引　数		プレイシーンを抜けるかどうか（bool）
//! 戻り値		なし
===================================================================== */
void Pause::ClosePause(bool sceneOut)
{
	if (sceneOut)
	{
		// 次のシーンを作成する
		Scene* nextScene = TitleScene::createScene();

		//フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// 次のシーンに移行
		_director->replaceScene(nextScene);
	}

	// 後処理
	Stage::m_isPause = false;
	removeFromParent();
}