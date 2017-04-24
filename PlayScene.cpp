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

// ������
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
	m_pButton[static_cast<int>(BUTTON::LEFT)] = OperationButton::create(BUTTON::LEFT);
	m_pButton[static_cast<int>(BUTTON::RIGHT)] = OperationButton::create(BUTTON::RIGHT);
	m_pButton[static_cast<int>(BUTTON::ACTION)] = OperationButton::create(BUTTON::ACTION);

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

	// �A�N�V�����{�^���̏������i�W�����v�{�^���j
	m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::JUMP);

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
		if (m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::JUMP)
		{
			m_pPlayer->Jump();
			m_pButton[static_cast<int>(BUTTON::ACTION)]->setColor(Color3B(128.0f, 128.0f, 128.0f));
		}
	}

	// �A�N�V�����{�^���ݒ�
	if (!Player::m_isJump)
	{
		m_pButton[static_cast<int>(BUTTON::ACTION)]->setColor(Color3B(255.0f, 255.0f, 255.0f));
	}
}