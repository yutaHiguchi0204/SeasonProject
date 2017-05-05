/* =====================================================================
//! @param		「PlayScene」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/03/04
===================================================================== */

// ヘッダファイルのインクルード
#include "PlayScene.h"

// 名前空間
USING_NS_CC;
using namespace std;

// 静的メンバの定義
bool Stage::m_isShowObject;
bool Stage::m_leftFlag;
bool Stage::m_rightFlag;

// メンバ関数の定義

// シーン管理
Scene* PlayScene::createScene()
{
	// シーンを作成する
	auto scene = Scene::create();

	// レイヤーを作成する
	auto layer = PlayScene::create();

	// レイヤーをシーンに追加する
	scene->addChild(layer);

	// シーンを返す
	return scene;
}

// 初期化
bool PlayScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// 各データの初期設定
	m_timeCnt = 0;								// 時間計測

	// ステージ
	m_pStage = Stage::create();
	this->addChild(m_pStage);

	// ボタン生成
	m_pButton[static_cast<int>(BUTTON::LEFT)]	= OperationButton::create(BUTTON::LEFT);
	m_pButton[static_cast<int>(BUTTON::RIGHT)]	= OperationButton::create(BUTTON::RIGHT);
	m_pButton[static_cast<int>(BUTTON::ACTION)] = OperationButton::create(BUTTON::ACTION);
	m_pButton[static_cast<int>(BUTTON::PAUSE)]	= OperationButton::create(BUTTON::PAUSE);

	// ボタンをシーンにつなぐ
	for (int i = 0; i < NUM_BUTTON; i++) this->addChild(m_pButton[i]);

	return true;
}

/* =====================================================================
//! 内　容		更新処理
//! 引　数		ダミー引数（float）
//! 戻り値		なし
===================================================================== */
void PlayScene::update(float delta)
{
	// スクロール
	m_pStage->Scroll();

	// ボタンの明るさ
	m_pButton[static_cast<int>(BUTTON::LEFT)]->SetFullBright();
	m_pButton[static_cast<int>(BUTTON::RIGHT)]->SetFullBright();

	// アクションボタンの初期化（ジャンプボタン）
	m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::JUMP);

	// 当たり判定
	m_pStage->CheckCollision();

	// 時間計測
	m_timeCnt++;

	// ボタンが押されていたらプレイヤーを移動させる
	if (!Stage::m_isShowObject)
	{
		// 移動ボタンが押されたときの処理
		if (!Stage::m_leftFlag)
			m_pStage->CheckButtonHighlighted(BUTTON::LEFT);
		if (!Stage::m_rightFlag)
			m_pStage->CheckButtonHighlighted(BUTTON::RIGHT);

		// アクションボタンが押されたときの処理
		m_pStage->CheckButtonHighlighted(BUTTON::ACTION);
	}

	// ポーズボタンが押されたらポーズ画面を出す
	m_pStage->CheckButtonHighlighted(BUTTON::PAUSE);

	// 左右で進めない場合はその時に応じてボタンの明度を変える
	if		(Stage::m_leftFlag)
		m_pButton[static_cast<int>(BUTTON::LEFT)]->SetFullBright(false);
	else if (Stage::m_rightFlag)
		m_pButton[static_cast<int>(BUTTON::RIGHT)]->SetFullBright(false);

	// アクションボタンの明度を戻す
	if ((!Player::m_isJump && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::JUMP)				||
		(!Stage::m_isShowObject && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::SEASON_BOOK)	||
		(!Stage::m_isShowObject && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::SIGN_BOARD))
	{
		m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright();
	}
}