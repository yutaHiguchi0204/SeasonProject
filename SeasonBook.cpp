/* =====================================================================
//! @param		�uSeasonBook�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/03/19
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "SeasonBook.h"

// ���O���
USING_NS_CC;

// �����o�֐��̒�`

bool SeasonBook::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �G�ߊ����̃y�[�W��\��
	m_pBook = Sprite::create("object/seasonChanger.png");
	this->addChild(m_pBook, 4);

	return true;
}