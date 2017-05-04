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
	// �X�e�[�W
	Stage* m_pStage;

	cocos2d::Sprite* Pauseback;
	cocos2d::ui::Button* m_pTitleButton;
	cocos2d::ui::Button* m_pGameBackButton;


public:
	CREATE_FUNC(PlayScene);
	virtual bool init();

	// �V�[�����쐬����
	static cocos2d::Scene* createScene();

	void update(float delta);				// �X�V����

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType);

	// �ÓI�����o
	static int m_timeCnt;									// ���Ԍv��
	static OperationButton* m_pButton[NUM_BUTTON];			// �{�^��
	//�|�[�Y�{�^��
	cocos2d::ui::Button* m_pPauseButton;
	//�J����
	cocos2d::Camera* m_pCamera;
	
	void EnabledPauseback(bool TorF);
};