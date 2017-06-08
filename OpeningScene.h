/* =====================================================================
//! @param		�uOpeningScene�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/06/07
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"

// �N���X�̒�`
class OpeningScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* m_pButtonSkip;			// �X�L�b�v�{�^��
	int m_time;								// ����

public:
	CREATE_FUNC(OpeningScene);
	virtual bool init();

	// �V�[�����쐬����
	static cocos2d::Scene* createScene();

	void update(float delta);

	void DrawLines();						// �Z���t��\��

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) { return true; };
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	// �֐��̒x�����s
	void CallFuncAfter(const float& delay, const std::function<void()>& func)
	{
		runAction(cocos2d::Sequence::create
		(cocos2d::DelayTime::create(delay), cocos2d::CallFunc::create(func), nullptr));
	}
};