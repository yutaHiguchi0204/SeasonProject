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
#include "OperationButton.h"
#include "Pause.h"
#include "Player.h"
#include "Pollen.h"
#include "SeasonBook.h"
#include "SignBoard.h"

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
	int m_seasonBefore;									// 変更前の季節
	int m_numTiles;										// 総タイル数
	int m_numObjects;									// 総オブジェクト数
	int m_numSignBoards;								// 総看板数
	int m_numGimmicks;									// 総ギミック数

	Background* m_pBack;								// 背景
	Particle* m_pParticle;								//パーティクル
	Player* m_pPlayer;									// プレイヤー
	SeasonBook* m_pSeasonBook;							// 季節記
	Pollen* m_pPollen;									// 花粉

	cocos2d::TMXTiledMap* m_pMap;						// マップ
	cocos2d::TMXLayer* m_pMapTileLayer[NUM_SEASON];		// マップレイヤー（タイル）
	cocos2d::TMXLayer* m_pMapGimmickLayer[NUM_SEASON];	// マップレイヤー（ギミック）
	cocos2d::TMXLayer* m_pMapObjectLayer;				// マップレイヤー（オブジェクト）

	std::vector<StageInfo> m_tileInfo;					// タイル情報
	std::vector<StageInfo> m_objectInfo;				// オブジェクト情報
	std::vector<StageInfo> m_gimmickInfo;				// ギミック情報
	std::vector<SignBoard*> m_pSignBoard;				// 看板

	cocos2d::Sprite* m_pNewBookmark;					// 新しい季節のしおり

	Pause* m_pPause;									// ポーズ
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
	void SetSignBoardID();																		// 説明盤のＩＤを登録
	void SetNewBookmark();																		// 新しい季節のしおりを配置

	void ChangeSeason();																		// 季節の変更

	void Scroll();																				// マップのスクロール
	inline const float GetCameraPosX() { return m_pCamera->getPositionX(); };					// カメラ座標xの取得

	void CheckCollision();																		// 当たり判定チェック

	void CheckButtonHighlighted(BUTTON button);													// ボタンが押された時の処理
	void ActionButtonHighlighted(ACTION action);												// アクションボタンが押された時の処理

	void ActionObject(int objID);																// オブジェクトアクション

	// 静的メンバ
	static int m_season;																		// 季節
	static bool m_isShowObject;																	// 看板や季節記などオブジェクトを参照している状態かどうか
	static bool m_leftFlag;																		// 衝突判定用フラグ（左）
	static bool m_rightFlag;																	// 衝突判定用フラグ（右）
	static bool m_isPause;																		// ポーズ中かどうか


	/// デバッグ用
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	cocos2d::EventListenerKeyboard* keyListener;
	bool keyLeft, keyRight;
};