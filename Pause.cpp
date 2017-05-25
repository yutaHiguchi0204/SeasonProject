/* =====================================================================
//! @param		「Pause」クラスのソースファイル
//! @create		木下　浩輝
//! @date		17/05/01
===================================================================== */

// ヘッダファイルのインクルード
#include "Pause.h"
#include "Stage.h"
#include "StageSelectScene.h"
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
	m_pPauseButtonBack->setPosition(Vec2(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF - 32.0f));
	this->addChild(m_pPauseButtonBack);

	// タイトルに戻るボタンの生成
	m_pPauseButtonTitle = cocos2d::ui::Button::create("pause/button_backTitle.png");
	m_pPauseButtonTitle->setPosition(Vec2(WINDOW_WIDTH_HERF - 192.0f, WINDOW_HEIGHT_HERF - 96.0f));
	this->addChild(m_pPauseButtonTitle);

	// ステージ選択画面に戻るボタンの生成
	m_pPauseButtonSelect = cocos2d::ui::Button::create("pause/button_backSelect.png");
	m_pPauseButtonSelect->setPosition(Vec2(WINDOW_WIDTH_HERF + 128.0f, WINDOW_HEIGHT_HERF - 96.0f));
	this->addChild(m_pPauseButtonSelect);

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
		// 後処理
		Stage::m_isPause = false;
		removeFromParent();
	}
	// タイトルに戻るボタンが押されたら
	else if (m_pPauseButtonTitle->isHighlighted())
	{
		// 次のシーンを作成する
		Scene* nextScene = TitleScene::createScene();

		// フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// 次のシーンに移行
		_director->replaceScene(nextScene);

		unscheduleUpdate();
	}
	// ステージ選択画面に戻るボタンが押されたら
	else if (m_pPauseButtonSelect->isHighlighted())
	{
		// 次のシーンを作成する
		Scene* nextScene = StageSelectScene::createScene();

		// フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// 次のシーンに移行
		_director->replaceScene(nextScene);

		unscheduleUpdate();
	}
}