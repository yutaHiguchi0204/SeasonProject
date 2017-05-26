/* =====================================================================
//! @param		�萔���܂Ƃ߂��w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/05/22
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "cocos2d.h"

/* �����̃N���X�Ŏg�p����萔�������Œ�`���Ă�������
// �N���X���݂̂̏ꍇ�̓N���X�̃w�b�_�[���Œ�`���Ă�������
*/

// ���C���֌W
const float				WINDOW_WIDTH				= 960.0f;													// ��ʂ̕�
const float				WINDOW_HEIGHT				= 540.0f;													// ��ʂ̍���
const float				WINDOW_WIDTH_HERF			= WINDOW_WIDTH / 2;											// ��ʂ̕��̔���
const float				WINDOW_HEIGHT_HERF			= WINDOW_HEIGHT / 2;										// ��ʂ̍����̔���
const cocos2d::Vec2		WINDOW_MIDDLE				= cocos2d::Vec2(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF);		// ��ʂ̒��S
const int				NUM_SECOND					= 60;														// �P�b
const int				SPEED_ANIMATION				= 10;														// �A�j���[�V�����X�s�[�h�i�R�}�Ԋu�j

// �X�e�[�W�֌W
const int				NUM_ROW						= 17;														// �s��
const int				NUM_COLUMN					= 120;														// ��
const int				NUM_STAGE					= 4;														// �X�e�[�W��
const int				NUM_SEASON					= 4;														// �G�ߐ�
const int				NUM_BUTTON					= 5;														// �{�^����
const int				NUM_ITEM					= 100;														// �A�C�e����
const int				NUM_STAGE_ITEM				= 25;														// �X�e�[�W�̃A�C�e����
const float				STAGE_WIDTH					= WINDOW_WIDTH * 4;											// �X�e�[�W�T�C�Y
const float				STAGE_WIDTH_HERF			= STAGE_WIDTH / 2;											// �X�e�[�W�T�C�Y�̔���
const cocos2d::Vec2		STAGE_MIDDLE				= cocos2d::Vec2(STAGE_WIDTH_HERF, WINDOW_HEIGHT_HERF);		// �X�e�[�W�̒��S
const float				SIZE_TILE					= 32.0f;													// �^�C���T�C�Y(32�~32)
const float				SIZE_COLLIDER				= 10.0f;														// �����蔻�蒲���p
const float				NUM_GRAVITY					= 0.4f;														// �d��
const float				NUM_WATER_GRAVITY			= 0.05f;													// ���́i���̏d�́j

// �v���C���[�֌W
const float				SIZE_PLAYER					= 48.0f;													// �v���C���[�T�C�Y(48�~48)
const float				SIZE_PLAYER_HERF			= SIZE_PLAYER / 2;											// �v���C���[�̔����̃T�C�Y
const float				SIZE_PLAYER_COLLISION		= 32.0f;													// �v���C���[�̓����蔻��
const float				SIZE_PLAYER_COLLISION_HERF	= SIZE_PLAYER_COLLISION / 2;								// �v���C���[�̓����蔻��̔���
const float				SPEED_MOVE_PLAYER			= 4.0f;														// �ړ����x
const float				JUMP_PLAYER					= 10.0f;													// �W�����v�̍���

// �����萔
const std::string STAGE_NAME[NUM_STAGE] = {				// �X�e�[�W��
	"flower",
	"bird",
	"wind",
	"moon"
};

const std::string SEASON_NAME[NUM_SEASON] = {			// �G�ߖ�
	"spring",
	"summer",
	"autumn",
	"winter"
};

// �񋓌^
enum class STAGE			// �X�e�[�W
{
	FLOWER,
	BIRD,
	WIND,
	MOON
};

enum class SEASON			// �G��
{
	SPRING,
	SUMMER,
	AUTUMN,
	WINTER
};

enum class TILE				// �^�C��
{
	NONE = -1,
	BLOCK,
	WATER,
	POLLEN,
	ITEM
};

enum class COLLISION
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};