/* =====================================================================
//! @param		�uItem�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/05/26
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"

// �X�e�[�W�A�G�߂��Ƃ̃A�C�e����
const int NUM_PLACE = NUM_SEASON * NUM_STAGE;
const int NUM_ITEM_PLACE[NUM_PLACE] = {
	6,		// �Ԃ̏t
	6,		// �Ԃ̉�
	6,		// �Ԃ̏H
	7,		// �Ԃ̓~
	7,		// ���̏t
	6,		// ���̉�
	5,		// ���̏H
	7,		// ���̓~
	5,		// ���̏t
	6,		// ���̉�
	6,		// ���̏H
	8,		// ���̓~
	7,		// ���̏t
	7,		// ���̉�
	7,		// ���̏H
	4,		// ���̓~
};

// �N���X�̒�`
class Item : public cocos2d::Sprite
{
public:
	CREATE_FUNC(Item);
	virtual bool init();
};