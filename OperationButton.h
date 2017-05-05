/* =====================================================================
//! @param		�uOperationButton�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/04/20
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <string>
#include "GameManager.h"
#include "ui/CocosGUI.h"

// �萔
const int NUM_ACTION = 3;						// �A�N�V������
const std::string ACTION_NAME[NUM_ACTION] =		// �A�N�V������
{
	"jump",
	"book",
	"signBoard"
};

// �񋓌^
enum class BUTTON			// �{�^��
{
	LEFT,
	RIGHT,
	ACTION,
	PAUSE
};

enum class ACTION			// �A�N�V����
{
	JUMP,
	SEASON_BOOK,
	SIGN_BOARD
};

// �N���X�̒�`
class OperationButton : public cocos2d::ui::Button
{
private:
	ACTION m_actionFlg;							// �A�N�V�����t���O�i�A�N�V�����{�^���̂Ƃ��̂ݕύX�L�j

public:
	CREATE_FUNC(OperationButton);
	virtual bool init();
	bool init(BUTTON button);

	static OperationButton* create(BUTTON button);

	void SetFullBright(bool full = true);				// �{�^���̖��x�ݒ�i�l�`�w���������j

	void ChangeActionFlg(ACTION action);				// �A�N�V�����t���O�̕ύX
	void ChangeButtonTexture(ACTION action);			// �{�^���̉摜��ς���

	ACTION GetActionFlg();								// �A�N�V�����t���O���擾����
};