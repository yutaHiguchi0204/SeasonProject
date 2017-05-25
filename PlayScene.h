/* =====================================================================
//! @param		�uPlayScene�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/03/04
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"
#include "OperationButton.h"
#include "Pause.h"
#include "Stage.h"

// �N���X�̒�`
class PlayScene : public cocos2d::Scene
{
private:
	Stage* m_pStage;										// �X�e�[�W
	Pause* m_pPause;										// �|�[�Y

public:
	CREATE_FUNC(PlayScene);
	virtual bool init();

	// �V�[�����쐬����
	static cocos2d::Scene* createScene();

	void update(float delta);

	void CheckPauseButtonHighlighted();						// �|�[�Y�{�^���������ꂽ���̏���

	// �ÓI�����o
	static OperationButton* m_pButton[NUM_BUTTON];			// �A�N�V�����{�^���i�ړ��A�|�[�Y�܂ށj
};