/* =====================================================================
//! @param		�uPlayer�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/03/06
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameManager.h"

// �萔
const float		SPEED_MAX_FALL			= -10.0f;		// �ő嗎�����x
const float		SPEED_MAX_FALL_WATER	= -5.0f;		// �ő吅���������x
const float		JUMP_WATER_PLAYER		= 3.0f;			// �����W�����v�̍���

// �N���X�̒�`
class Player : public cocos2d::Sprite
{
private:
	int m_grpX;			// �摜��x���W
	float m_spdX;		// �ړ����xx
	float m_spdY;		// �ړ����xy

	bool m_isStand;		// �n�ʂɂ����Ă��邩�ǂ���

	int m_time;			// ���Ԍv��

public:
	CREATE_FUNC(Player);
	virtual bool init();

	void update(float delta);

	void Gravity(bool dive);										// �d�͕t��
	void Fall(int mapInfo, int season);								// ��������
	void Move(float speed);											// ���E�Ɉړ�
	void Jump();													// �W�����v����

	void Action(int tile, cocos2d::Vec2 tileVec, int season);		// �^�C���ɑ΂��Ă̍s��

	void SetSpdY(float spdY);										// �㉺�̃X�s�[�h���擾

	void AnimationPlayer();											// �v���C���[�A�j���[�V����

	// �ÓI�����o�ϐ�
	static bool m_isJump;											// �W�����v�����Ă��邩
	static bool m_isDive;											// �����ɂ��邩�ǂ���
};