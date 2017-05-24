/* =====================================================================
//! @param		�Q�[���}�l�[�W��
//! @create		����@�T��
//! @date		17/03/04
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "Consant.h"

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

	// ���n����i�S�̂̓����蔻��j
	static bool isCollision(cocos2d::Vec2 tileVec, cocos2d::Vec2 playerVec)
	{
		if ((tileVec.x <= playerVec.x + SIZE_PLAYER_HERF) &&
			(tileVec.x + SIZE_TILE >= playerVec.x - SIZE_PLAYER_HERF))
		{
			if ((tileVec.y <= playerVec.y + SIZE_PLAYER_HERF) &&
				(tileVec.y + SIZE_TILE >= playerVec.y - SIZE_PLAYER_HERF))
			{
				return true;
			}
		}

		return false;
	};

	// ���E�̓����蔻��
	static int decisionCollision(cocos2d::Vec2 tileVec, cocos2d::Vec2 playerVec)
	{
		if (playerVec.y - tileVec.y <= SIZE_TILE)
		{
			// �E�̂����蔻��
			if (playerVec.x + SIZE_PLAYER_HERF + SPEED_MOVE_PLAYER >= tileVec.x &&
				playerVec.x - SIZE_PLAYER_HERF <= tileVec.x + SIZE_TILE)
			{
				return static_cast<int>(COLLISION::RIGHT);
			}
			// ���̂����蔻��
			else if (playerVec.x - SIZE_PLAYER_HERF - SPEED_MOVE_PLAYER <= tileVec.x + SIZE_TILE &&
				playerVec.x + SIZE_PLAYER_HERF >= tileVec.x)
			{
				return static_cast<int>(COLLISION::LEFT);
			}
		}
	};

private:
	GameManager() {};
};