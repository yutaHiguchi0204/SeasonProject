/* =====================================================================
//! @param		�uPollen�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/05/02
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"

// �萔
const int TIME_POLLEN = 20;			// �ԕ��ɐN����Ă��鎞��

// �N���X�̒�`
class Pollen : public cocos2d::Sprite
{
private:
	int m_time;

public:
	CREATE_FUNC(Pollen);
	virtual bool init();

	void update(float delta);

	// �ÓI�����o�ϐ�
	static bool m_isPollenFlg;
};