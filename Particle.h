/* =====================================================================
//! @param		�uParticle�v�N���X�̃w�b�_�t�@�C��
//! @create		���ہ@�E�P
//! @date		17/05/19
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"

// �N���X�̒�`
class Particle : public cocos2d::Sprite
{
private:
	cocos2d::ParticleSystemQuad* m_pParticle;		// �p�[�e�B�N��

public:
	CREATE_FUNC(Particle);
	virtual bool init();

	void ParticleScroll(float cameraX);				// �p�[�e�B�N���̃X�N���[��
};