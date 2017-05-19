/* =====================================================================
//! @param		「StageSelectScene」クラスのソースファイル
//! @create		松丸　勇輝
//! @date		17/05/01
===================================================================== */

// ヘッダファイルのインクルード
#include "StageSelectScene.h"
#include "PlayScene.h"

// 名前空間
USING_NS_CC;
using namespace std;

// シーン管理
Scene* StageSelectScene::createScene()
{
	// シーンを作成する
	auto scene = Scene::create();

	// レイヤーを作成する
	auto layer = StageSelectScene::create();

	// レイヤーをシーンに追加する
	scene->addChild(layer);

	// シーンを返す
	return scene;
}

// 初期化
bool StageSelectScene::init()
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
	m_stageID = static_cast<int>(STAGE::FLOWER);
	m_touchID = 0;

	// 背景
	Sprite* back = Sprite::create("background/back_stageSelect.png");
	back->setPosition(480, 270);
	this->addChild(back);

	// ボタン画像
	for (int i = 0; i < STAGEMAX_NUM; i++)
	{
		selectButton[i]= cocos2d::ui::Button::create("object/selectButton.png");
		selectButton[i]->setPosition(Vec2(i % 2 * 704.0f + 128.0f, i * 88.0f + 96.0f));
		addChild(selectButton[i]);
	}
	
	// プレイヤー
	m_pSprPlayer = Sprite::create("object/player1.png");
	m_pSprPlayer->setPosition(selectButton[static_cast<int>(STAGE::FLOWER)]->getPosition());
	this->addChild(m_pSprPlayer);

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	
	
	selectButton[0]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch, this));
	selectButton[1]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch2, this));
	selectButton[2]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch3, this));
	selectButton[3]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch4, this));

	return true;
}

void StageSelectScene::update(float delta)
{
	
	// プレイヤーアニメーション
	if (m_time % SPEED_ANIMATION == 0) animationPlayer();

	// 画像の変更
	m_pSprPlayer->setTextureRect(Rect(m_playerGrpX, 0, SIZE_PLAYER, SIZE_PLAYER));

	// 時間計測
	m_time++;

}

// プレイヤーアニメーション
void StageSelectScene::animationPlayer()
{
	m_playerGrpX += SIZE_PLAYER;
	if (m_playerGrpX >= SIZE_PLAYER * 3)
	{
		m_playerGrpX = 0;
	}
}

//プレイヤーの移動
void StageSelectScene::CharactorMove()
{
	if (m_pSprPlayer->getPosition() == selectButton[m_touchID]->getPosition())
	{
		// 次のシーンを作成する
		Scene* nextScene = PlayScene::create();

		//フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// 次のシーンに移行
		_director->replaceScene(nextScene);

		return;
	}

	MoveTo* move_action[STAGEMAX_NUM - 1];

	int move_distance = m_touchID - m_stageID;

	for (int i = 0; i < STAGEMAX_NUM - 1; i++)
	{
		move_action[i] = nullptr;
	}

	if (move_distance > 0)
	{

		for (int i = 0; i < move_distance; i++)
		{

			move_action[i] = MoveTo::create(1.0f, selectButton[m_stageID + i + 1]->getPosition());

		}
	}
	else
	{
		move_distance *= -1;

		for (int i = 0; i < move_distance; i++)
		{
			move_action[i] = MoveTo::create(1.0f, selectButton[m_stageID - i - 1]->getPosition());
		}
	}

	m_move_action_sequence = Sequence::create(move_action[0], move_action[1], move_action[2], nullptr);

	if (!m_pSprPlayer->getActionByTag(1))
	{
		m_pSprPlayer->stopActionByTag(1);
		m_move_action_sequence->setTag(1);
		m_pSprPlayer->runAction(m_move_action_sequence);

		m_stageID = m_touchID;
	}

}
