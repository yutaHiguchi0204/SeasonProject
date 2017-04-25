/* =====================================================================
//! @param		「Stage」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/04/01
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <vector>
#include "Background.h"
#include "GameManager.h"
#include "OperationButton.h"
#include "Player.h"

// 列挙型
enum class KIND_TILE
{
	TILE,
	OBJECT,
	GIMMICK
};

// 構造体
struct StageInfo
{
	int ID;					// タイルID
	cocos2d::Vec2 pos;		// 矩形座標
};

// クラスの定義
class Stage : public cocos2d::Node
{
private:
	int m_season;										// 季節
	int m_numTiles;										// 総タイル数
	int m_numObjects;									// 総オブジェクト数
	int m_numGimmicks;									// 総ギミック数

	Background* m_pBack;								// 背景

	cocos2d::TMXTiledMap* m_pMap;						// マップ
	cocos2d::TMXLayer* m_pMapTileLayer[NUM_SEASON];		// マップレイヤー（タイル）
	cocos2d::TMXLayer* m_pMapGimmickLayer[NUM_SEASON];	// マップレイヤー（ギミック）
	cocos2d::TMXLayer* m_pMapObjectLayer;				// マップレイヤー（オブジェクト）

	std::vector<StageInfo> m_tileInfo;					// タイル情報
	std::vector<StageInfo> m_objectInfo;				// タイル情報
	std::vector<StageInfo> m_gimmickInfo;				// タイル情報

	cocos2d::Camera* m_pCamera;							// カメラ

public:

	CREATE_FUNC(Stage);
	virtual bool init();

	void ReSetLayerInfo();																		// タイル情報の初期化
	void SetLayerInfo();																		// レイヤー情報の設定
	void SetTileInfoWithLayer(cocos2d::TMXLayer* layer, KIND_TILE tile);						// レイヤーからタイル情報を設定
	void SetTileInfoWithProperty(cocos2d::ValueMap map, int row, int col, KIND_TILE tile);		// プロパティからタイル情報を設定

	void ChangeSeason();																		// 季節の変更

	void Scroll(float playerX, OperationButton* button[]);										// マップのスクロール
	float GetCameraPosX();																		// カメラ座標xの取得

	void CheckCollision(Player* player);														// 当たり判定チェック
	void MoveButtonHighlighted(BUTTON button, Player* player);									// 移動ボタンが押された時の処理

	// タッチ判定
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};