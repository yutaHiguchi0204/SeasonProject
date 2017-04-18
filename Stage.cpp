/* =====================================================================
//! @param		「Stage」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/04/01
===================================================================== */

// ヘッダファイルのインクルード
#include "Stage.h"

// 名前空間
USING_NS_CC;

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
//! 内　容		レイヤー情報の設定
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Stage::SetLayerInfo()
{
	for (int i = 0; i < NUM_ROW; i++)
	{
		for (int j = 0; j < NUM_COLUMN; j++)
		{
			auto gid = m_pMapTileLayer[m_season]->getTileGIDAt(Vec2(j, i));

			// タイル情報の設定
			SetTileInfoWithProperty(gid, i, j);
		}
	}
}

/* =====================================================================
//! 内　容		プロパティからタイル情報を設定
//! 引　数		GID（uint32_t）、行（int）、列（int）
//! 戻り値		なし
===================================================================== */
void Stage::SetTileInfoWithProperty(uint32_t gid, int row, int col)
{
	// プロパティ情報を取得
	Value propertyValue = m_pMap->getPropertiesForGID(gid);

	if (!propertyValue.isNull())
	{
		// プロパティをマップ配列として保持
		ValueMap propertyMap = propertyValue.asValueMap();

		if (!propertyMap.empty())
		{
			// タイル情報の登録
			// asInt関数が使えれば一行で済むが、バグるため保留
			//m_tileInfo.push_back(TileInfo{ propertyValue.asInt(), Vec2(j * SIZE_TILE, (NUM_ROW - i) * SIZE_TILE - SIZE_TILE) });

			// 座標設定
			Vec2 pos = Vec2(col * SIZE_TILE, (NUM_ROW - row) * SIZE_TILE - SIZE_TILE);

			int id;

			// タイルIDの取得
			if		(propertyMap["collision"].asString() == "block")	id = static_cast<int>(TILE::BLOCK);
			else if (propertyMap["collision"].asString() == "water")	id = static_cast<int>(TILE::WATER);
			else if (propertyMap["tree"].asString() == "block")			id = static_cast<int>(TILE::BLOCK);

			// タイルIDの設定
			m_tileInfo.push_back(TileInfo{ id, pos });

			// 総タイル数加算
			m_numTiles++;
		}
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

	// レイヤーを表示する
	m_pMapTileLayer[m_season]->setVisible(true);
	m_pMapGimmickLayer[m_season]->setVisible(true);
}

/* =====================================================================
//! 内　容		マップのスクロール
//! 引　数		プレイヤーのx座標（float）
//! 戻り値		なし
===================================================================== */
void Stage::Scroll(float playerX, cocos2d::ui::Button* button[])
{
	// カメラ設定
	Camera* camera = getScene()->getDefaultCamera();

	float cameraPos = camera->getPositionX();

	// カメラ移動の基準値を設定
	const float CAMERA_BORDER = WINDOW_WIDTH / 2.0f;

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
	camera->setPositionX(cameraPos);
}

/* =====================================================================
//! 内　容		当たり判定チェック
//! 引　数		プレイヤー（Player*）
//! 戻り値		なし
===================================================================== */
void Stage::CheckCollision(Player* player)
{
	for (int i = 0; i < Stage::m_numTiles; i++)
	{
		// 当たり判定チェック
		if (GameManager::isCollision(Stage::m_tileInfo[i].pos, player->getPosition()))
		{
			switch (Stage::m_tileInfo[i].ID)
			{
			case static_cast<int>(TILE::BLOCK) :			// ブロック

				// 調整
				player->setPositionY(Stage::m_tileInfo[i].pos.y + SIZE_TILE + SIZE_PLAYER / 2);

				player->Fall(static_cast<int>(TILE::BLOCK), m_season);

				break;

			case static_cast<int>(TILE::WATER) :			// 水

				player->Fall(static_cast<int>(TILE::WATER), m_season);
				break;
			}
		}
	}
}



bool Stage::onTouchBegan(Touch* touch, Event* unused_event)
{
	ChangeSeason();

	return true;
}