/* =====================================================================
//! @param		�uMessageWindow�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/05/28
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"
#include "ui/CocosGUI.h"

// �N���X�̒�`
class MessageWindow : public cocos2d::Sprite
{
private:
	cocos2d::ui::Button* m_pButtonOK;

public:
	CREATE_FUNC(MessageWindow);
	virtual bool init();

	// �ÓI�����o
	static bool m_isSaveCheck;
};