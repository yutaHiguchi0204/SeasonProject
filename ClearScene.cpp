/* =====================================================================
//! @param		「ClearScene」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/05/05
===================================================================== */

// ヘッダファイルのインクルード
#include "ClearScene.h"
#include "StageSelectScene.h"

// 名前空間
USING_NS_CC;
using namespace std;

// 定数
const int HERF_COLOR = 127;

// メンバ関数の定義

// シーン管理
Scene* ClearScene::createScene()
{
	// シーンを作成する
	auto scene = Scene::create();

	// レイヤーを作成する
	auto layer = ClearScene::create();

	// レイヤーをシーンに追加する
	scene->addChild(layer);

	// シーンを返す
	return scene;
}

// 初期化
bool ClearScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// メンバ変数の初期化
	m_time = 0;

	// 背景
	m_pBack = Sprite::create("background/back_clear.png");
	m_pBack->setPosition(WINDOW_MIDDLE);
	this->addChild(m_pBack);

	// ボタン画像
	m_pMsgBack = Sprite::create("object/button_clearBack.png");
	m_pMsgBack->setPosition(Vec2(WINDOW_WIDTH - 80.0f, WINDOW_HEIGHT - 32.0f));
	m_pMsgBack->setOpacity(0x80);
	this->addChild(m_pMsgBack);

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ClearScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	
	//決定音の生成
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);
	// クリアのBGM生成
	sm.PlayGameSound(static_cast<int>(SOUND::BGM_CLEAR), false);

	return true;
}

/* =====================================================================
//! 内　容		更新処理
//! 引　数		ダミー引数（float）
//! 戻り値		なし
===================================================================== */
void ClearScene::update(float delta)
{
	// フェード
	if (m_time / HERF_COLOR % 2 == 0)	m_pMsgBack->setOpacity(m_pMsgBack->getOpacity() + 0x01);
	else								m_pMsgBack->setOpacity(m_pMsgBack->getOpacity() - 0x01);

	// 時間計測
	m_time++;
}

/* =====================================================================
//! 内　容		タッチ処理
//! 引　数		タッチ情報（Touch）、イベント情報（Event）
//! 戻り値		タッチされたか否か（bool）
===================================================================== */
bool ClearScene::onTouchBegan(Touch* touch, Event* pEvent)
{
	//決定音を生成
	SoundManager& sm = SoundManager::getInstance();
	sm.UncacheGameSound(SOUND::BGM_CLEAR);
	sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);

	// 次のシーンを作成する
	Scene* nextScene = StageSelectScene::create();

	// フェードトランジション
	nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

	// 次のシーンに移行
	_director->replaceScene(nextScene);

	return false;
}