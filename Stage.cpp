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
	m_numTiles = 0;
	m_numObjects = 0;
	m_numSignBoards = 0;
	m_numGimmicks = 0;

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

	// 説明盤のＩＤ登録
	SetSignBoardID();

	// プレイヤー
	m_pPlayer = Player::create();
	m_pPlayer->setPosition(Vec2(64.0f, 216.0f));
	this->addChild(m_pPlayer, 1);

	// 季節記
	m_pSeasonBook = nullptr;

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
		ChangeSeason();
	}
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

	// タイル数の初期化
	m_numTiles = 0;
	m_numObjects = 0;
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
		if (map["object"].asString() == "signBoard")
		{
			// 看板クラスの生成
			m_pSignBoard.push_back(SignBoard::create());
			this->addChild(m_pSignBoard[m_numSignBoards], 4);
			m_numSignBoards++;

			id = static_cast<int>(TILE::SIGN_BOARD);
		}
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
		else if (map["tree"].asString() == "pollen")		id = static_cast<int>(TILE::POLLEN);
		else												id = static_cast<int>(TILE::NONE);

		// ギミック数加算
		m_numGimmicks++;

		// ギミックIDの設定
		m_gimmickInfo.push_back(StageInfo{ id, pos });

		break;
	}
}

/* =====================================================================
//! 内　容		説明盤のＩＤを登録
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Stage::SetSignBoardID()
{
	// 看板数の初期化
	m_numSignBoards = 0;

	for (int i = 0; i < m_numObjects; i++)
	{
		if (m_objectInfo[i].ID == static_cast<int>(TILE::SIGN_BOARD))
		{
			m_numSignBoards++;

			// オブジェクト情報中の看板情報を登録
			m_pSignBoard[m_numSignBoards - 1]->SetObjectNumber(i);
			m_pSignBoard[m_numSignBoards - 1]->SetBlackBoardTexture(m_numSignBoards);
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
	m_pMapTileLayer[m_seasonBefore]->setVisible(false);
	m_pMapGimmickLayer[m_seasonBefore]->setVisible(false);

	// 背景を変える
	m_pBack->Change(m_season);

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
		// 背景移動
		m_pBack->setPositionX(GetCameraPosX());

		// 花粉移動
		if (Pollen::m_isPollenFlg)
		{
			m_pPollen->setPositionX(GetCameraPosX());
		}

		// ボタン移動
		PlayScene::m_pButton[static_cast<int>(BUTTON::LEFT)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 96.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::RIGHT)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 288.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->setPositionX(m_pPlayer->getPositionX() + WINDOW_WIDTH_HERF - 96.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::PAUSE)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 64.0f);

		// カメラ設定
		cameraPos = m_pPlayer->getPositionX();
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
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Stage::CheckCollision()
{
	m_leftFlag = false;
	m_rightFlag = false;

	// タイルとの当たり判定
	for (int i = 0; i < m_numTiles; i++)
	{
		if (GameManager::isCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()))
		{
			// タイルに応じたプレイヤーの処理
			m_pPlayer->Action(m_tileInfo[i].ID, m_tileInfo[i].pos, m_season);
		}

		// 左右の衝突判定
		if (GameManager::decisionCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == static_cast<int>(COLLISION::RIGHT) && !m_tileInfo[i].ID == static_cast<int>(TILE::WATER))
		{
			m_rightFlag = true;
		}
		else if (GameManager::decisionCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == static_cast<int>(COLLISION::LEFT) && !m_tileInfo[i].ID == static_cast<int>(TILE::WATER))
		{
			m_leftFlag = true;
		}
	}

	// オブジェクトとの当たり判定
	for (int i = 0; i < m_numObjects; i++)
	{
		if (GameManager::isCollision(m_objectInfo[i].pos, m_pPlayer->getPosition()))
		{
			// オブジェクトの処理
			ActionObject(m_objectInfo[i].ID);
			
			// オブジェクトに応じたプレイヤーの処理
			//m_pPlayer->Action(m_objectInfo[i].ID, m_objectInfo[i].pos, m_season);
		}
	}

	// ギミックとの当たり判定
	for (int i = 0; i < m_numGimmicks; i++)
	{
		if (GameManager::isCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()))
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
			if (GameManager::decisionCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == static_cast<int>(COLLISION::RIGHT))
			{
				m_rightFlag = true;
			}
			else if (GameManager::decisionCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == static_cast<int>(COLLISION::LEFT))
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
		// ポーズボタン
		else
		{
			// ポーズ画面の生成
			m_pPause = Pause::create();
			m_pPause->setPosition(Vec2(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF));
			this->addChild(m_pPause);
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
	switch (action)
	{
	case ACTION::JUMP:				// ジャンプボタン

		m_pPlayer->Jump();
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright(false);
		break;

	case ACTION::SEASON_BOOK:		// 季節記ボタン

		// 季節記の生成
		m_pSeasonBook = SeasonBook::create();
		m_pSeasonBook->setPosition(Vec2(GetCameraPosX(), WINDOW_HEIGHT_HERF));
		this->addChild(m_pSeasonBook, 4);

		// 明度を暗くする
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright(false);

		// 季節記を見ている状態にする
		m_isShowObject = true;

		break;

	case ACTION::SIGN_BOARD:		// 看板ボタン

		// 明度を暗くする
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright(false);

		// 説明盤の生成（プレイヤーと当たっているものだけ）
		for (int i = 0; i < m_numObjects; i++)
		{
			if (GameManager::isCollision(m_objectInfo[i].pos, m_pPlayer->getPosition()))
			{
				for (int j = 0; j < m_numSignBoards; j++)
				{
					m_pSignBoard[j]->setPosition(Vec2(GetCameraPosX(), WINDOW_HEIGHT_HERF));
					m_pSignBoard[j]->DrawBlackBoard(i);
				}
			}
		}

		// 看板を見ている状態にする
		m_isShowObject = true;

		break;
	}
}

/* =====================================================================
//! 内　容		オブジェクトアクション
//! 引　数		オブジェクトＩＤ（int）
//! 戻り値		なし
===================================================================== */
void Stage::ActionObject(int objID)
{
	switch (objID)
	{
	case static_cast<int>(TILE::SEASON_BOOK):		// 季節記と当たった場合

		// ボタンの画像を変える
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::SEASON_BOOK);

		break;

	case static_cast<int>(TILE::SIGN_BOARD) :		// 看板と当たった場合

		// ボタンの画像を変える
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::SIGN_BOARD);

		break;
	}
}