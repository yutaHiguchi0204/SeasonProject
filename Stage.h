/* =====================================================================
//! @param		「Stage」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/04/01
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <vector>
#include "Background.h"
#include "Particle.h"
#include "GameManager.h"
#include "Item.h"
#include "OperationButton.h"
#include "Pause.h"
#include "Player.h"
#include "Pollen.h"
#include "SeasonBook.h"

// 列挙型
enum class KIND_TILE
{
	TILE,
	ITEM,
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
	int m_seasonBefore;									// 変更前の季節
	int m_numTiles;										// 総タイル数
	int m_numItems;										// 総アイテム数
	int m_numGimmicks;									// 総ギミック数
	int m_Leftnum;
	int m_Rightnum;
	int m_Topnum;
	bool m_DiveFlag;

	Background* m_pBack;								// 背景
	Particle* m_pParticle;								// パーティクル
	Player* m_pPlayer;									// プレイヤー
	SeasonBook* m_pSeasonBook;							// 季節記
	Pollen* m_pPollen;									// 花粉
	std::vector<Item*> m_item;							// アイテム

	cocos2d::TMXTiledMap* m_pMap;						// マップ
	cocos2d::TMXLayer* m_pMapTileLayer[NUM_SEASON];		// マップレイヤー（タイル）
	cocos2d::TMXLayer* m_pMapItemLayer[NUM_SEASON];		// マップレイヤー（アイテム）
	cocos2d::TMXLayer* m_pMapGimmickLayer[NUM_SEASON];	// マップレイヤー（ギミック）

	std::vector<StageInfo> m_tileInfo;					// タイル情報
	std::vector<StageInfo> m_itemInfo;					// アイテム情報
	std::vector<StageInfo> m_gimmickInfo;				// ギミック情報

	cocos2d::Sprite* m_pItemUIspr;						// アイテムＵＩの画像
	cocos2d::Label* m_pItemUInum;						// アイテムＵＩのアイテム所持数

	cocos2d::Camera* m_pCamera;							// カメラ

public:

	CREATE_FUNC(Stage);
	virtual bool init();

	void update(float delta);

	void InitLayerInfo();																		// レイヤー情報の初期設定
	void ReSetLayerInfo();																		// タイル情報の初期化
	void SetLayerInfo();																		// レイヤー情報の設定
	void SetTileInfoWithLayer(cocos2d::TMXLayer* layer, KIND_TILE tile);						// レイヤーからタイル情報を設定
	void SetTileInfoWithProperty(cocos2d::ValueMap map, int row, int col, KIND_TILE tile);		// プロパティからタイル情報を設定
	void SetItem();																				// アイテム情報を設定

	void ChangeSeason();																		// 季節の変更

	void Scroll();																				// マップのスクロール
	inline const float GetCameraPosX() { return m_pCamera->getPositionX(); };					// カメラ座標xの取得

	void CheckCollision();																		// 当たり判定チェック

	void CheckButtonHighlighted(BUTTON button);													// ボタンが押された時の処理

	// 静的メンバ
	static int m_season;																		// 季節
	static bool m_isLeftCollision;																// 左判定フラグ
	static bool m_isRightCollision;																// 右判定フラグ
	static bool m_isTopCollision;																// 上判定フラグ
	static bool m_isShowObject;																	// 看板や季節記などオブジェクトを参照している状態かどうか
	static bool m_isPause;																		// ポーズ中かどうか


	/// デバッグ用
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	cocos2d::EventListenerKeyboard* keyListener;
	bool keyLeft, keyRight;
};