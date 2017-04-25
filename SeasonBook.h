/* =====================================================================
//! @param		�uSeasonBook�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/03/19
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"
#include "SeasonBook.h"
#include "ui/CocosGUI.h"

// �N���X�̒�`
class SeasonBook : public cocos2d::Sprite
{
private:
	cocos2d::Sprite* m_pBook;					// �{��

	cocos2d::ui::Button* m_pButtonClose;		// ����{�^��
	cocos2d::ui::Button* m_pButtonArrowLeft;	// �����
	cocos2d::ui::Button* m_pButtonArrowRight;	// �E���

public:
	CREATE_FUNC(SeasonBook);
	virtual bool init();

	void update(float delta);
};