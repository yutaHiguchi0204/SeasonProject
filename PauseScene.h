/* =====================================================================
//! @param		�uPauseScene�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/05/01
===================================================================== */
#pragma once

//�w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"
#include "OperationButton.h"
#include"PlayScene.h"

class PauseScene :cocos2d::Scene
{
private:


public:
	CREATE_FUNC(PauseScene);
	virtual bool init();


	void update(float delta);

	void onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType);


	static OperationButton* m_pButton[NUM_BUTTON];

	
	


};

