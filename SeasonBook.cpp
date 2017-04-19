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

	setTexture("object/seasonBook.png");

	return true;
}

//�t���O�Ǘ�
void SeasonBook::Setbookflag()
{
	bool setflag;

	if (setflag != 0)
	{
		setTexture("object/button_book.png");
	}
	else if (setflag == 0)
	{
		setTexture("object/button_action.png");
	}
}