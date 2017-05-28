/* =====================================================================
//! @param		�uMessageWindow�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/05/28
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "MessageWindow.h"

// ���O���
USING_NS_CC;

// �ÓI�����o�ϐ��̏�����
bool MessageWindow::m_isSaveCheck;

// �����o�֐��̒�`

// ������
bool MessageWindow::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �����o�ϐ��̏�����
	m_isSaveCheck = true;

	// ���
	setTexture("object/saveMsg.png");

	// �n�j�{�^��
	m_pButtonOK = cocos2d::ui::Button::create("object/button_ok.png");
	m_pButtonOK->setPosition(Vec2(320.0f, 96.0f));
	this->addChild(m_pButtonOK);

	// �n�j�{�^���m�F
	m_pButtonOK->addClickEventListener([&](Ref* ref) {

		// ���艹�̐���
		SoundManager& sm = SoundManager::getInstance();
		sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);

		runAction(Sequence::create(
			ScaleTo::create(0.5f, 0.0f),
			CallFunc::create([&]() { m_isSaveCheck = false; removeFromParent(); }),
			nullptr
		)
		);

	});

	return true;
}