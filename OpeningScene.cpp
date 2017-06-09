/* =====================================================================
//! @param		「OpeningScene」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/06/07
===================================================================== */

// ヘッダファイルのインクルード
#include "OpeningScene.h"
#include "TitleScene.h"

// 名前空間
USING_NS_CC;

// 定数
const int HERF_COLOR = 127;
const int NUM_LINES = 19;
const int NUM_WINDOW_LINES = 7;
const float TIME_SCENE_TRANS = 72.0f;

// シーン管理
Scene* OpeningScene::createScene()
{
	// シーンを作成する
	auto scene = Scene::create();

	// レイヤーを作成する
	auto layer = OpeningScene::create();

	// レイヤーをシーンに追加する
	scene->addChild(layer);

	// シーンを返す
	return scene;
}

// 初期化
bool OpeningScene::init()
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

	// 背景
	Sprite* back = Sprite::create("opening/back.png");
	back->setPosition(Vec2(0.0f, -WINDOW_HEIGHT));
	back->setAnchorPoint(Vec2(0.0f, 0.0f));
	back->setOpacity(0xff);
	this->addChild(back);
	Sprite* back2 = Sprite::create("opening/back2.png");
	back2->setPosition(Vec2(0.0f, -WINDOW_HEIGHT));
	back2->setAnchorPoint(Vec2(0.0f, 0.0f));
	back2->setOpacity(0x00);
	this->addChild(back2);

	// ボタン画像
	m_pButtonSkip = Sprite::create("opening/button_skip.png");
	m_pButtonSkip->setPosition(Vec2(WINDOW_WIDTH - 128.0f, 32.0f));
	m_pButtonSkip->setOpacity(0x80);
	this->addChild(m_pButtonSkip);

	// タイトルのBGM生成
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::BGM_OP), false);

	// セリフを表示
	DrawLines();

	// 背景を動かしたり色を変えたりする
	back->runAction(Sequence::create(
		MoveTo::create(20.0f, Vec2(0.0f, 0.0f)),
		DelayTime::create(14.0f),
		FadeOut::create(2.0f),
		nullptr
	));
	back2->runAction(Sequence::create(
		MoveTo::create(20.0f, Vec2(0.0f, 0.0f)),
		DelayTime::create(14.0f),
		FadeIn::create(2.0f),
		nullptr
	));

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(OpeningScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(OpeningScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

/* =====================================================================
//! 内　容		更新処理
//! 引　数		ダミー引数（float）
//! 戻り値		なし
===================================================================== */
void OpeningScene::update(float delta)
{
	// フェード
	if (m_time / HERF_COLOR % 2 == 0)	m_pButtonSkip->setOpacity(m_pButtonSkip->getOpacity() + 0x01);
	else								m_pButtonSkip->setOpacity(m_pButtonSkip->getOpacity() - 0x01);

	// 時間計測
	m_time++;
}

/* =====================================================================
//! 内　容		セリフを表示
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void OpeningScene::DrawLines()
{
	Sprite* lines[NUM_LINES];

	// セリフのロード
	for (int i = 0; i < NUM_LINES; i++)
	{
		std::stringstream sFileName;

		sFileName.str("");
		sFileName.clear();

		sFileName << "opening/lines" << i + 1 << ".png";

		lines[i] = Sprite::create(sFileName.str());
		lines[i]->setPosition(0.0f, WINDOW_HEIGHT - i % NUM_WINDOW_LINES * 64.0f);
		lines[i]->setAnchorPoint(Vec2(0.0f, 1.0f));
		lines[i]->setOpacity(0x00);
		this->addChild(lines[i]);
	}

	// セリフを出す
	for (int i = 0; i < NUM_LINES; i++)
	{
		if		(i < NUM_WINDOW_LINES)		lines[i]->runAction(Sequence::create(DelayTime::create(i * 3.0f + 2.0f), FadeIn::create(1.0f), DelayTime::create(22.0f - i * 3.0f), FadeOut::create(1.0f), nullptr));
		else if (i < NUM_WINDOW_LINES + 2)	lines[i]->runAction(Sequence::create(DelayTime::create((i - NUM_WINDOW_LINES) * 3.0f + 26.0f), FadeIn::create(1.0f), DelayTime::create(28.0f - (i - NUM_WINDOW_LINES) * 3.0f), FadeOut::create(1.0f), nullptr));
		else if (i < NUM_WINDOW_LINES * 2)	lines[i]->runAction(Sequence::create(DelayTime::create((i - (NUM_WINDOW_LINES + 2)) * 3.0f + 38.0f), FadeIn::create(1.0f), DelayTime::create(16.0f - (i - (NUM_WINDOW_LINES + 2)) * 3.0f), FadeOut::create(1.0f), nullptr));
		else								lines[i]->runAction(Sequence::create(DelayTime::create((i - (NUM_WINDOW_LINES * 2)) * 3.0f + 56.0f), FadeIn::create(1.0f), nullptr));
	}
	
	// ７２秒後にタイトルシーンへ
	CallFuncAfter(TIME_SCENE_TRANS, [&]() {

		// 次のシーンを作成する
		Scene* nextScene = TitleScene::create();

		// フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// 次のシーンに移行
		_director->replaceScene(nextScene);
	});
}

/* =====================================================================
//! 内　容		タッチの終了処理
//! 引　数		タッチ情報（Touch*）、イベント情報（Event*）
//! 戻り値		なし
===================================================================== */
void OpeningScene::onTouchEnded(Touch* touch, Event* event)
{
	// 次のシーンを作成する
	Scene* nextScene = TitleScene::create();

	// フェードトランジション
	nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

	// 次のシーンに移行
	_director->replaceScene(nextScene);
}