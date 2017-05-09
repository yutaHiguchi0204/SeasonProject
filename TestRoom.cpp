/* =====================================================================
//! @param		デバッグ用
//! @create		樋口　裕太
//! @date		17/03/05
===================================================================== */
#include "TestRoom.h"

USING_NS_CC;

//bool Player::m_isJump;

bool Test::init()
{
	if (!Scene::init())
	{
		return false;
	}

	m_season = static_cast<int>(SEASON::SPRING);
	//m_timeCnt = 0;

	// 背景
	m_pBack = Sprite::create("background/back_spring.png");
	m_pBack->setPosition(Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	this->addChild(m_pBack);

	// ボタン
	m_pButtonLeft = cocos2d::ui::Button::create("object/button_arrow.png");
	m_pButtonRight = cocos2d::ui::Button::create("object/button_arrow.png");
	m_pButtonAction = cocos2d::ui::Button::create("object/button_action.png");
	m_pButtonRight->setFlippedX(true);
	m_pButtonLeft->setPosition(Vec2(96.0f, 96.0f));
	m_pButtonRight->setPosition(Vec2(288.0f, 96.0f));
	m_pButtonAction->setPosition(Vec2(WINDOW_WIDTH - 96.0f, 96.0f));
	this->addChild(m_pButtonLeft, 1);
	this->addChild(m_pButtonRight, 1);
	this->addChild(m_pButtonAction, 1);

	// プレイヤー
	m_pPlayer = Player::create();
	m_pPlayer->setPosition(Vec2(64.0f, 216.0f));
	this->addChild(m_pPlayer, 1);

	// 看板
	m_pSignBoard = Sprite::create("object/signBoard.png");
	m_pSignBoard->setPosition(Vec2(216.0f, 216.0f));
	this->addChild(m_pSignBoard);

	// 説明盤
	m_pBoard = Sprite::create("object/blackboard.png");
	m_pBoard->setPosition(Vec2(WINDOW_WIDTH / 2, 352.0f));
	m_pBoard->setVisible(false);
	this->addChild(m_pBoard);

	// イベントリスナー作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	// イベントリスナーに各コールバック関数をセットする
	listener->onTouchBegan = CC_CALLBACK_2(Test::onTouchBegan, this);

	// イベントリスナー登録
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Import();
	TestRoom();

	scheduleUpdate();

	return true;
}

void Test::update(float delta)
{
	//m_timeCnt++;

	// プレイヤーに重力をかける
	//m_pPlayer->Fall(m_map, m_pTip, m_season);

	// ボタンが押されていたらプレイヤーを移動させる
	if (m_pButtonLeft->isHighlighted())
	{
		m_pPlayer->Move(-SPEED_MOVE_PLAYER);
	}
	else if (m_pButtonRight->isHighlighted())
	{
		m_pPlayer->Move(SPEED_MOVE_PLAYER);
	}

	// アクションボタンが押されたらプレイヤーをジャンプさせる
	if (m_pButtonAction->isHighlighted() && !Player::m_isJump)
	{
		m_pPlayer->Jump();
		m_pButtonAction->setColor(Color3B(128.0f, 128.0f, 128.0f));

		// ジャンプ終了後にフラグを降ろす
		CallFuncAfter(1.0f, [&]()
		{
			Player::m_isJump = false;
			m_pButtonAction->setColor(Color3B(255.0f, 255.0f, 255.0f));
		});
	}

	// プレイヤーと看板の当たり判定
	Rect rectPlayer = m_pPlayer->getBoundingBox();
	Rect rectSignBoard = m_pSignBoard->getBoundingBox();
	if (rectPlayer.intersectsRect(rectSignBoard))
	{
		m_pBoard->setVisible(true);
	}
	else
	{
		m_pBoard->setVisible(false);
	}
}

void Test::TestRoom()
{
	for (int i = 0; i < NUM_ROW; i++)
	{
		for (int j = 0; j < NUM_COLUMN; j++)
		{
			m_pTip[i][j] = Sprite::create();
			m_pTip[i][j]->setAnchorPoint(Vec2(0.0f, 1.0f));
			m_pTip[i][j]->setPosition(Vec2(j * SIZE_TILE, i * SIZE_TILE + SIZE_TILE));
			this->addChild(m_pTip[i][j]);

			if (m_map[i][j] == static_cast<int>(TILE::BLOCK))
			{
				m_pTip[i][j]->setTexture("tile/tile_spring.png");
			}
			else if (m_map[i][j] == static_cast<int>(TILE::WATER))
			{
				m_pTip[i][j]->setTexture("tile/tile_water.png");
			}
			else
			{
				m_pTip[i][j]->removeFromParent();
				m_pTip[i][j] = nullptr;
			}
		}
	}
}

void Test::ChangeSeason()
{
	std::stringstream sFileName;
	sFileName << "background/back_" << SEASON_NAME[m_season] << ".png";
	m_pBack->setTexture(sFileName.str());

	sFileName.str("");
	sFileName.clear();

	sFileName << "tile/tile_" << SEASON_NAME[m_season] << ".png";
	for (int i = 0; i < NUM_ROW; i++)
	{
		for (int j = 0; j < NUM_COLUMN; j++)
		{
			if (m_map[i][j] == static_cast<int>(TILE::BLOCK))
			{
				m_pTip[i][j]->setTexture(sFileName.str());
			}

			// 冬なら水を氷に変える
			if (m_season == static_cast<int>(SEASON::WINTER) && m_map[i][j] == static_cast<int>(TILE::WATER))
			{
				m_pTip[i][j]->setTexture("tile/tile_ice.png");
			}
			else if (m_map[i][j] == static_cast<int>(TILE::WATER))
			{
				m_pTip[i][j]->setTexture("tile/tile_water.png");
			}
		}
	}
}

void Test::Import()
{
	// ファイルのフルパスを取得
	std::string filePath = FileUtils::getInstance()->fullPathForFilename("data/mapData_stageTest.csv");
	ssize_t size;

	// データ読み込み
	unsigned char* data = FileUtils::getInstance()->getFileData(filePath, "r", &size);

	// データからストリングストリーム作成
	std::stringstream ss((char*)data);
	std::string csvLine;

	// マップデータ読み込み
	int i = 0;
	while (getline(ss, csvLine))
	{
		std::istringstream csvStream(csvLine);
		std::string csvCol;

		int j = 0;
		while (getline(csvStream, csvCol, ','))
		{
			m_map[i][j] = atoi(csvCol.c_str());
			j++;
		}

		i++;
	}
}

bool Test::onTouchBegan(Touch* touch, Event* unused_event)
{
	m_season++;
	if (m_season >= NUM_SEASON)
		m_season = static_cast<int>(SEASON::SPRING);

	ChangeSeason();

	return true;
}