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
OperationButton* PlayScene::m_pButton[NUM_BUTTON];
int StageSelectScene::m_stageID;
bool Pollen::m_isPollenFlg;

// メンバ関数の定義

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
	m_isShowObject = false;								// オブジェクトを参照しているかどうか
	m_isPause = false;									// ポーズ中かどうか
	Pollen::m_isPollenFlg = false;						// 花粉フラグをおろしておく
	m_numTiles = 0;										// タイル数
	m_numSignBoards = 0;								// 看板数
	m_numGimmicks = 0;									// ギミック数

	//各ステージの音の生成
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(StageSelectScene::m_stageID + static_cast<int>(SOUND::BGM_FLOWER), false);

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
	m_pPlayer->setPosition(Vec2(192.0f, 216.0f));
	this->addChild(m_pPlayer, 1);

	// 季節記
	m_pSeasonBook = nullptr;

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


	/// デバッグ用
	if (!m_isPause)
	{
		// ボタンが押されていたらプレイヤーを移動させる
		if (!m_isShowObject)
		{
			if (keyLeft && !m_leftFlag)
			{
				// プレイヤーの向きを設定
				m_pPlayer->setFlippedX(true);

				// プレイヤーの移動
				if (m_pPlayer->getPositionX() > SIZE_PLAYER_HERF)
				{
					m_pPlayer->Move(-SPEED_MOVE_PLAYER);
				}
			}
			if (keyRight && !m_rightFlag)
			{
				// プレイヤーの向きを設定
				m_pPlayer->setFlippedX(false);

				// プレイヤーの移動
				if (m_pPlayer->getPositionX() < STAGE_WIDTH - SIZE_PLAYER_HERF)
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

	// ギミック情報の初期化
	while (!m_gimmickInfo.empty())
	{
		m_gimmickInfo.pop_back();
	}

	// タイル数の初期化
	m_numTiles = 0;
	m_numGimmicks = 0;

	// タイル情報の設定
	SetLayerInfo();
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
		// パーティクル移動
		if (m_pParticle != nullptr) m_pParticle->ParticleScroll(GetCameraPosX());

		// 花粉移動
		if (Pollen::m_isPollenFlg)
		{
			m_pPollen->setPositionX(GetCameraPosX());
		}

		// ボタン移動
		PlayScene::m_pButton[static_cast<int>(BUTTON::LEFT)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 96.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::RIGHT)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 288.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->setPositionX(m_pPlayer->getPositionX() + WINDOW_WIDTH_HERF - 96.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::PAUSE)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 88.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::SEASON_BOOK)]->setPositionX(m_pPlayer->getPositionX() + WINDOW_WIDTH_HERF - 208.0f);

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
	m_leftFlag = false;
	m_rightFlag = false;

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

		// 左右の衝突判定
		if (gm.CheckCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::RIGHT && !m_tileInfo[i].ID == static_cast<int>(TILE::WATER))
		{
			m_rightFlag = true;
		}
		if (gm.CheckCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::LEFT && !m_tileInfo[i].ID == static_cast<int>(TILE::WATER))
		{
			m_leftFlag = true;
		}
	}

	// ギミックとの当たり判定
	for (int i = 0; i < m_numGimmicks; i++)
	{
		if (gm.isCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()))
		{
			// 杉の場合花粉を出す
			if (m_gimmickInfo[i].ID == static_cast<int>(TILE::POLLEN) && !Pollen::m_isPollenFlg)
			{
				m_pPollen = Pollen::create();
				m_pPollen->setPosition(Vec2(GetCameraPosX(), WINDOW_HEIGHT_HERF));
				this->addChild(m_pPollen, 5);
			}

			// ギミックに応じたプレイヤーの処理
			m_pPlayer->Action(m_gimmickInfo[i].ID, m_gimmickInfo[i].pos, m_season);
		}

		// 左右の衝突判定
		if (m_gimmickInfo[i].ID == static_cast<int>(TILE::BLOCK))
		{
			if (gm.CheckCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::RIGHT)
			{
				m_rightFlag = true;
			}
			if (gm.CheckCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::LEFT)
			{
				m_leftFlag = true;
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
			if (m_pPlayer->getPositionX() > SIZE_PLAYER_HERF)
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
			if (m_pPlayer->getPositionX() < STAGE_WIDTH - SIZE_PLAYER_HERF)
			{
				m_pPlayer->Move(SPEED_MOVE_PLAYER);
			}
		}
		// アクションボタン
		else if (button == BUTTON::ACTION)
		{
			// ジャンプしてないときに処理
			if (!Player::m_isJump)
			{
				ActionButtonHighlighted(PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg());
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
//! 内　容		アクションボタンが押された時の処理
//! 引　数		アクション（ACTION）
//! 戻り値		なし
===================================================================== */
void Stage::ActionButtonHighlighted(ACTION action)
{
	GameManager& gm = GameManager::GetInstance();

	switch (action)
	{
	case ACTION::JUMP:				// ジャンプボタン
	case ACTION::SWIM:				// 泳ぐボタン

		m_pPlayer->Jump();
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright(false);
		break;
	}
}

/* =====================================================================
//! 内　容		キーデバッグ
//! 引　数		いろいろ
//! 戻り値		なし
===================================================================== */
void Stage::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!Stage::m_isPause)
	{
		// ボタンが押されていたらプレイヤーを移動させる
		if (!Stage::m_isShowObject)
		{
			if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && !m_leftFlag)
			{
				keyLeft = true;
			}
			if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && !m_rightFlag)
			{
				keyRight = true;
			}
		}
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