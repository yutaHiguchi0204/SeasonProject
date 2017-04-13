/* =====================================================================
//! @param		�uPlayScene�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/03/04
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"
#include "Player.h"
#include "SeasonBook.h"
#include "Stage.h"
#include "ui/CocosGUI.h"

// �N���X�̒�`
class PlayScene : public cocos2d::Scene
{
private:
	int m_mapInfo[NUM_ROW][NUM_COLUMN];					// �}�b�v���

	Stage* m_pStage;									// �X�e�[�W

	//cocos2d::Sprite* m_pSignBoard01;					// �ŔP
	//cocos2d::Sprite* m_pBoard01;						// �����ՂP

	Player* m_pPlayer;						// �v���C���[
	//SeasonBook* m_pSeasonBook;				// �G�ߋL

	cocos2d::ui::Button* m_pButton[NUM_BUTTON];			// �{�^��

public:
	CREATE_FUNC(PlayScene);
	virtual bool init();

	// �V�[�����쐬����
	static cocos2d::Scene* createScene();

	void update(float delta);				// �X�V����

	//bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	static int m_timeCnt;					// ���Ԍv��
};