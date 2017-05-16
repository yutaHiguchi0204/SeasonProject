/* =====================================================================
//! @param		�uBackground�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/04/01
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"

// �N���X�̒�`
class Background : public cocos2d::Sprite
{
private:
	cocos2d::ParticleSystemQuad* m_pParticle;		// �p�[�e�B�N��

public:
	CREATE_FUNC(Background);
	virtual bool init();

	void Change(int season);						// �w�i�̕ύX
	void ParticleScroll(float cameraX);				// �p�[�e�B�N���̃X�N���[��
};