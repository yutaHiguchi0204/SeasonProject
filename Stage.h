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
#include "Player.h"
#include "ui/CocosGUI.h"

// 構造体
struct TileInfo
{
	int ID;					// タイルID
	cocos2d::Vec2 pos;		// 矩形座標
};

// クラスの定義
class Stage : public cocos2d::Node
{
private:
	int m_season;										// 季節

	Background* m_pBack;								// 背景

	cocos2d::TMXTiledMap* m_pMap;						// マップ
	cocos2d::TMXLayer* m_pMapTileLayer[NUM_SEASON];		// マップレイヤー（タイル）
	cocos2d::TMXLayer* m_pMapGimmickLayer[NUM_SEASON];	// マップレイヤー（ギミック）
	cocos2d::TMXLayer* m_pMapObjectLayer;				// マップレイヤー（オブジェクト）

public:

	CREATE_FUNC(Stage);
	virtual bool init();

	void ReSetLayerInfo();											// タイル情報の初期化
	void SetLayerInfo();											// レイヤー情報の設定
	void SetTileInfoWithProperty(uint32_t gid, int row, int col);	// プロパティからタイル情報を設定

	void ChangeSeason();											// 季節の変更

	void Scroll(float playerX, cocos2d::ui::Button* button[]);		// マップのスクロール

	void CheckCollision(Player* player);							// 当たり判定チェック

	// タッチ判定
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	// 静的メンバ
	static std::vector<TileInfo> m_tileInfo;						// タイル情報
	static int m_numTiles;											// 総タイル数
};