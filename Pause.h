/* =====================================================================
//! @param		�uPause�v�N���X�̃w�b�_�t�@�C��
//! @create		�؉��@�_�P
//! @date		17/05/01
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"
#include "ui/CocosGUI.h"

class Pause : public cocos2d::Sprite
{
private:
	cocos2d::ui::Button* m_pPauseButtonBack;			// �Q�[���ɖ߂�{�^��
	cocos2d::ui::Button* m_pPauseButtonTitle;			// �^�C�g���ɖ߂�{�^��

public:
	CREATE_FUNC(Pause);
	virtual bool init();

	void update(float delta);

	void ClosePause(bool sceneOut = false);				// �|�[�Y��ʂ����
};