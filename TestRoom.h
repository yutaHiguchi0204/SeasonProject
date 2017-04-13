/* =====================================================================
//! @param		�f�o�b�O�p
//! @create		����@�T��
//! @date		17/03/05
===================================================================== */
#pragma once

#include "GameManager.h"
#include "Player.h"
#include "ui/CocosGUI.h"

class Test : public cocos2d::Scene
{
private:
	int m_season;										// �G��
	int m_map[NUM_ROW][NUM_COLUMN];						// �}�b�v

	cocos2d::Sprite* m_pBack;							// �w�i
	cocos2d::Sprite* m_pTip[NUM_ROW][NUM_COLUMN];		// �}�b�v�`�b�v
	cocos2d::Sprite* m_pSignBoard;						// �Ŕ�
	cocos2d::Sprite* m_pBoard;							// ������

	Player* m_pPlayer;									// �v���C���[
	cocos2d::ui::Button* m_pButtonLeft;					// ���{�^��
	cocos2d::ui::Button* m_pButtonRight;				// �E�{�^��
	cocos2d::ui::Button* m_pButtonAction;				// �A�N�V�����{�^��

public:
	CREATE_FUNC(Test);
	virtual bool init();

	void update(float delta);

	// �֐��̒x�����s
	void CallFuncAfter(const float& delay, const std::function<void()>& func)
	{
		runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(delay), cocos2d::CallFunc::create(func), nullptr));
	}

	void TestRoom();
	void ChangeSeason();

	void Import();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	//static int m_timeCnt;							// �^�C�}�[�v��
};