/* =====================================================================
//! @param		�uParticle�v�N���X�̃\�[�X�t�@�C��
//! @create		���ہ@�E�P
//! @date		17/05/19
===================================================================== */
// �w�b�_�t�@�C���̃C���N���[�h
#include "Particle.h"
#include "Stage.h"

// ���O���
USING_NS_CC;

// �����o�֐��̒�`

bool Particle::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �v���Z�b�g�̏����ݒ�
	std::stringstream sFileName;
	sFileName << "particle/particle_" << SEASON_NAME[Stage::m_season] << ".plist";
	m_pParticle = ParticleSystemQuad::create(sFileName.str());

	// �p�[�e�B�N���̍��W�ݒ�i����j
	m_pParticle->setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT);

	// �p�[�e�B�N���̃��������[�N���
	m_pParticle->setAutoRemoveOnFinish(true);

	// �p�[�e�B�N���J�n
	m_pParticle->resetSystem();

	// �p�[�e�B�N�����m�[�h�ɂȂ�
	this->addChild(m_pParticle);

	return true;
}

/* =====================================================================
//! ���@�e		�p�[�e�B�N���̃X�N���[��
//! ���@��		�J�����̍��Wx�ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void Particle::ParticleScroll(float cameraX)
{
	m_pParticle->setPositionX(cameraX);
}