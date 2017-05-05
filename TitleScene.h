/* =====================================================================
//! @param		�uTitleScene�v�N���X�̃w�b�_�t�@�C��
//! @create		���ہ@�E�P
//! @date		17/05/01
===================================================================== */
#pragma once

//�w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"
#include "ui/CocosGUI.h"

class TitleScene : public cocos2d::Scene
{
private:
public:

	CREATE_FUNC(TitleScene);

	virtual bool init();

	// �V�[�����쐬����
	static cocos2d::Scene* createScene();
	
	void update(float delta);

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType);

	cocos2d::ui::Button* m_tButton; //�{�^��

};

