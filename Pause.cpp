/* =====================================================================
//! @param		�uPause�v�N���X�̃\�[�X�t�@�C��
//! @create		�؉��@�_�P
//! @date		17/05/01
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Pause.h"
#include "Stage.h"
#include "StageSelectScene.h"
#include "TitleScene.h"

// ���O���
USING_NS_CC;
using namespace std;

// �����o�֐��̒�`

// ������
bool Pause::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �X�V��������
	scheduleUpdate();

	// �|�[�Y��ʂ̐ݒ�
	setTexture("pause/pauseBack.png");

	// ���C����ʂ̐ݒ�
	m_pPauseMain = Sprite::create("pause/pause.png");
	m_pPauseMain->setPosition(Vec2(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF));
	this->addChild(m_pPauseMain);

	// �Q�[���ɖ߂�{�^���̐���
	m_pPauseButtonBack = cocos2d::ui::Button::create("pause/button_backGame.png");
	m_pPauseButtonBack->setPosition(Vec2(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF - 32.0f));
	this->addChild(m_pPauseButtonBack);

	// �^�C�g���ɖ߂�{�^���̐���
	m_pPauseButtonTitle = cocos2d::ui::Button::create("pause/button_backTitle.png");
	m_pPauseButtonTitle->setPosition(Vec2(WINDOW_WIDTH_HERF - 192.0f, WINDOW_HEIGHT_HERF - 96.0f));
	this->addChild(m_pPauseButtonTitle);

	// �X�e�[�W�I����ʂɖ߂�{�^���̐���
	m_pPauseButtonSelect = cocos2d::ui::Button::create("pause/button_backSelect.png");
	m_pPauseButtonSelect->setPosition(Vec2(WINDOW_WIDTH_HERF + 128.0f, WINDOW_HEIGHT_HERF - 96.0f));
	this->addChild(m_pPauseButtonSelect);

	return true;
}

/* =====================================================================
//! ���@�e		�X�V����
//! ���@��		�_�~�[�����ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void Pause::update(float delta)
{
	// �Q�[���ɖ߂�{�^���������ꂽ��
	if (m_pPauseButtonBack->isHighlighted())
	{

		//�|�[�Y����鉹�̐���
		SoundManager& sm = SoundManager::getInstance();
		sm.PlayGameSound(static_cast<int>(SOUND::SE_CLOSE), false);

		// �㏈��
		Stage::m_isPause = false;
		removeFromParent();
	}
	// �^�C�g���ɖ߂�{�^���������ꂽ��
	else if (m_pPauseButtonTitle->isHighlighted())
	{
		//�^�C�g���ɖ߂鉹�̐���
		SoundManager& sm = SoundManager::getInstance();
		sm.UncacheGameSoundAll();
		sm.PlayGameSound(static_cast<int>(SOUND::BGM_TITLE), false);

		// ���̃V�[�����쐬����
		Scene* nextScene = TitleScene::createScene();

		// ���̃V�[���Ɉڍs
		_director->replaceScene(nextScene);

		unscheduleUpdate();
	}
	// �X�e�[�W�I����ʂɖ߂�{�^���������ꂽ��
	else if (m_pPauseButtonSelect->isHighlighted())
	{

		//�|�[�Y����鉹�̐���
		SoundManager& sm = SoundManager::getInstance();
		sm.UncacheGameSoundAll();
		sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);

		// ���̃V�[�����쐬����
		Scene* nextScene = StageSelectScene::createScene();

		// ���̃V�[���Ɉڍs
		_director->replaceScene(nextScene);

		unscheduleUpdate();
	}
}