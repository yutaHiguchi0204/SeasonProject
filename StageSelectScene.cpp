/* =====================================================================
//! @param		「StageSelectScene」クラスのソースファイル
//! @create		松丸　勇輝
//! @date		17/05/01
===================================================================== */

// ヘッダファイルのインクルード
#include "StageSelectScene.h"
#include "ClearScene.h"
#include "PlayScene.h"

// 名前空間
USING_NS_CC;
using namespace std;

// 静的メンバの定義
int StageSelectScene::m_stageID;

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
	m_touchID = static_cast<int>(STAGE::FLOWER);

	// 背景
	Sprite* back = Sprite::create("background/back_stageSelect.png");
	back->setPosition(480, 270);
	this->addChild(back);

	// ボタン画像
	for (int i = 0; i < STAGEMAX_NUM; i++)
	{
		selectButton[i]= cocos2d::ui::Button::create("object/selectButton.png");
		selectButton[i]->setPosition(Vec2(i % 2 * 704.0f + 128.0f, i * 112.0f + 96.0f));
		addChild(selectButton[i]);
	}
	
	// プレイヤー
	m_pSprPlayer = Sprite::create("object/player.png");
	m_pSprPlayer->setPosition(selectButton[static_cast<int>(STAGE::FLOWER)]->getPosition());
	this->addChild(m_pSprPlayer);

	// アイテムＵＩ設定
	GameManager& gm = GameManager::GetInstance();
	m_pItemUIspr = Sprite::create("object/item_page.png");
	m_pItemUInum = Label::create("0 /100", "HGP行書体", 60);

	std::stringstream strNum;
	strNum << gm.GetPageNum() << " /100";
	m_pItemUInum->setString(strNum.str());

	m_pItemUIspr->setPosition(48.0f, WINDOW_HEIGHT - 48.0f);
	m_pItemUInum->setPosition(192.0f, WINDOW_HEIGHT - 48.0f);
	m_pItemUIspr->setScale(2.0f);
	m_pItemUInum->setColor(Color3B(255, 255, 255));
	this->addChild(m_pItemUIspr);
	this->addChild(m_pItemUInum);
	m_pItemUIspr->runAction(RepeatForever::create(RotateBy::create(4.0f, Vec3(0.0f, 360.0f, 0.0f))));

	// セーブボタン
	m_pSaveButton = cocos2d::ui::Button::create("object/button_dataSave.png");
	m_pSaveButton->setPosition(Vec2(WINDOW_WIDTH - 80.0f, 48.0f));
	this->addChild(m_pSaveButton);

	// データの保存
	m_pSaveButton->addClickEventListener([&](Ref* ref) { gm.ExportPageInfo(); });

	if (gm.GetPageNum() == NUM_ITEM)
	{
		// クリア
		cocos2d::ui::Button* clearButton = cocos2d::ui::Button::create("object/clearObj.png");
		clearButton->setPosition(WINDOW_MIDDLE);
		this->addChild(clearButton);

		// 回転させる
		clearButton->runAction(RepeatForever::create(RotateBy::create(2.0f, Vec3(0.0f, 0.0f, 360.0f))));

		// クリア遷移
		clearButton->addClickEventListener([&](Ref* ref) {

			Scene* nextScene = ClearScene::create();
			nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));
			_director->replaceScene(nextScene);
		});
	}

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	selectButton[0]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch, this));
	selectButton[1]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch2, this));
	selectButton[2]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch3, this));
	selectButton[3]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch4, this));

	//ステージセレクト画面での音生成
	SoundManager& sm = SoundManager::getInstance();
	sm.UncacheGameSound(SOUND::BGM_TITLE);
	sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);

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

// プレイヤーの移動
void StageSelectScene::CharactorMove()
{
	if (m_pSprPlayer->getPosition() == selectButton[m_touchID]->getPosition())
	{
		// ステージ決定音の生成
		SoundManager& sm = SoundManager::getInstance();
		sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);
		
		// 次のシーンを作成する
		Scene* nextScene = PlayScene::create();

		// フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// 次のシーンに移行
		_director->replaceScene(nextScene);

		return;
	}

	//MoveTo* move_action[STAGEMAX_NUM - 1];
	Spawn* move_action[STAGEMAX_NUM - 1];

	int move_distance = m_touchID - m_stageID;

	for (int i = 0; i < STAGEMAX_NUM - 1; i++)
	{
		move_action[i] = nullptr;
	}

	if (move_distance > 0)
	{
		for (int i = 0; i < move_distance; i++)
		{
			MoveTo* move = MoveTo::create(1.0f, selectButton[m_stageID + i + 1]->getPosition());
			
			CallFunc* func = nullptr;

			if (selectButton[m_stageID + i]->getPositionX() > selectButton[m_stageID + i + 1]->getPositionX())
				func = CallFunc::create([&]() { m_pSprPlayer->setFlippedX(true); });
			else
				func = CallFunc::create([&]() { m_pSprPlayer->setFlippedX(false); });

			move_action[i] = Spawn::create(move, func, nullptr);
		}
	}
	else
	{
		move_distance *= -1;

		for (int i = 0; i < move_distance; i++)
		{
			MoveTo* move = MoveTo::create(1.0f, selectButton[m_stageID - i - 1]->getPosition());

			CallFunc* func = nullptr;

			if (selectButton[m_stageID - i]->getPositionX() > selectButton[m_stageID - i - 1]->getPositionX())
				func = CallFunc::create([&]() { m_pSprPlayer->setFlippedX(true); });
			else
				func = CallFunc::create([&]() { m_pSprPlayer->setFlippedX(false); });

			move_action[i] = Spawn::create(move, func, nullptr);
		}
	}

	m_move_action_sequence = Sequence::create(move_action[0], move_action[1], move_action[2], nullptr);

	if (!m_pSprPlayer->getActionByTag(1))
	{
		m_pSprPlayer->stopActionByTag(1);
		m_move_action_sequence->setTag(1);
		m_pSprPlayer->runAction(m_move_action_sequence);

		m_stageID = m_touchID;

		// ステージセレクト音の生成
		SoundManager& sm = SoundManager::getInstance();
		sm.UncacheGameSound(SOUND::SE_DECISION);
		sm.PlayGameSound(static_cast<int>(SOUND::SE_STAGESELECT), false);
	}

}