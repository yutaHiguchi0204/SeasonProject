/* =====================================================================
//! @param		�uBackground�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/04/01
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Background.h"

// ���O���
USING_NS_CC;

// �����o�֐��̒�`

bool Background::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �摜�̏����ݒ�
	setTexture("background/back_spring.png");

	// �ʒu�̏����ݒ�
	setPosition(STAGE_MIDDLE);

	return true;
}

/* =====================================================================
//! ���@�e		�w�i�̕ύX
//! ���@��		�G�߁iint�j
//! �߂�l		�Ȃ�
===================================================================== */
void Background::Change(int season)
{
	std::stringstream sFileName;
	sFileName << "background/back_" << SEASON_NAME[season] << ".png";

	// �w�i�̕ύX
	setTexture(sFileName.str());
}