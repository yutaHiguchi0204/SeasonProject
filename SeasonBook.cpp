/* =====================================================================
//! @param		�uSeasonBook�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/03/19
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "SeasonBook.h"
#include "PlayScene.h"

// ���O���
USING_NS_CC;

// �ÓI�����o�̒�`
bool PlayScene::m_isChangeSeason;

// �����o�֐��̒�`

bool SeasonBook::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �X�V��������
	scheduleUpdate();

	// �G�ߊ����̃y�[�W��\��
	m_pBook = Sprite::create("object/seasonChanger.png");
	this->addChild(m_pBook);

	// ����{�^��
	m_pButtonClose = cocos2d::ui::Button::create("object/button_close.png");
	m_pButtonClose->setPositionY(160.0f);
	this->addChild(m_pButtonClose);

	// ��󐶐�
	m_pButtonArrowLeft = cocos2d::ui::Button::create("object/page_arrow.png");
	m_pButtonArrowRight = cocos2d::ui::Button::create("object/page_arrow.png");
	m_pButtonArrowRight->setFlippedX(true);
	m_pButtonArrowLeft->setPositionX(-256.0f);
	m_pButtonArrowRight->setPositionX(256.0f);
	this->addChild(m_pButtonArrowLeft);
	this->addChild(m_pButtonArrowRight);

	return true;
}

/* =====================================================================
//! ���@�e		�X�V����
//! ���@��		�_�~�[�����ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void SeasonBook::update(float delta)
{
	// ����{�^����������Ă���{�����
	if (m_pButtonClose->isHighlighted())
	{
		removeFromParent();
		PlayScene::m_isChangeSeason = false;
	}
}