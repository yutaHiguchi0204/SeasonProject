/* =====================================================================
//! @param		�uLogoScene�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/05/25
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"

// �N���X�̒�`
class LogoScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* m_pLogo;
	int m_time;

public:
	CREATE_FUNC(LogoScene);
	virtual bool init();

	// �V�[�����쐬����
	static cocos2d::Scene* createScene();

	void update(float delta);
};