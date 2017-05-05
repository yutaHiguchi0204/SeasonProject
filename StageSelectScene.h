/* =====================================================================
//! @param		�uStageSelectScene�v�N���X�̃w�b�_�t�@�C��
//! @create		���ہ@�E�P
//! @date		17/05/01
===================================================================== */
#pragma once

//�w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"

class StageSelectScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(StageSelectScene);
	virtual bool init();

	// �V�[�����쐬����
	static cocos2d::Scene* createScene();

	void update(float delta);

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);

};

