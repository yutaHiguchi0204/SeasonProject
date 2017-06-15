/* =====================================================================
//! @param		「Stage」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/04/01
===================================================================== */

// ヘッダファイルのインクルード
#include "Stage.h"
#include "ClearScene.h"
#include "PlayScene.h"
#include "StageSelectScene.h"

// 名前空間
USING_NS_CC;

// 静的メンバの定義
int Stage::m_season;
bool Stage::m_isLeftCollision;
bool Stage::m_isRightCollision;
bool Stage::m_isTopCollision;
bool Stage::m_isShowObject;
bool Stage::m_isPause;

// メンバ関数の定義

// 初期化
bool Stage::init()
{
	if (!Node::init())
	{
		return false;
	}

	// 更新処理準備
	scheduleUpdate();

	// メンバの初期設定
	m_season = static_cast<int>(SEASON::SPRING);		// 季節
	m_seasonBefore = m_season;							// 季節の確定
	m_isLeftCollision = false;							// 左判定フラグ
	m_isRightCollision = false;							// 右判定フラグ
	m_isTopCollision = false;							// 上判定フラグ
	m_isShowObject = false;								// オブジェクトを参照しているかどうか
	m_isPause = false;									// ポーズ中かどうか
	Pollen::m_isPollenFlg = false;						// 花粉フラグをおろしておく
	m_numTiles = 0;										// タイル数
	m_numItems = 0;										// アイテム数
	m_numGimmicks = 0;									// ギミック数
	m_Leftnum	  = 0;
	m_Rightnum	  = 0;
	m_Topnum	  = 0;

	// 各ステージの音の生成
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);
	sm.PlayGameSound(StageSelectScene::m_stageID + static_cast<int>(SOUND::BGM_FLOWER), true);

	// 背景
	m_pBack = Background::create();
	this->addChild(m_pBack,-1);

	// パーティクル
	m_pParticle = Particle::create();
	this->addChild(m_pParticle);

	// マップ描画
	std::stringstream sTMXFileName;
	sTMXFileName << "mapData/map_" << STAGE_NAME[StageSelectScene::m_stageID] << ".tmx";
	m_pMap = TMXTiledMap::create(sTMXFileName.str());
	m_pMap->setAnchorPoint(Vec2(0, 0));
	m_pMap->setPosition(Vec2(0, 0));
	this->addChild(m_pMap);

	// プレイヤー
	m_pPlayer = Player::create();
	if		(StageSelectScene::m_stageID == static_cast<int>(STAGE::FLOWER))	m_pPlayer->setPosition(Vec2(192.0f, 216.0f));
	else if (StageSelectScene::m_stageID == static_cast<int>(STAGE::BIRD))		m_pPlayer->setPosition(Vec2(64.0f, 440.0f));
	else if (StageSelectScene::m_stageID == static_cast<int>(STAGE::WIND))		m_pPlayer->setPosition(Vec2(64.0f, 216.0f));
	else if (StageSelectScene::m_stageID == static_cast<int>(STAGE::MOON))		m_pPlayer->setPosition(Vec2(64.0f, 504.0f));
	this->addChild(m_pPlayer, 1);

	// 季節記
	m_pSeasonBook = nullptr;

	// アイテムＵＩ設定
	m_pItemUIspr = Sprite::create("object/item_page.png");
	m_pItemUInum = Label::create("0 /25", "HGP行書体", 60);
	m_pItemUIspr->setPosition(192.0f, WINDOW_HEIGHT - 48.0f);
	m_pItemUInum->setPosition(320.0f, WINDOW_HEIGHT - 48.0f);
	m_pItemUIspr->setScale(2.0f);
	m_pItemUInum->setColor(Color3B(0, 0, 0));
	this->addChild(m_pItemUIspr, 2);
	this->addChild(m_pItemUInum, 2);
	m_pItemUIspr->runAction(RepeatForever::create(RotateBy::create(4.0f, Vec3(0.0f, 360.0f, 0.0f))));

	// レイヤー情報の初期設定
	InitLayerInfo();


	/// デバッグ用
	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(Stage::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(Stage::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	keyLeft = false;	keyRight = false;

	return true;
}

/* =====================================================================
//! 内　容		更新処理
//! 引　数		ダミー引数（float）
//! 戻り値		なし
===================================================================== */
void Stage::update(float delta)
{
	// 季節の変更
	if (m_season != m_seasonBefore)
	{
		// パーティクルの破棄
		if (m_pParticle != nullptr)
		{
			m_pParticle->removeFromParent();
			m_pParticle = nullptr;
		}

		// 季節を変える
		ChangeSeason();
	}

	// アイテムＵＩラベルの変更
	GameManager& gm = GameManager::GetInstance();
	std::stringstream strNum;
	strNum << gm.GetPageStageNum(StageSelectScene::m_stageID) << " /25";
	m_pItemUInum->setString(strNum.str());

	/// デバッグ用
	if (!m_isPause)
	{
		// ボタンが押されていたらプレイヤーを移動させる
		if (!m_isShowObject)
		{
			if (keyLeft)
			{
				// プレイヤーの向きを設定
				m_pPlayer->setFlippedX(true);

				// プレイヤーの移動
				if (m_pPlayer->getPositionX() > SIZE_PLAYER_HERF && !m_isLeftCollision)
				{
					m_pPlayer->Move(-SPEED_MOVE_PLAYER);
				}
			}
			if (keyRight)
			{
				// プレイヤーの向きを設定
				m_pPlayer->setFlippedX(false);

				// プレイヤーの移動
				if (m_pPlayer->getPositionX() < STAGE_WIDTH - SIZE_PLAYER_HERF && !m_isRightCollision)
				{
					m_pPlayer->Move(SPEED_MOVE_PLAYER);
				}
			}
		}
	}
}

/* =====================================================================
//! 内　容		レイヤー情報の初期設定
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Stage::InitLayerInfo()
{
	// レイヤー設定
	for (int i = 0; i < NUM_SEASON; i++)
	{
		std::stringstream sFileName;
		sFileName << "tileLayer_" << SEASON_NAME[i];

		// タイルレイヤー
		m_pMapTileLayer[i] = m_pMap->getLayer(sFileName.str());
		m_pMapTileLayer[i]->setVisible(false);

		sFileName.str("");
		sFileName.clear();

		sFileName << "itemLayer_" << SEASON_NAME[i];

		// アイテムレイヤー
		m_pMapItemLayer[i] = m_pMap->getLayer(sFileName.str());
		m_pMapItemLayer[i]->setVisible(false);

		sFileName.str("");
		sFileName.clear();

		sFileName << "gimmickLayer_" << SEASON_NAME[i];		

		// ギミックレイヤー
		m_pMapGimmickLayer[i] = m_pMap->getLayer(sFileName.str());
		m_pMapGimmickLayer[i]->setVisible(false);
	}

	// 初期レイヤーを表示
	m_pMapTileLayer[m_season]->setVisible(true);
	m_pMapGimmickLayer[m_season]->setVisible(true);

	// レイヤー情報の設定
	ReSetLayerInfo();
}

/* =====================================================================
//! 内　容		タイル情報の再設定
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Stage::ReSetLayerInfo()
{
	// タイル情報の初期化
	while (!m_tileInfo.empty())
	{
		m_tileInfo.pop_back();
	}

	// アイテム情報の初期化
	while (!m_itemInfo.empty())
	{
		m_itemInfo.pop_back();
	}
	while (!m_item.empty())
	{
		if (m_item[m_item.size() - 1] != nullptr)
		{
			m_item[m_item.size() - 1]->removeFromParent();
			m_item[m_item.size() - 1] = nullptr;
		}
		m_item.pop_back();
	}

	// ギミック情報の初期化
	while (!m_gimmickInfo.empty())
	{
		m_gimmickInfo.pop_back();
	}

	// タイル数の初期化
	m_numTiles = 0;
	m_numItems = 0;
	m_numGimmicks = 0;

	// タイル情報の設定
	SetLayerInfo();

	// アイテム設定
	SetItem();
}

/* =====================================================================
//! 内　容		レイヤー情報の設定
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Stage::SetLayerInfo()
{
	// タイル情報の設定
	SetTileInfoWithLayer(m_pMapTileLayer[m_season], KIND_TILE::TILE);

	// アイテム情報の設定
	SetTileInfoWithLayer(m_pMapItemLayer[m_season], KIND_TILE::ITEM);

	// ギミック情報の設定
	SetTileInfoWithLayer(m_pMapGimmickLayer[m_season], KIND_TILE::GIMMICK);
}

/* =====================================================================
//! 内　容		レイヤーからタイル情報を設定
//! 引　数		レイヤー（TMXLayer）、タイルの種類（KIND_TILE）
//! 戻り値		なし
===================================================================== */
void Stage::SetTileInfoWithLayer(TMXLayer* layer, KIND_TILE tile)
{
	for (int i = 0; i < NUM_ROW; i++)
	{
		for (int j = 0; j < NUM_COLUMN; j++)
		{
			auto gid = layer->getTileGIDAt(Vec2(j, i));

			// プロパティ情報を取得
			Value propertyValue = m_pMap->getPropertiesForGID(gid);

			if (!propertyValue.isNull())
			{
				// プロパティをマップ配列として保持
				ValueMap propertyMap = propertyValue.asValueMap();

				if (!propertyMap.empty())
				{
					// プロパティからタイル情報を設定
					SetTileInfoWithProperty(propertyMap, i, j, tile);
				}
			}
		}
	}
}

/* =====================================================================
//! 内　容		プロパティからタイル情報を設定
//! 引　数		GID（uint32_t）、行（int）、列（int）、タイルの種類（KIND_TILE）
//! 戻り値		なし
===================================================================== */
void Stage::SetTileInfoWithProperty(ValueMap map, int row, int col, KIND_TILE tile)
{		
	// 座標設定
	Vec2 pos = Vec2(col * SIZE_TILE, (NUM_ROW - row) * SIZE_TILE - SIZE_TILE);

	int id;

	// タイル情報の登録
	switch (tile)
	{
	case KIND_TILE::TILE:		// タイル

		// 各タイル設定
		if		(map["collision"].asString() == "block")	id = static_cast<int>(TILE::BLOCK);
		else if (map["collision"].asString() == "water")	id = static_cast<int>(TILE::WATER);
		else												id = static_cast<int>(TILE::NONE);

		// タイル数加算
		m_numTiles++;

		// タイルIDの設定
		m_tileInfo.push_back(StageInfo{ id, pos });

		break;

	case KIND_TILE::ITEM:		// アイテム

		// アイテム設定
		if		(map["item"].asString() == "page")			id = static_cast<int>(TILE::ITEM);
		else												id = static_cast<int>(TILE::NONE);

		// アイテムIDの設定
		m_itemInfo.push_back(StageInfo{ id, pos });

	case KIND_TILE::GIMMICK:	// ギミック

		// 各ギミック設定
		if		(map["tree"].asString() == "block")			id = static_cast<int>(TILE::BLOCK);
		else if (map["tree"].asString() == "pollen")		id = static_cast<int>(TILE::POLLEN);
		else if (map["bug"].asString() == "block")			id = static_cast<int>(TILE::BLOCK);
		else												id = static_cast<int>(TILE::NONE);

		// ギミック数加算
		m_numGimmicks++;

		// ギミックIDの設定
		m_gimmickInfo.push_back(StageInfo{ id, pos });

		break;
	}
}

/* =====================================================================
//! 内　容		アイテム情報を設定
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Stage::SetItem()
{
	GameManager& gm = GameManager::GetInstance();

	// アイテムのＩＤがどの要素番号から始まるかを調べる
	int idStart = 0;
	for (int i = 0; i < StageSelectScene::m_stageID * NUM_STAGE + m_season; i++)
	{
		idStart += NUM_ITEM_PLACE[i];
	}

	for (int i = 0; i < NUM_ITEM_PLACE[StageSelectScene::m_stageID * NUM_STAGE + m_season]; i++)
	{
		m_item.push_back(Item::create());
		m_item[m_item.size() - 1]->setPosition(Vec2(m_itemInfo[i].pos.x + SIZE_TILE / 2, m_itemInfo[i].pos.y));
		this->addChild(m_item[m_item.size() - 1], -1);

		if (gm.GetPage()[idStart + i])
		{
			m_item[m_item.size() - 1]->removeFromParent();
			m_item[m_item.size() - 1] = nullptr;
		}

		// アイテム数加算
		m_numItems++;
	}
}

/* =====================================================================
//! 内　容		季節の変更
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Stage::ChangeSeason()
{
	// 現在の季節のレイヤーを非表示にする
	m_pMapTileLayer[m_seasonBefore]->setVisible(false);
	m_pMapGimmickLayer[m_seasonBefore]->setVisible(false);

	// 背景を変える
	m_pBack->Change(m_season);
	if (m_season != static_cast<int>(SEASON::SUMMER))
	{
		m_pParticle = Particle::create();
		this->addChild(m_pParticle, -1);
	}

	// レイヤー情報の再設定
	ReSetLayerInfo();

	// レイヤーを表示する
	m_pMapTileLayer[m_season]->setVisible(true);
	m_pMapGimmickLayer[m_season]->setVisible(true);

	// 季節の変更を確定させる
	m_seasonBefore = m_season;
}

/* =====================================================================
//! 内　容		マップのスクロール
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Stage::Scroll()
{
	// カメラ設定
	m_pCamera = getScene()->getDefaultCamera();

	float cameraPos = m_pCamera->getPositionX();

	// カメラ移動の基準値を設定
	const float CAMERA_BORDER = WINDOW_WIDTH_HERF;

	// はみ出し確認
	if (m_pPlayer->getPositionX() >= CAMERA_BORDER && m_pPlayer->getPositionX() <= STAGE_WIDTH - CAMERA_BORDER)
	{
		// アイテムＵＩ移動
		m_pItemUIspr->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 192.0f);
		m_pItemUInum->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 320.0f);

		// パーティクル移動
		if (m_pParticle != nullptr) m_pParticle->ParticleScroll(GetCameraPosX());

		// 花粉移動
		if (Pollen::m_isPollenFlg)
		{
			m_pPollen->setPositionX(GetCameraPosX());
		}

		// ボタン移動
		PlayScene::m_pButton[static_cast<int>(BUTTON::LEFT)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 80.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::RIGHT)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 208.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->setPositionX(m_pPlayer->getPositionX() + WINDOW_WIDTH_HERF - 80.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::PAUSE)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 88.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::SEASON_BOOK)]->setPositionX(m_pPlayer->getPositionX() + WINDOW_WIDTH_HERF - 184.0f);

		// カメラ設定
		cameraPos = m_pPlayer->getPositionX();
	}

	// カメラ移動
	m_pCamera->setPositionX(cameraPos);
}

/* =====================================================================
//! 内　容		当たり判定チェック
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Stage::CheckCollision()
{
	// 当たり判定フラグの初期化
	Stage::m_isLeftCollision = false;
	Stage::m_isRightCollision = false;
	Stage::m_isTopCollision = false;

	GameManager& gm = GameManager::GetInstance();

	// タイルとの当たり判定
	for (int i = 0; i < m_numTiles; i++)
	{
		// 着地判定
		if (gm.CheckCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::DOWN)
		{
			// タイルに応じたプレイヤーの処理
			m_pPlayer->Action(m_tileInfo[i].ID, m_tileInfo[i].pos, m_season);
			break;
		}

		// 各当たり判定
		if (gm.CheckCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::LEFT && m_tileInfo[i].ID != static_cast<int>(TILE::WATER))
		{
			m_Leftnum = static_cast<int>(COLLISION::LEFT);
			m_isLeftCollision = true;
		}
		else if (gm.CheckCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::RIGHT && m_tileInfo[i].ID != static_cast<int>(TILE::WATER))
		{
			m_Rightnum = static_cast<int>(COLLISION::RIGHT);
			m_isRightCollision = true;
		}
		else if (gm.CheckCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::UP && m_tileInfo[i].ID != static_cast<int>(TILE::WATER))
		{
			m_Topnum = static_cast<int>(COLLISION::UP);
			m_pPlayer->SetSpdY(-1.0f);
			m_isTopCollision = true;
		}
		else
		{
			m_Leftnum = static_cast<int>(COLLISION::NONE);
			m_Rightnum = static_cast<int>(COLLISION::NONE);
			m_Topnum = static_cast<int>(COLLISION::NONE);
		}

		// めり込み判定
		if (m_tileInfo[i].ID != static_cast<int>(TILE::WATER))
		{
			if ((m_Leftnum == static_cast<int>(COLLISION::LEFT)) &&
				(m_Rightnum == static_cast<int>(COLLISION::RIGHT)) &&
				(m_Topnum == static_cast<int>(COLLISION::UP)))
			{
				if (!Player::m_isJump)
				{
					m_pPlayer->SetSpdY(0.0f);
					m_isLeftCollision = true;
					m_isRightCollision = true;
				}
			}
			else if ((m_Rightnum == static_cast<int>(COLLISION::RIGHT)) &&
					(m_Topnum == static_cast<int>(COLLISION::UP)))
			{
				if (!Player::m_isJump)
				{
					m_pPlayer->SetSpdY(0.0f);
					m_isLeftCollision = true;
					m_isRightCollision = true;
				}
			}
			else if ((m_Leftnum == static_cast<int>(COLLISION::LEFT)) &&
				(m_Topnum == static_cast<int>(COLLISION::UP)))
			{
				if (!Player::m_isJump)
				{
					m_pPlayer->SetSpdY(0.0f);
					m_isLeftCollision = true;
					m_isRightCollision = true;
				}
			}
		}

	}

	if (m_season == m_seasonBefore)
	{
		// アイテムのＩＤがどの要素番号から始まるかを調べる
		int idStart = 0;
		for (int i = 0; i < StageSelectScene::m_stageID * NUM_STAGE + m_season; i++)
		{
			idStart += NUM_ITEM_PLACE[i];
		}

		// アイテムとの当たり判定
		for (int i = 0; i < m_numItems; i++)
		{
			if (!gm.GetPage()[idStart + i])
			{
				if (gm.isCollision(m_itemInfo[i].pos, m_pPlayer->getPosition()))
				{
					// ページ取得
					gm.SetPage(idStart + i);

					// アイテムを取得した時の音の生成
					SoundManager& sm = SoundManager::getInstance();
					sm.PlayGameSound(static_cast<int>(SOUND::SE_GET), false);

					// ページを消す
					m_item[i]->removeFromParent();
					m_item[i] = nullptr;
				}
			}
		}
	}

	// ギミックとの当たり判定
	for (int i = 0; i < m_numGimmicks; i++)
	{
		// 杉の場合花粉を出す
		if (m_gimmickInfo[i].ID == static_cast<int>(TILE::POLLEN) && !Pollen::m_isPollenFlg)
		{
			if (gm.isCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()))
			{
				m_pPollen = Pollen::create();
				m_pPollen->setPosition(Vec2(GetCameraPosX(), WINDOW_HEIGHT_HERF));
				this->addChild(m_pPollen, 5);
			}
		}
		else
		{
			// 着地判定
			if (m_gimmickInfo[i].ID == static_cast<int>(TILE::BLOCK) && gm.CheckCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::DOWN)
			{
				// タイルに応じたプレイヤーの処理
				m_pPlayer->Action(m_gimmickInfo[i].ID, m_gimmickInfo[i].pos, m_season);
				break;
			}

			// 各当たり判定
			if		(m_gimmickInfo[i].ID == static_cast<int>(TILE::BLOCK) && gm.CheckCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::LEFT)		m_isLeftCollision = true;
			else if (m_gimmickInfo[i].ID == static_cast<int>(TILE::BLOCK) && gm.CheckCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::RIGHT)		m_isRightCollision = true;
			else if (m_gimmickInfo[i].ID == static_cast<int>(TILE::BLOCK) && gm.CheckCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::UP)
			{
				m_pPlayer->SetSpdY(-1.0f);
				m_isTopCollision = true;
			}
		}
	}
}

/* =====================================================================
//! 内　容		ボタンが押された時の処理
//! 引　数		ボタン（BUTTON）
//! 戻り値		なし
===================================================================== */
void Stage::CheckButtonHighlighted(BUTTON button)
{
	// ボタンが押されてるかどうか
	if (PlayScene::m_pButton[static_cast<int>(button)]->isHighlighted())
	{
		// 左ボタン
		if (button == BUTTON::LEFT)
		{
			// プレイヤーの向きを設定
			m_pPlayer->setFlippedX(true);

			// プレイヤーの移動
			if (m_pPlayer->getPositionX() > SIZE_PLAYER_HERF && !m_isLeftCollision)
			{
				m_pPlayer->Move(-SPEED_MOVE_PLAYER);
			}
		}
		// 右ボタン
		else if (button == BUTTON::RIGHT)
		{
			// プレイヤーの向きを設定
			m_pPlayer->setFlippedX(false);

			// プレイヤーの移動
			if (m_pPlayer->getPositionX() < STAGE_WIDTH - SIZE_PLAYER_HERF && !m_isRightCollision)
			{
				m_pPlayer->Move(SPEED_MOVE_PLAYER);
			}
		}
		// アクションボタン
		else if (button == BUTTON::ACTION)
		{
			// ジャンプしてないときに処理
			if (!Player::m_isJump && !m_isTopCollision)
			{
				m_pPlayer->Jump();
				PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright(false);
			}
		}
		// 季節記ボタン
		else if (button == BUTTON::SEASON_BOOK)
		{
			if (!m_isShowObject)
			{
				// 季節記の生成
				m_pSeasonBook = SeasonBook::create();
				m_pSeasonBook->setPosition(Vec2(GetCameraPosX(), WINDOW_HEIGHT_HERF));
				this->addChild(m_pSeasonBook, 4);

				// 明度を暗くする
				PlayScene::m_pButton[static_cast<int>(BUTTON::SEASON_BOOK)]->SetFullBright(false);

				// 季節記を見ている状態にする
				m_isShowObject = true;
			}
		}
	}
}

/* =====================================================================
//! 内　容		キーデバッグ
//! 引　数		いろいろ
//! 戻り値		なし
===================================================================== */
void Stage::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		keyLeft = true;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		keyRight = true;
	}
}

/* =====================================================================
//! 内　容		キーデバッグ
//! 引　数		いろいろ
//! 戻り値		なし
===================================================================== */
void Stage::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		keyLeft = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		keyRight = false;
	}
}