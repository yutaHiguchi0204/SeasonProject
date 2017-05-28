/* =====================================================================
//! @param		�uClearScene�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/05/05
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"

// �N���X�̒�`
class ClearScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* m_pBack;			// �w�i
	cocos2d::Sprite* m_pMsgBack;		// �߂郁�b�Z�[�W

	int m_time;

public:
	CREATE_FUNC(ClearScene);
	virtual bool init();

	// �V�[�����쐬����
	static cocos2d::Scene* createScene();

	// �X�V����
	void update(float delta);

	// �^�b�`����
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* pEvent);
};