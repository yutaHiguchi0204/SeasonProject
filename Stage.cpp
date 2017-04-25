/* =====================================================================
//! @param		「Stage」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/04/01
===================================================================== */

// ヘッダファイルのインクルード
#include "Stage.h"
#include "PlayScene.h"

// 名前空間
USING_NS_CC;

// 静的メンバの定義
OperationButton* PlayScene::m_pButton[NUM_BUTTON];

// メンバ関数の定義

bool Stage::init()
{
	if (!Node::init())
	{
		return false;
	}

	// メンバの初期設定
	m_season = static_cast<int>(SEASON::SPRING);		// 季節
	m_numTiles = 0;

	// 背景
	m_pBack = Background::create();
	this->addChild(m_pBack);

	// マップ描画
	m_pMap = TMXTiledMap::create("mapData/mapFlower.tmx");
	m_pMap->setAnchorPoint(Vec2(0, 0));
	m_pMap->setPosition(Vec2(0, 0));
	this->addChild(m_pMap);

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

	// オブジェクトレイヤー
	m_pMapObjectLayer = m_pMap->getLayer("objectLayer");

	// レイヤー情報の設定
	SetLayerInfo();

	// イベントリスナー作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	// イベントリスナーに各コールバック関数をセットする
	listener->onTouchBegan = CC_CALLBACK_2(Stage::onTouchBegan, this);

	// イベントリスナー登録
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
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

	// オブジェクト情報の初期化
	while (!m_objectInfo.empty())
	{
		m_objectInfo.pop_back();
	}

	// ギミック情報の初期化
	while (!m_gimmickInfo.empty())
	{
		m_gimmickInfo.pop_back();
	}

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

	// オブジェクト情報の設定
	SetTileInfoWithLayer(m_pMapObjectLayer, KIND_TILE::OBJECT);

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

	case KIND_TILE::OBJECT:		// オブジェクト

		// 各オブジェクト設定
		if		(map["object"].asString() == "signBoard")	id = static_cast<int>(TILE::SIGN_BOARD);
		else if	(map["object"].asString() == "seasonBook")	id = static_cast<int>(TILE::SEASON_BOOK);
		else												id = static_cast<int>(TILE::NONE);

		// オブジェクト数加算
		m_numObjects++;

		// オブジェクトIDの設定
		m_objectInfo.push_back(StageInfo{ id, pos });

		break;

	case KIND_TILE::GIMMICK:	// ギミック

		// 各ギミック設定
		if		(map["tree"].asString() == "block")			id = static_cast<int>(TILE::BLOCK);
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
	m_pMapTileLayer[m_season]->setVisible(false);
	m_pMapGimmickLayer[m_season]->setVisible(false);

	// 季節を変える
	m_season++;
	if (m_season >= NUM_SEASON) m_season = static_cast<int>(SEASON::SPRING);

	// 背景を変える
	m_pBack->Change(m_season);

	// レイヤー情報の再設定
	//ReSetLayerInfo();

	// レイヤーを表示する
	m_pMapTileLayer[m_season]->setVisible(true);
	m_pMapGimmickLayer[m_season]->setVisible(true);
}

/* =====================================================================
//! 内　容		マップのスクロール
//! 引　数		プレイヤーのx座標（float）
//! 戻り値		なし
===================================================================== */
void Stage::Scroll(float playerX, OperationButton* button[])
{
	// カメラ設定
	m_pCamera = getScene()->getDefaultCamera();

	float cameraPos = m_pCamera->getPositionX();

	// カメラ移動の基準値を設定
	const float CAMERA_BORDER = WINDOW_WIDTH_HERF;

	// はみ出し確認
	if (playerX >= CAMERA_BORDER && playerX <= STAGE_WIDTH - CAMERA_BORDER)
	{
		// 背景移動
		m_pBack->setPositionX(playerX);

		// ボタン移動
		button[static_cast<int>(BUTTON::LEFT)]->setPositionX(playerX - 384.0f);
		button[static_cast<int>(BUTTON::RIGHT)]->setPositionX(playerX - 192.0f);
		button[static_cast<int>(BUTTON::ACTION)]->setPositionX(playerX + 384.0f);

		// カメラ設定
		cameraPos = playerX;
	}

	// カメラ移動
	m_pCamera->setPositionX(cameraPos);
}

/* =====================================================================
//! 内　容		カメラ座標xの取得
//! 引　数		なし
//! 戻り値		カメラ座標x（float）
===================================================================== */
float Stage::GetCameraPosX()
{
	return m_pCamera->getPositionX();
}

/* =====================================================================
//! 内　容		当たり判定チェック
//! 引　数		プレイヤー（Player*）
//! 戻り値		なし
===================================================================== */
void Stage::CheckCollision(Player* player)
{
	// タイルとの当たり判定
	for (int i = 0; i < m_numTiles; i++)
	{
		if (GameManager::isCollision(m_tileInfo[i].pos, player->getPosition()))
		{
			// タイルに応じて処理
			player->Action(m_tileInfo[i].ID, m_tileInfo[i].pos, m_season);
		}
	}

	// オブジェクトとの当たり判定
	for (int i = 0; i < m_numObjects; i++)
	{
		if (GameManager::isCollision(m_objectInfo[i].pos, player->getPosition()))
		{
			// 季節記と当たった場合
			if (m_objectInfo[i].ID == static_cast<int>(TILE::SEASON_BOOK))
			{
				PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::SEASON_BOOK);
			}

			// オブジェクトに応じて処理
			player->Action(m_objectInfo[i].ID, m_objectInfo[i].pos, m_season);
		}
	}

	// ギミックとの当たり判定
	for (int i = 0; i < m_numGimmicks; i++)
	{
		if (GameManager::isCollision(m_gimmickInfo[i].pos, player->getPosition()))
		{
			// ギミックに応じて処理
			player->Action(m_gimmickInfo[i].ID, m_gimmickInfo[i].pos, m_season);
		}
	}
}

/* =====================================================================
//! 内　容		移動ボタンが押された時の処理
//! 引　数		ボタン（BUTTON）、プレイヤー（Player*）
//! 戻り値		なし
===================================================================== */
void Stage::MoveButtonHighlighted(BUTTON button, Player* player)
{
	// ボタンが押されてるかどうか
	if (PlayScene::m_pButton[static_cast<int>(button)]->isHighlighted())
	{
		// 左ボタン
		if (button == BUTTON::LEFT)
		{
			// プレイヤーの向きを設定
			player->setFlippedX(true);

			// プレイヤーの移動
			if (player->getPositionX() > SIZE_PLAYER_HERF)
			{
				player->Move(-SPEED_MOVE_PLAYER);
			}
		}
		// 右ボタン
		else
		{
			// プレイヤーの向きを設定
			player->setFlippedX(false);

			// プレイヤーの移動
			if (player->getPositionX() < STAGE_WIDTH - SIZE_PLAYER_HERF)
			{
				player->Move(SPEED_MOVE_PLAYER);
			}
		}
	}
}

bool Stage::onTouchBegan(Touch* touch, Event* unused_event)
{
	ChangeSeason();

	return true;
}