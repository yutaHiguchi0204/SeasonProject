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
int Stage::m_season;

// �����o�֐��̒�`

bool SeasonBook::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �X�V��������
	scheduleUpdate();

	// �G�ߋL�̐���
	m_pBook = Sprite::create("object/seasonChanger.png");
	this->addChild(m_pBook);

	// �G�߂̃y�[�W�̐���
	std::stringstream sFileName;
	sFileName << "object/page_" << SEASON_NAME[Stage::m_season] << ".png";
	m_pPage = Sprite::create(sFileName.str());
	this->addChild(m_pPage);

	// ����{�^��
	m_pButtonClose = cocos2d::ui::Button::create("object/button_close.png");
	m_pButtonClose->setPositionY(176.0f);
	this->addChild(m_pButtonClose);

	// ��󐶐�
	m_pButtonArrowLeft = cocos2d::ui::Button::create("object/page_arrow.png");
	m_pButtonArrowRight = cocos2d::ui::Button::create("object/page_arrow.png");
	m_pButtonArrowRight->setFlippedX(true);
	m_pButtonArrowLeft->setPositionX(-256.0f);
	m_pButtonArrowRight->setPositionX(256.0f);
	this->addChild(m_pButtonArrowLeft);
	this->addChild(m_pButtonArrowRight);

	// ����{�^���������ꂽ��
	m_pButtonClose->addClickEventListener([&](Ref* ref)
	{
		removeFromParent();
		Stage::m_isShowObject = false;
	});

	// �G�ߋL�̖��{�^���������ꂽ��
	m_pButtonArrowLeft->addClickEventListener([&](Ref* ref) { Change(-1); });
	m_pButtonArrowRight->addClickEventListener([&](Ref* ref) { Change(1); });

	return true;
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
	if (Stage::m_season < static_cast<int>(SEASON::WINTER)) Stage::m_season = Player::m_numBookmark - 1;
	if (Stage::m_season > Player::m_numBookmark - 1)		Stage::m_season = static_cast<int>(SEASON::WINTER);

	// �G�߂̃y�[�W��ς���
	std::stringstream sFileName;
	sFileName << "object/page_" << SEASON_NAME[Stage::m_season] << ".png";
	m_pPage->setTexture(sFileName.str());
}