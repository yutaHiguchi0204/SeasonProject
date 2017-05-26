/* =====================================================================
//! @param		�uItem�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/05/26
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Item.h"

// ���O���
USING_NS_CC;

// �����o�֐��̒�`

// ������
bool Item::init()
{
	// ���N���X�̏�����
	if (!Sprite::init())
	{
		// ���N���X�̏����������s�Ȃ�A�ُ�I��
		return false;
	}

	// �摜�ݒ�
	setTexture("object/item_page.png");
	setAnchorPoint(Vec2(0.5f, 0.0f));

	// �x���ŉ�]����A�N�V������ݒ�
	runAction(RepeatForever::create(RotateBy::create(4.0f, Vec3(0.0f, 360.0f, 0.0f))));

	return true;
}