/* =====================================================================
//! @param		�uPlayScene�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/03/04
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "PlayScene.h"

// ���O���
USING_NS_CC;
using namespace std;

// �����o�֐��̒�`

// �V�[���Ǘ�
Scene* PlayScene::createScene()
{
	// �V�[�����쐬����
	auto scene = Scene::create();

	// ���C���[���쐬����
	auto layer = PlayScene::create();

	// ���C���[���V�[���ɒǉ�����
	scene->addChild(layer);

	// �V�[����Ԃ�
	return scene;
}

bool PlayScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// �X�V��������
	scheduleUpdate();

	// �e�f�[�^�̏����ݒ�
	m_timeCnt = 0;										// ���Ԍv��

	// �X�e�[�W
	m_pStage = Stage::create();
	this->addChild(m_pStage);

	// �{�^������
	m_pButton[static_cast<int>(BUTTON::LEFT)]	= cocos2d::ui::Button::create("object/button_arrow.png");
	m_pButton[static_cast<int>(BUTTON::RIGHT)]	= cocos2d::ui::Button::create("object/button_arrow.png");
	m_pButton[static_cast<int>(BUTTON::ACTION)] = cocos2d::ui::Button::create("object/button_action.png");

	// �{�^���̏����ݒ�
	m_pButton[static_cast<int>(BUTTON::RIGHT)]->setFlippedX(true);
	m_pButton[static_cast<int>(BUTTON::LEFT)]->setPosition(Vec2(96.0f, 96.0f));
	m_pButton[static_cast<int>(BUTTON::RIGHT)]->setPosition(Vec2(288.0f, 96.0f));
	m_pButton[static_cast<int>(BUTTON::ACTION)]->setPosition(Vec2(WINDOW_WIDTH - 96.0f, 96.0f));

	// �{�^�����V�[���ɂȂ�
	for (int i = 0; i < NUM_BUTTON; i++) this->addChild(m_pButton[i], 3);

	// �v���C���[
	m_pPlayer = Player::create();
	m_pPlayer->setPosition(Vec2(64.0f, 216.0f));
	this->addChild(m_pPlayer, 1);

	return true;
}

/* =====================================================================
//! ���@�e		�X�V����
//! ���@��		�_�~�[�����ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void PlayScene::update(float delta)
{
	// �X�N���[��
	m_pStage->Scroll(m_pPlayer->getPositionX(), m_pButton);

	// �����蔻��
	m_pStage->CheckCollision(m_pPlayer);

	// ���Ԍv��
	m_timeCnt++;

	// �{�^����������Ă�����v���C���[���ړ�������
	if (m_pButton[static_cast<int>(BUTTON::LEFT)]->isHighlighted())
	{
		// �v���C���[�̌�����ݒ�
		m_pPlayer->setFlippedX(true);

		// �v���C���[�̈ړ�
		if (m_pPlayer->getPositionX() > SIZE_PLAYER / 2)
		{
			m_pPlayer->Move(-SPEED_MOVE_PLAYER);
		}
	}
	else if (m_pButton[static_cast<int>(BUTTON::RIGHT)]->isHighlighted())
	{
		// �v���C���[�̌�����ݒ�
		m_pPlayer->setFlippedX(false);

		// �v���C���[�̈ړ�
		if (m_pPlayer->getPositionX() < STAGE_WIDTH - SIZE_PLAYER / 2)
		{
			m_pPlayer->Move(SPEED_MOVE_PLAYER);
		}
	}

	// �A�N�V�����{�^���������ꂽ��v���C���[���W�����v������
	if (m_pButton[static_cast<int>(BUTTON::ACTION)]->isHighlighted() && !Player::m_isJump)
	{
		m_pPlayer->Jump();
		m_pButton[static_cast<int>(BUTTON::ACTION)]->setColor(Color3B(128.0f, 128.0f, 128.0f));
	}

	// �A�N�V�����{�^���ݒ�
	if (!Player::m_isJump)
	{
		m_pButton[static_cast<int>(BUTTON::ACTION)]->setColor(Color3B(255.0f, 255.0f, 255.0f));
	}

	// �v���C���[�ƋG�ߋL�̓����蔻��
	/*Rect rectSeasonBook = m_pSeasonBook->getBoundingBox();
	if (rectPlayer.intersectsRect(rectSeasonBook))
	{
		m_pButtonAction->loadTextureNormal("object/button_book.png");
	}
	else
	{
		m_pButtonAction->loadTextureNormal("object/button_action.png");
	}*/

	// �v���C���[�ƊŔ̓����蔻��
	/*Rect rectSignBoard = m_pSignBoard01->getBoundingBox();
	if (rectPlayer.intersectsRect(rectSignBoard))
	{
		m_pBoard01->setVisible(true);
	}
	else
	{
		m_pBoard01->setVisible(false);
	}*/
}