/* =====================================================================
//! @param		�Q�[���}�l�[�W��
//! @create		����@�T��
//! @date		17/03/04
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "Consant.h"
#include "SoundManager.h"

// ���ʊ֐����܂Ƃ߂��N���X
class GameManager
{
private:
	bool m_isGetPage[NUM_ITEM];
	int m_numPage;

public:

	// �Q�[���}�l�[�W���̐���
	static GameManager& GetInstance()
	{
		static GameManager gm;
		return gm;
	};

	// �������Ă��邩�ǂ���
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

	// �S�̂̓����蔻��
	COLLISION CheckCollision(cocos2d::Vec2 tileVec, cocos2d::Vec2 playerVec)
	{
		// �㉺�̓����蔻��
		if ((playerVec.x - SIZE_PLAYER_COLLISION_HERF <= tileVec.x + SIZE_TILE) &&
			(playerVec.x + SIZE_PLAYER_COLLISION_HERF >= tileVec.x))
		{
			// ���̓����蔻��
			if ((playerVec.y - SIZE_PLAYER_HERF >= tileVec.y + SIZE_TILE) &&
				(playerVec.y - SIZE_PLAYER_HERF - SIZE_COLLIDER <= tileVec.y + SIZE_TILE))
			{
				return COLLISION::DOWN;
			}

			// ��̓����蔻��
			if ((playerVec.y + SIZE_PLAYER_HERF <= tileVec.y + SIZE_TILE) &&
				(playerVec.y + SIZE_PLAYER_HERF >= tileVec.y))
			{
				return COLLISION::UP;
			}
		}

		// ���E�̓����蔻��
		if ((playerVec.y - SIZE_PLAYER_HERF <= tileVec.y + SIZE_TILE) &&
			(playerVec.y + SIZE_PLAYER_HERF >= tileVec.y))
		{
			// �E�̓����蔻��
			if ((playerVec.x + SIZE_PLAYER_COLLISION_HERF >= tileVec.x) &&
				(playerVec.x - SIZE_PLAYER_COLLISION_HERF <= tileVec.x + SIZE_TILE))
			{
				return COLLISION::RIGHT;
			}

			// ���̓����蔻��
			if ((playerVec.x - SIZE_PLAYER_COLLISION_HERF <= tileVec.x + SIZE_TILE) &&
				(playerVec.x + SIZE_PLAYER_COLLISION_HERF >= tileVec.x))
			{
				return COLLISION::LEFT;
			}
		}

		return COLLISION::NONE;
	};

	void SetPage(int pageID)
	{
		m_isGetPage[pageID] = true;
	}

	bool* GetPage()
	{
		return m_isGetPage;
	}

	int GetPageNum()
	{
		int num = 0;
		for (int i = 0; i < NUM_ITEM; i++)
		{
			if (m_isGetPage[i]) num++;
		}

		return num;
	}

	int GetPageStageNum(int stageID)
	{
		int num = 0;
		for (int i = 0; i < NUM_STAGE_ITEM; i++)
		{
			if (m_isGetPage[stageID * NUM_STAGE_ITEM + i]) num++;
		}

		return num;
	}

private:
	GameManager()
	{
		for (int i = 0; i < NUM_ITEM; i++) m_isGetPage[i] = false;
		m_numPage = 0;
	};
};