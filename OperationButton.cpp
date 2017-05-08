/* =====================================================================
//! @param		�uOperationButton�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/04/20
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "OperationButton.h"
#include <fstream>
#include <sstream>
#include "PlayScene.h"

// ���O���
USING_NS_CC;

// �萔
const Color3B FULL_COLOR = Color3B(255.0f, 255.0f, 255.0f);
const Color3B HERF_COLOR = Color3B(128.0f, 128.0f, 128.0f);

// �����o�֐��̒�`

// �������i�f�t�H���g�j
bool OperationButton::init()
{
	if (!cocos2d::ui::Button::init())
	{
		return false;
	}

	// �A�N�V�����t���O���f�t�H���g��Ԃɂ���i�W�����v�{�^���j
	m_actionFlg = ACTION::JUMP;

	return true;
}

// �������i�{�^���w��j
bool OperationButton::init(BUTTON button)
{
	if (!cocos2d::ui::Button::init())
	{
		return false;
	}

	// �摜�ݒ�
	switch (button)
	{
	case BUTTON::LEFT:
		loadTextureNormal("object/button_arrow.png");
		setPosition(Vec2(96.0f, 96.0f));
		break;

	case BUTTON::RIGHT:
		loadTextureNormal("object/button_arrow.png");
		setPosition(Vec2(288.0f, 96.0f));
		setFlippedX(true);
		break;

	case BUTTON::ACTION:
		loadTextureNormal("object/button_action.png");
		setPosition(Vec2(WINDOW_WIDTH - 96.0f, 96.0f));
		break;

	case BUTTON::PAUSE:
		loadTextureNormal("object/button_pause.png");
		setPosition(Vec2(88.0f, WINDOW_HEIGHT - 48.0f));
		break;
	}

	// �A�N�V�����t���O���f�t�H���g��Ԃɂ���i�W�����v�{�^���j
	m_actionFlg = ACTION::JUMP;

	return true;
}

/* =====================================================================
//! ���@�e		�{�^������
//! ���@��		�{�^���iBUTTON�j
//! �߂�l		�Ȃ�
===================================================================== */
OperationButton* OperationButton::create(BUTTON button)
{
	OperationButton* btn = new (std::nothrow) OperationButton;
	if (btn && btn->init(button))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

/* =====================================================================
//! ���@�e		�{�^���̖��x�ݒ�
//! ���@��		�l�`�w���Â߂��ibool�j
//! �߂�l		�Ȃ�
===================================================================== */
void OperationButton::SetFullBright(bool full)
{
	if (full)	setColor(FULL_COLOR);			// �l�`�w
	else		setColor(HERF_COLOR);			// �Â�
}

/* =====================================================================
//! ���@�e		�A�N�V�����t���O�̕ύX
//! ���@��		�A�N�V����ID�iACTION�j
//! �߂�l		�Ȃ�
===================================================================== */
void OperationButton::ChangeActionFlg(ACTION action)
{
	// �A�N�V�����t���O�̕ύX
	m_actionFlg = action;

	// �{�^���̉摜�̕ύX
	ChangeButtonTexture(action);
}

/* =====================================================================
//! ���@�e		�{�^���̉摜��ς���
//! ���@��		�A�N�V����ID�iACTION�j
//! �߂�l		�Ȃ�
===================================================================== */
void OperationButton::ChangeButtonTexture(ACTION action)
{
	std::stringstream sFileName;
	sFileName << "object/button_" << ACTION_NAME[static_cast<int>(action)] << ".png";

	// �w�i�̕ύX
	loadTextureNormal(sFileName.str());
}

/* =====================================================================
//! ���@�e		�A�N�V�����t���O�̎擾
//! ���@��		�Ȃ�
//! �߂�l		�A�N�V�����t���O�iACTION�j
===================================================================== */
ACTION OperationButton::GetActionFlg()
{
	return m_actionFlg;
}