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
	setTexture("background/back_spring.png");

	//// �v���Z�b�g�̏����ݒ�
	//m_pParticle = ParticleSystemQuad::create("background/particle_spring.plist");

	//// �p�[�e�B�N���̃��������[�N���
	//m_pParticle->setAutoRemoveOnFinish(true);

	//// �p�[�e�B�N���J�n
	//m_pParticle->resetSystem();

	//// �p�[�e�B�N���̍��W�ݒ�i����j
	//m_pParticle->setPosition(Vec2(0.0f, WINDOW_HEIGHT));

	//// �p�[�e�B�N�����m�[�h�ɂȂ�
	//this->addChild(m_pParticle);

	// �ʒu�̏����ݒ�
	setPosition(Vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f));

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

	//// �t�@�C�����̃��Z�b�g
	//sFileName.str("");
	//sFileName.clear();

	//sFileName << "background/particle_" << SEASON_NAME[season] << ".png";

	//// �p�[�e�B�N���̕ύX
	//m_pParticle->initWithFile(sFileName.str());
}