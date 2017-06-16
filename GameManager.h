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
		if ((playerVec.x - SIZE_PLAYER_COLLISION_HERF <= tileVec.x + SIZE_TILE / 2) &&
			(playerVec.x + SIZE_PLAYER_COLLISION_HERF >= tileVec.x))
		{
			// ���̓����蔻��
			if ((playerVec.y - SIZE_PLAYER_HERF >= tileVec.y + SIZE_TILE / 2) &&
				(playerVec.y - SIZE_PLAYER_HERF - SIZE_COLLIDER <= tileVec.y + SIZE_TILE))
			{
				return COLLISION::DOWN;
			}

			// ��̓����蔻��
			if ((playerVec.y + SIZE_PLAYER_HERF <= tileVec.y + SIZE_TILE / 2) &&
				(playerVec.y + SIZE_PLAYER_HERF >= tileVec.y))
			{
				return COLLISION::UP;
			}
		}

		// ���E�̓����蔻��
		if ((playerVec.y - SIZE_PLAYER_HERF <= tileVec.y + SIZE_TILE / 2 + SIZE_COLLIDER + SIZE_COLLIDER / 2) &&
			(playerVec.y + SIZE_PLAYER_HERF >= tileVec.y + SIZE_COLLIDER / 2))
		{
			// �E�̓����蔻��
			if ((playerVec.x + SIZE_PLAYER_COLLISION_HERF + SPEED_MOVE_PLAYER >= tileVec.x) &&
				(playerVec.x - SIZE_PLAYER_COLLISION_HERF <= tileVec.x + SIZE_TILE / 2/* + SIZE_COLLIDER*/))
			{
				return COLLISION::RIGHT;
			}

			// ���̓����蔻��
			if ((playerVec.x - SIZE_PLAYER_COLLISION_HERF - SPEED_MOVE_PLAYER <= tileVec.x + SIZE_TILE /*/ 2 + SIZE_COLLIDER*/) &&
				(playerVec.x + SIZE_PLAYER_COLLISION_HERF >= tileVec.x))
			{
				return COLLISION::LEFT;
			}
		}

		return COLLISION::NONE;
	};

	// �A�C�e�����̃Z�b�g
	void SetPage(int pageID)
	{
		m_isGetPage[pageID] = true;
		m_numPage++;
	}

	// �A�C�e�����̎擾
	bool* GetPage()
	{
		return m_isGetPage;
	}
	
	// �擾�A�C�e�����̎擾
	int GetPageNum()
	{
		return m_numPage;
	}

	// �X�e�[�W���̎擾�A�C�e�����̎擾
	int GetPageStageNum(int stageID)
	{
		int num = 0;
		for (int i = 0; i < NUM_STAGE_ITEM; i++)
		{
			if (m_isGetPage[stageID * NUM_STAGE_ITEM + i]) num++;
		}

		return num;
	}

	// �A�C�e�����̃f�[�^���C���|�[�g
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

	// �A�C�e�����̃G�N�X�|�[�g
	void ExportPageInfo()
	{
		cocos2d::UserDefault* _userDefault = cocos2d::UserDefault::getInstance();

		std::stringstream key;

		// ���艹�̐���
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

	// �A�C�e�����̏�����
	void ResetPageInfo()
	{
		cocos2d::UserDefault* _userDefault = cocos2d::UserDefault::getInstance();

		std::stringstream key;

		// ���艹�̐���
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