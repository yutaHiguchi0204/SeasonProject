/* =====================================================================
//! @param		�uPollen�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/05/02
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Pollen.h"

// ���O���
USING_NS_CC;

// �ÓI�����o�̒�`
bool Pollen::m_isPollenFlg;

// �����o�֐��̒�`

// �����ݒ�
bool Pollen::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �X�V��������
	scheduleUpdate();

	// �����o�̏����ݒ�
	m_isPollenFlg = true;
	m_time = 0;

	// �ԕ��摜
	setTexture("object/pollen.png");

	// �摜�̏����ݒ�
	setOpacity(0x00);
	
	//���̓ǂݍ���
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::SE_KAFUN), false);

	return true;
}

/* =====================================================================
//! ���@�e		�X�V����
//! ���@��		�_�~�[�����ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void Pollen::update(float delta)
{
	if (m_time / NUM_SECOND < TIME_POLLEN)
	{
		// �t�F�[�h�C��
		if (getOpacity() < 0xff)
		{
			setOpacity(getOpacity() + 0x01);
		}
	}
	else
	{
		// �t�F�[�h�A�E�g
		if (getOpacity() > 0x00)
		{
			setOpacity(getOpacity() - 0x01);
		}
		else
		{
			m_isPollenFlg = false;
			removeFromParent();
		}
	}
	
	// ���Ԍv��
	m_time++;
}