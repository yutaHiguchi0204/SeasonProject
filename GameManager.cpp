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