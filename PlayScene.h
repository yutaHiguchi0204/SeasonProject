/* =====================================================================
//! @param		�uPlayScene�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/03/04
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"
#include "OperationButton.h"
#include "Stage.h"

// �N���X�̒�`
class PlayScene : public cocos2d::Scene
{
private:
	Stage* m_pStage;									// �X�e�[�W

public:
	CREATE_FUNC(PlayScene);
	virtual bool init();

	// �V�[�����쐬����
	static cocos2d::Scene* createScene();

	void update(float delta);				// �X�V����

	// �ÓI�����o
	static int m_timeCnt;									// ���Ԍv��
	static OperationButton* m_pButton[NUM_BUTTON];			// �{�^��
};