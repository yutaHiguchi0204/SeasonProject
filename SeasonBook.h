/* =====================================================================
//! @param		�uSeasonBook�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/03/19
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"

// �N���X�̒�`
class SeasonBook : public cocos2d::Sprite
{
private:
	cocos2d::Sprite* m_pBook;			// �{��
	bool m_isChange;					// �G�ߋL���J���ċG�߂�ς��Ă�r�����ǂ���

public:
	CREATE_FUNC(SeasonBook);
	virtual bool init();

	void Change();						// �G�ߓ���ւ���ʂ�\��
};