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

private:
	GameManager() {};
};