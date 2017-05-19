/* =====================================================================
//! @param		�uBackground�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/04/01
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Background.h"

// ���O���
USING_NS_CC;

// �����o�֐��̒�`

bool Background::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �摜�̏����ݒ�
	setTexture("background/back_winter.png");

	// �v���Z�b�g�̏����ݒ�
	m_pParticle = ParticleSystemQuad::create("particle/particle_winter.plist");

	// �p�[�e�B�N���̃��������[�N���
	m_pParticle->setAutoRemoveOnFinish(true);

	// �p�[�e�B�N���J�n
	m_pParticle->resetSystem();

	// �p�[�e�B�N���̍��W�ݒ�i����j
	m_pParticle->setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT);

	// �p�[�e�B�N�����m�[�h�ɂȂ�
	this->addChild(m_pParticle);

	// �ʒu�̏����ݒ�
	setPosition(STAGE_MIDDLE);

	return true;
}

/* =====================================================================
//! ���@�e		�w�i�̕ύX
//! ���@��		�G�߁iint�j
//! �߂�l		�Ȃ�
===================================================================== */
void Background::Change(int season)
{
	std::stringstream sFileName;
	sFileName << "background/back_" << SEASON_NAME[season] << ".png";

	// �w�i�̕ύX
	setTexture(sFileName.str());

	//�Ă̋G�߂�����\��
	if (season == static_cast<int>(SEASON::SUMMER))
	{
		m_pParticle->setVisible(false);
	}

	// �ĈȊO�̓p�[�e�B�N�����o��
	if (season != static_cast<int>(SEASON::SUMMER))
	{
		// �t�@�C�����̃��Z�b�g
		sFileName.str("");
		sFileName.clear();

		//�p�[�e�B�N���̕\��
		m_pParticle->setVisible(true);

		sFileName << "particle/particle_" << SEASON_NAME[season] << ".plist";

		// �p�[�e�B�N���̕ύX
		m_pParticle->initWithFile(sFileName.str());
	}
}

/* =====================================================================
//! ���@�e		�p�[�e�B�N���̃X�N���[��
//! ���@��		�J�����̍��Wx�ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void Background::ParticleScroll(float cameraX)
{
	m_pParticle->setPositionX(cameraX);
}