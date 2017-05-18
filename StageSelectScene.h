/* =====================================================================
//! @param		�uStageSelectScene�v�N���X�̃w�b�_�t�@�C��
//! @create		���ہ@�E�P
//! @date		17/05/01
===================================================================== */
#pragma once

//�w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"
#include "ui/CocosGUI.h"

const int STAGEMAX_NUM = 4;	//�X�e�[�W�p�̔z��

class StageSelectScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* m_pSprPlayer;
	
	int m_playerGrpX;	// �摜��x���W
	int m_time;			// ���Ԍv��

public:
	CREATE_FUNC(StageSelectScene);
	virtual bool init();

	// �V�[�����쐬����
	static cocos2d::Scene* createScene();

	void update(float delta);

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType)  { if (eventType == cocos2d::ui::Widget::TouchEventType::BEGAN){ m_touchID = 0;CharactorMove();} }
	void onButtonTouch2(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType) { if (eventType == cocos2d::ui::Widget::TouchEventType::BEGAN){ m_touchID = 1;CharactorMove();} }
	void onButtonTouch3(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType) { if (eventType == cocos2d::ui::Widget::TouchEventType::BEGAN){ m_touchID = 2;CharactorMove();} }
	void onButtonTouch4(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType) { if (eventType == cocos2d::ui::Widget::TouchEventType::BEGAN){ m_touchID = 3;CharactorMove();} }


	void animationPlayer();	// �v���C���[�A�j���[�V����

	void CharactorMove();	//�v���C���[�̈ړ�

	// �ÓI�����o
	static int m_stageID;

	//�^�b�`����ID
	int m_touchID;

	cocos2d::ui::Button* selectButton[STAGEMAX_NUM];

	/// �f�o�b�O�p�����o�ϐ�
	cocos2d::EventListenerKeyboard* keyListener;
	cocos2d::Label* text;

};

