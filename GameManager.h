/* =====================================================================
//! @param		�uGameManager�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/03/04
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "cocos2d.h"

// �萔
const int WINDOW_WIDTH			= 960;					// ��ʂ̕�
const int WINDOW_HEIGHT			= 540;					// ��ʂ̍���
const int STAGE_WIDTH			= WINDOW_WIDTH * 4;		// �X�e�[�W�T�C�Y
const int SIZE_TILE				= 32;					// �^�C���T�C�Y(32�~32)
const int SIZE_PLAYER			= 48;					// �v���C���[�T�C�Y(48�~48)
const int NUM_ROW				= 17;					// �s��
const int NUM_COLUMN			= 120;					// ��
const int NUM_BUTTON			= 3;					// �{�^����
const int NUM_SEASON			= 4;					// �G��
const int NUM_SECOND			= 60;					// �P�b
const float NUM_GRAVITY			= 0.4f;					// �d��
const float NUM_WATER_GRAVITY	= 0.05f;				// ���́i���̏d�́j

const std::string SEASON_NAME[NUM_SEASON] = {			// �G�ߖ�
	"spring",
	"summer",
	"autumn",
	"winter"
};

// �񋓌^
enum class BUTTON			// �{�^��
{
	LEFT,
	RIGHT,
	ACTION
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
	SIGN_BOARD
};

enum class OBJECT			// �I�u�W�F�N�g
{
	SIGN_BOARD,
	SEASON_BOOK
};

// ���ʊ֐����܂Ƃ߂��N���X
class GameManager
{
public:

	static bool isCollision(cocos2d::Vec2 tileVec, cocos2d::Vec2 playerVec);		// ���n����
};