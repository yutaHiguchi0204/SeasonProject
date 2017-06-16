/* =====================================================================
//! @param		ゲームマネージャ
//! @create		樋口　裕太
//! @date		17/03/04
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "Consant.h"
#include "SoundManager.h"

// 共通関数をまとめたクラス
class GameManager
{
private:
	bool m_isGetPage[NUM_ITEM];
	int m_numPage;

public:

	// ゲームマネージャの生成
	static GameManager& GetInstance()
	{
		static GameManager gm;
		return gm;
	};

	// 当たっているかどうか
	bool isCollision(cocos2d::Vec2 tileVec, cocos2d::Vec2 playerVec)
	{
		if ((playerVec.x - SIZE_PLAYER_COLLISION_HERF <= tileVec.x + SIZE_TILE) &&
			(playerVec.x + SIZE_PLAYER_COLLISION_HERF >= tileVec.x))
		{
			if ((playerVec.y - SIZE_PLAYER_HERF <= tileVec.y + SIZE_TILE) &&
				(playerVec.y + SIZE_PLAYER_HERF >= tileVec.y))
			{
				return true;
			}
		}

		return false;
	}

	// 全体の当たり判定
	COLLISION CheckCollision(cocos2d::Vec2 tileVec, cocos2d::Vec2 playerVec)
	{
		// 上下の当たり判定
		if ((playerVec.x - SIZE_PLAYER_COLLISION_HERF <= tileVec.x + SIZE_TILE / 2) &&
			(playerVec.x + SIZE_PLAYER_COLLISION_HERF >= tileVec.x))
		{
			// 下の当たり判定
			if ((playerVec.y - SIZE_PLAYER_HERF >= tileVec.y + SIZE_TILE / 2) &&
				(playerVec.y - SIZE_PLAYER_HERF - SIZE_COLLIDER <= tileVec.y + SIZE_TILE))
			{
				return COLLISION::DOWN;
			}

			// 上の当たり判定
			if ((playerVec.y + SIZE_PLAYER_HERF <= tileVec.y + SIZE_TILE / 2) &&
				(playerVec.y + SIZE_PLAYER_HERF >= tileVec.y))
			{
				return COLLISION::UP;
			}
		}

		// 左右の当たり判定
		if ((playerVec.y - SIZE_PLAYER_HERF <= tileVec.y + SIZE_TILE / 2 + SIZE_COLLIDER + SIZE_COLLIDER / 2) &&
			(playerVec.y + SIZE_PLAYER_HERF >= tileVec.y + SIZE_COLLIDER / 2))
		{
			// 右の当たり判定
			if ((playerVec.x + SIZE_PLAYER_COLLISION_HERF + SPEED_MOVE_PLAYER >= tileVec.x) &&
				(playerVec.x - SIZE_PLAYER_COLLISION_HERF <= tileVec.x + SIZE_TILE / 2/* + SIZE_COLLIDER*/))
			{
				return COLLISION::RIGHT;
			}

			// 左の当たり判定
			if ((playerVec.x - SIZE_PLAYER_COLLISION_HERF - SPEED_MOVE_PLAYER <= tileVec.x + SIZE_TILE /*/ 2 + SIZE_COLLIDER*/) &&
				(playerVec.x + SIZE_PLAYER_COLLISION_HERF >= tileVec.x))
			{
				return COLLISION::LEFT;
			}
		}

		return COLLISION::NONE;
	};

	// アイテム情報のセット
	void SetPage(int pageID)
	{
		m_isGetPage[pageID] = true;
		m_numPage++;
	}

	// アイテム情報の取得
	bool* GetPage()
	{
		return m_isGetPage;
	}
	
	// 取得アイテム数の取得
	int GetPageNum()
	{
		return m_numPage;
	}

	// ステージ内の取得アイテム数の取得
	int GetPageStageNum(int stageID)
	{
		int num = 0;
		for (int i = 0; i < NUM_STAGE_ITEM; i++)
		{
			if (m_isGetPage[stageID * NUM_STAGE_ITEM + i]) num++;
		}

		return num;
	}

	// アイテム情報のデータをインポート
	void ImportPageInfo()
	{
		cocos2d::UserDefault* _userDefault = cocos2d::UserDefault::getInstance();

		std::stringstream key;

		for (int i = 0; i < NUM_ITEM; i++)
		{
			key.str("");
			key.clear();
			key << "key_" << i;

			if (_userDefault->getBoolForKey(key.str().c_str()))
				SetPage(i);
		}
	}

	// アイテム情報のエクスポート
	void ExportPageInfo()
	{
		cocos2d::UserDefault* _userDefault = cocos2d::UserDefault::getInstance();

		std::stringstream key;

		// 決定音の生成
		SoundManager& sm = SoundManager::getInstance();
		sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);

		for (int i = 0; i < NUM_ITEM; i++)
		{
			key.str("");
			key.clear();
			key << "key_" << i;

			_userDefault->setBoolForKey(key.str().c_str(), GetPage()[i]);
		}
	}

	// アイテム情報の初期化
	void ResetPageInfo()
	{
		cocos2d::UserDefault* _userDefault = cocos2d::UserDefault::getInstance();

		std::stringstream key;

		// 決定音の生成
		SoundManager& sm = SoundManager::getInstance();
		sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);

		for (int i = 0; i < NUM_ITEM; i++)
		{
			key.str("");
			key.clear();
			key << "key_" << i;

			_userDefault->setBoolForKey(key.str().c_str(), false);
			m_isGetPage[i] = false;
		}

		m_numPage = 0;
	}

private:
	GameManager()
	{
		for (int i = 0; i < NUM_ITEM; i++) m_isGetPage[i] = false;
		m_numPage = 0;

		ImportPageInfo();
	};
};