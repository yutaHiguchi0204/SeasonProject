/* =====================================================================
//! @param		�uGameManager�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/04/03
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"
#include "PlayScene.h"

// ���O���
USING_NS_CC;

// �����o�֐��̒�`

/* =====================================================================
//! ���@�e		�����蔻��`�F�b�N
//! ���@��		�^�C�����W�iVec2�j�A�v���C���[���W�iVec2�j
//! �߂�l		�Ȃ�
===================================================================== */
bool GameManager::isCollision(Vec2 tileVec, Vec2 playerVec)
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
}
/* =====================================================================
//! ���@�e		�Փ˔���`�F�b�N
//! ���@��		�^�C�����W�iVec2�j�A�v���C���[���W�iVec2�j
//! �߂�l		�Ȃ�
===================================================================== */
int GameManager::decisionCollision(Vec2 tileVec, Vec2 playerVec)
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

	return static_cast<int>(COLLISION::NONE);
}
