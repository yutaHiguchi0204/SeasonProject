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
	cocos2d::Sprite* m_pSprPlayer;
	cocos2d::ui::Button* m_selectButton; //�{�^��
	
	int m_playerGrpX;	// �摜��x���W
	int m_time;			// ���Ԍv��

public:
	CREATE_FUNC(StageSelectScene);
	virtual bool init();

	// �V�[�����쐬����
	static cocos2d::Scene* createScene();

	void update(float delta);

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType);

	void animationPlayer();	// �v���C���[�A�j���[�V����

};

