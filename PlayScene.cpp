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
bool Stage::m_isShowObject;
bool Stage::m_leftFlag;
bool Stage::m_rightFlag;

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
	for (int i = 0; i < NUM_BUTTON; i++) this->addChild(m_pButton[i]);

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

	// �{�^���̖��邳
	m_pButton[static_cast<int>(BUTTON::LEFT)]->SetFullBright();

	m_pButton[static_cast<int>(BUTTON::RIGHT)]->SetFullBright();

	// �A�N�V�����{�^���̏������i�W�����v�{�^���j
	m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::JUMP);

	// �����蔻��
	m_pStage->CheckCollision();

	// �Փ˔���
	m_pStage->CheckDecisionColision();

	m_pStage->CheckGimmickCollision();

	// ���Ԍv��
	m_timeCnt++;

	// �{�^����������Ă�����v���C���[���ړ�������
	if (!Stage::m_isShowObject)
	{
		// �ړ��{�^���������ꂽ�Ƃ��̏���
		if(!Stage::m_leftFlag)m_pStage->CheckButtonHighlighted(BUTTON::LEFT);
		if (!Stage::m_rightFlag)m_pStage->CheckButtonHighlighted(BUTTON::RIGHT);

		// �A�N�V�����{�^���������ꂽ�Ƃ��̏���
		m_pStage->CheckButtonHighlighted(BUTTON::ACTION);
	}
	if (Stage::m_leftFlag)
	{
		m_pButton[static_cast<int>(BUTTON::LEFT)]->SetFullBright(false);
	}
	else if (Stage::m_rightFlag)
	{
		m_pButton[static_cast<int>(BUTTON::RIGHT)]->SetFullBright(false);
	}

	// �A�N�V�����{�^���̖��x��߂�
	if ((!Player::m_isJump && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::JUMP)				||
		(!Stage::m_isShowObject && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::SEASON_BOOK)	||
		(!Stage::m_isShowObject && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::SIGN_BOARD))
	{
		m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright();
	}
}