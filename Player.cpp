/* =====================================================================
//! @param		�uPlayer�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/03/06
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Player.h"
#include "PlayScene.h"
#include "Stage.h"
#include "StageSelectScene.h"

// ���O���
USING_NS_CC;

// �ÓI�����o�̒�`
bool Player::m_isJump;

// �����o�֐��̒�`

bool Player::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �X�V��������
	scheduleUpdate();

	// �v���C���[�̉摜�ݒ�
	setTexture("object/player.png");

	// �����o�̏����ݒ�
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_isStand = false;
	m_isJump = false;
	m_isDive = false;
	m_time = 0;

	return true;
}

/* =====================================================================
//! ���@�e		�X�V����
//! ���@��		�_�~�[�����ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void Player::update(float delta)
{
	if (!Stage::m_isPause)
	{
		// �ړ�
		setPosition(getPosition() + Vec2(m_spdX, m_spdY));
		m_spdX = 0.0f;

		// �d��
		if (!m_isStand) Gravity(m_isDive);

		// �v���C���[�A�j���[�V����
		if (m_time % SPEED_ANIMATION == 0) AnimationPlayer();

		// �摜�̕ύX
		setTextureRect(Rect(m_grpX, 0, SIZE_PLAYER, SIZE_PLAYER));

		// ���Ԍv��
		m_time++;
	}

	// ���n�t���O�����낷
	m_isStand = false;
}

/* =====================================================================
//! ���@�e		�d�͕t��
//! ���@��		�������ۂ��ibool�j
//! �߂�l		�Ȃ�
===================================================================== */
void Player::Gravity(bool dive)
{
	// �����ɂ���ꍇ
	if (dive)
	{
		// �����ł̏d��
		if (m_spdY > SPEED_MAX_FALL_WATER)
		{
			m_spdY -= NUM_WATER_GRAVITY;
		}

		m_isDive = false;
	}
	else
	{
		// �ʏ�̏d��
		if (m_spdY > SPEED_MAX_FALL)
		{
			m_spdY -= NUM_GRAVITY;
		}
	}
}

/* =====================================================================
//! ���@�e		��������
//! ���@��		�}�b�v���iint�j�A�G�߁iint�j
//! �߂�l		�Ȃ�
===================================================================== */
void Player::Fall(int mapInfo, int season)
{
	if (mapInfo == static_cast<int>(TILE::WATER))
	{
		if (season == static_cast<int>(SEASON::WINTER))
		{
			// �X�̂Ƃ�
			m_spdY = 0.0f;
		}
		else
		{
			m_isJump = false;
			m_isDive = true;

			// �j���{�^���ɕς��
			PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeButtonTexture(ACTION::SWIM);
		}
	}
}

/* =====================================================================
//! ���@�e		�ړ�
//! ���@��		���x�ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void Player::Move(float speed)
{
	m_spdX = speed;
}

/* =====================================================================
//! ���@�e		�W�����v
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Player::Jump()
{
	if (m_isDive)
	{
		m_spdY = JUMP_WATER_PLAYER;
	}
	else
	{
		m_spdY = JUMP_PLAYER;
		m_isJump = true;
		m_isStand = false;
	}
}

/* =====================================================================
//! ���@�e		�^�C���ɑ΂��Ă̍s��
//! ���@��		�^�C��ID�iint�j�A�^�C�����W�iVec2�j�A�G�߁iint�j
//! �߂�l		�Ȃ�
===================================================================== */
void Player::Action(int tileID, Vec2 tileVec, int season)
{
	switch (tileID)
	{
	case static_cast<int>(TILE::BLOCK):		// �u���b�N

		if (m_spdY <= 0.0f)
		{
			// ����
			setPositionY(tileVec.y + SIZE_TILE + SIZE_PLAYER_HERF);
		
			m_spdY = 0.0f;
			m_isJump = false;
			m_isStand = true;
		}

		break;

	case static_cast<int>(TILE::WATER):		// ��

		// ��������
		Fall(static_cast<int>(TILE::WATER), season);

		break;
	}
}

/* =====================================================================
//! ���@�e		�㉺�̃X�s�[�h���擾
//! ���@��		�Ȃ�
//! �߂�l		�X�s�[�h�ifloat�j
===================================================================== */
void Player::SetSpdY(float spdY)
{
	m_spdY = spdY;
}

/* =====================================================================
//! ���@�e		�v���C���[�A�j���[�V����
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Player::AnimationPlayer()
{
	m_grpX += SIZE_PLAYER;
	if (m_grpX >= SIZE_PLAYER * 3)
	{
		m_grpX = 0;
	}
}