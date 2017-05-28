/* =====================================================================
//! @param		�uTwoOptionWindow�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/05/28
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"
#include "ui/CocosGUI.h"

// �N���X�̒�`
class TwoOptionWindow : public cocos2d::Sprite
{
private:
	cocos2d::ui::Button* m_pButtonOK;
	cocos2d::ui::Button* m_pButtonCancel;

public:
	CREATE_FUNC(TwoOptionWindow);
	virtual bool init();

	// �ÓI�����o
	static bool m_isResetCheck;
};