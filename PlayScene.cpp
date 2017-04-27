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

// �ÓI�����o�̒�`
bool Stage::m_isChangeSeason;

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
	m_timeCnt = 0;								// ���Ԍv��

	// �X�e�[�W
	m_pStage = Stage::create();
	this->addChild(m_pStage);

	// �{�^������
	m_pButton[static_cast<int>(BUTTON::LEFT)] = OperationButton::create(BUTTON::LEFT);
	m_pButton[static_cast<int>(BUTTON::RIGHT)] = OperationButton::create(BUTTON::RIGHT);
	m_pButton[static_cast<int>(BUTTON::ACTION)] = OperationButton::create(BUTTON::ACTION);

	// �{�^�����V�[���ɂȂ�
	for (int i = 0; i < NUM_BUTTON; i++) this->addChild(m_pButton[i], 3);

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
	m_pStage->Scroll();

	// �A�N�V�����{�^���̏������i�W�����v�{�^���j
	m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::JUMP);

	// �����蔻��
	m_pStage->CheckCollision();

	// ���Ԍv��
	m_timeCnt++;

	// �{�^����������Ă�����v���C���[���ړ�������
	if (!Stage::m_isChangeSeason)
	{
		// �ړ��{�^���������ꂽ�Ƃ��̏���
		m_pStage->CheckButtonHighlighted(BUTTON::LEFT);
		m_pStage->CheckButtonHighlighted(BUTTON::RIGHT);

		// �A�N�V�����{�^���������ꂽ�Ƃ��̏���
		m_pStage->CheckButtonHighlighted(BUTTON::ACTION);
	}

	// �A�N�V�����{�^���̖��x��߂�
	if ((!Player::m_isJump && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::JUMP) ||
		(!Stage::m_isChangeSeason && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::SEASON_BOOK))
	{
		m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright();
	}
}