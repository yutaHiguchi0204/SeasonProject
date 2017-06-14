/* =====================================================================
//! @param		�uStageSelectScene�v�N���X�̃w�b�_�t�@�C��
//! @create		���ہ@�E�P
//! @date		17/05/01
===================================================================== */
#pragma once

//�w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"
#include "ui/CocosGUI.h"

class StageSelectScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* m_pSprPlayer;						// �v���C���[�摜

	int m_touchID;										// �^�b�`�����h�c
	
	int m_playerGrpX;									// �摜��x���W
	int m_time;											// ���Ԍv��

	cocos2d::ui::Button* selectButton[NUM_STAGE];		// �X�e�[�W�{�^��
	cocos2d::Sequence* m_move_action_sequence;			// Sequence�A�N�V����

	cocos2d::Sprite* m_pStageName;						// �X�e�[�W��

	cocos2d::Sprite* m_pItemUIspr;						// �A�C�e���t�h�̉摜
	cocos2d::Label* m_pItemUInum;						// �A�C�e���t�h�̃A�C�e��������

	cocos2d::ui::Button* m_pSaveButton;					// �Z�[�u�{�^��
	cocos2d::ui::Button* m_pBackButton;					//�^�C�g���ɖ߂�{�^��

public:
	CREATE_FUNC(StageSelectScene);
	virtual bool init();

	// �V�[�����쐬����
	static cocos2d::Scene* createScene();

	void update(float delta);

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType)  { if (eventType == cocos2d::ui::Widget::TouchEventType::ENDED){ m_touchID = 0; CharactorMove();} }
	void onButtonTouch2(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType) { if (eventType == cocos2d::ui::Widget::TouchEventType::ENDED){ m_touchID = 1; CharactorMove();} }
	void onButtonTouch3(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType) { if (eventType == cocos2d::ui::Widget::TouchEventType::ENDED){ m_touchID = 2; CharactorMove();} }
	void onButtonTouch4(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType) { if (eventType == cocos2d::ui::Widget::TouchEventType::ENDED){ m_touchID = 3; CharactorMove();} }

	void animationPlayer();	// �v���C���[�A�j���[�V����

	void CharactorMove();	//�v���C���[�̈ړ�

	// �ÓI�����o
	static int m_stageID;
};

