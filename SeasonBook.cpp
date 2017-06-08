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

// �萔
const int HERF_COLOR = 127;

// �����o�֐��̒�`

bool SeasonBook::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �X�V��������
	scheduleUpdate();

	// �����o�ϐ��̏�����
	m_time = 0;

	// �G�ߋL�̐���
	m_pBook = Sprite::create("object/seasonChanger.png");
	m_pBook->setOpacity(0x80);
	this->addChild(m_pBook);

	// �G�߂̃y�[�W�̐���
	std::stringstream sFileName;
	sFileName << "object/page_" << SEASON_NAME[Stage::m_season] << ".png";
	m_pPage = Sprite::create(sFileName.str());
	m_pPage->setOpacity(0x80);
	this->addChild(m_pPage);

	// ����{�^��
	m_pButtonClose = cocos2d::ui::Button::create("object/button_close.png");
	m_pButtonClose->setPositionY(-144.0f);
	this->addChild(m_pButtonClose);

	// ��󐶐�
	m_pButtonArrowLeft = cocos2d::ui::Button::create("object/page_arrow.png");
	m_pButtonArrowRight = cocos2d::ui::Button::create("object/page_arrow.png");
	m_pButtonArrowRight->setFlippedX(true);
	m_pButtonArrowLeft->setPositionX(-256.0f);
	m_pButtonArrowRight->setPositionX(256.0f);
	m_pButtonArrowLeft->setOpacity(0x80);
	m_pButtonArrowRight->setOpacity(0x80);
	this->addChild(m_pButtonArrowLeft);
	this->addChild(m_pButtonArrowRight);

	// ����{�^���������ꂽ��
	m_pButtonClose->addClickEventListener([&](Ref* ref)
	{
		removeFromParent();
		PlayScene::m_pButton[static_cast<int>(BUTTON::SEASON_BOOK)]->SetFullBright(true);
		Stage::m_isShowObject = false;
	});

	// �G�ߋL�̖��{�^���������ꂽ��
	m_pButtonArrowLeft->addClickEventListener([&](Ref* ref) { Change(-1); });
	m_pButtonArrowRight->addClickEventListener([&](Ref* ref) { Change(1); });

	// �y�[�W�߂��鉹�̐���
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::SE_SELECT), false);

	return true;
}

/* =====================================================================
//! ���@�e		�X�V����
//! ���@��		�_�~�[�����ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void SeasonBook::update(float delta)
{
	// �����x�A�j���[�V����
	OpacityAnimation();

	// ���Ԍv��
	m_time++;
}

/* =====================================================================
//! ���@�e		�G�ߊ���
//! ���@��		�v���X���}�C�i�X�iint�j
//! �߂�l		�Ȃ�
===================================================================== */
void SeasonBook::Change(int num)
{
	Stage::m_season += num;

	// ����
	if (Stage::m_season < static_cast<int>(SEASON::SPRING)) Stage::m_season = static_cast<int>(SEASON::WINTER);
	if (Stage::m_season > static_cast<int>(SEASON::WINTER))	Stage::m_season = static_cast<int>(SEASON::SPRING);

	// �G�߂̃y�[�W��ς���
	std::stringstream sFileName;
	sFileName << "object/page_" << SEASON_NAME[Stage::m_season] << ".png";
	m_pPage->setTexture(sFileName.str());

	//�G�ߐ؂�ւ��̉�����
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::SE_CHANGE), false);
}

/* =====================================================================
//! ���@�e		�G�ߋL�̓����x�A�j���[�V����
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void SeasonBook::OpacityAnimation()
{
	// �t�F�[�h
	if (m_time / HERF_COLOR % 2 == 0)
	{
		m_pBook->setOpacity(m_pBook->getOpacity() + 0x01);
		m_pPage->setOpacity(m_pPage->getOpacity() + 0x01);
		m_pButtonArrowLeft->setOpacity(m_pButtonArrowLeft->getOpacity() + 0x01);
		m_pButtonArrowRight->setOpacity(m_pButtonArrowRight->getOpacity() + 0x01);
	}
	else
	{
		m_pBook->setOpacity(m_pBook->getOpacity() - 0x01);
		m_pPage->setOpacity(m_pPage->getOpacity() - 0x01);
		m_pButtonArrowLeft->setOpacity(m_pButtonArrowLeft->getOpacity() - 0x01);
		m_pButtonArrowRight->setOpacity(m_pButtonArrowRight->getOpacity() - 0x01);
	}
}