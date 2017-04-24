/* =====================================================================
//! @param		�uGameManager�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/03/04
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "cocos2d.h"

// �萔
const int				NUM_ROW					= 17;														// �s��
const int				NUM_COLUMN				= 120;														// ��
const int				NUM_BUTTON				= 3;														// �{�^����
const int				NUM_SEASON				= 4;														// �G��
const int				NUM_SECOND				= 60;														// �P�b
const float				WINDOW_WIDTH			= 960.0f;													// ��ʂ̕�
const float				WINDOW_HEIGHT			= 540.0f;													// ��ʂ̍���
const float				WINDOW_WIDTH_HERF		= WINDOW_WIDTH / 2;											// ��ʂ̕��̔���
const float				WINDOW_HEIGHT_HERF		= WINDOW_HEIGHT / 2;										// ��ʂ̍����̔���
const float				STAGE_WIDTH				= WINDOW_WIDTH * 4;											// �X�e�[�W�T�C�Y
const float				SIZE_TILE				= 32.0f;													// �^�C���T�C�Y(32�~32)
const float				SIZE_PLAYER				= 48.0f;													// �v���C���[�T�C�Y(48�~48)
const float				NUM_GRAVITY				= 0.4f;														// �d��
const float				NUM_WATER_GRAVITY		= 0.05f;													// ���́i���̏d�́j
const cocos2d::Vec2		WINDOW_MIDDLE			= cocos2d::Vec2(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF);		// ��ʂ̒��S

const std::string SEASON_NAME[NUM_SEASON] = {			// �G�ߖ�
	"spring",
	"summer",
	"autumn",
	"winter"
};

// �񋓌^
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
	SIGN_BOARD,
	SEASON_BOOK
};

// ���ʊ֐����܂Ƃ߂��N���X
class GameManager
{
public:

	static bool isCollision(cocos2d::Vec2 tileVec, cocos2d::Vec2 playerVec);		// ���n����
};