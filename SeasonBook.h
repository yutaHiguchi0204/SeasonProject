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

public:
	CREATE_FUNC(SeasonBook);
	virtual bool init();

	void Change();						// �G�ߓ���ւ���ʂ�\��

	// �ÓI�����o
	static bool m_isChangeSeason;		// �G�ߋL���J���ċG�߂�ς��Ă�r�����ǂ���
};