/* =====================================================================
//! @param		�uTwoOptionWindow�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/05/28
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "TwoOptionWindow.h"

// ���O���
USING_NS_CC;

// �ÓI�����o�ϐ��̏�����
bool TwoOptionWindow::m_isResetCheck;

// �����o�֐��̒�`

// ������
bool TwoOptionWindow::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �����o�ϐ��̏�����
	m_isResetCheck = true;

	// ���
	setTexture("object/resetCheck.png");

	// �n�j�{�^��
	m_pButtonOK = cocos2d::ui::Button::create("object/button_ok.png");
	m_pButtonOK->setPosition(Vec2(160.0f, 96.0f));
	this->addChild(m_pButtonOK);

	// �L�����Z���{�^��
	m_pButtonCancel = cocos2d::ui::Button::create("object/button_cancel.png");
	m_pButtonCancel->setPosition(Vec2(480.0f, 96.0f));
	this->addChild(m_pButtonCancel);

	// �n�j�{�^���^�b�v
	m_pButtonOK->addClickEventListener([&](Ref* ref) {

		// ���Z�b�g
		GameManager& gm = GameManager::GetInstance();
		gm.ResetPageInfo();

		// �㏈��
		runAction(Sequence::create(
			ScaleTo::create(0.5f, 0.0f),
			CallFunc::create([&]() { m_isResetCheck = false; removeFromParent(); }),
			nullptr
		)
		);
	});

	// �L�����Z���{�^���^�b�v
	m_pButtonCancel->addClickEventListener([&](Ref* ref) {

		// �㏈��
		runAction(Sequence::create(
			ScaleTo::create(0.5f, 0.0f),
			CallFunc::create([&]() { m_isResetCheck = false; removeFromParent(); }),
			nullptr
		)
		);
	});

	return true;
}