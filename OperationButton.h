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
const int NUM_ACTION = 2;						// �A�N�V������
const std::string ACTION_NAME[NUM_ACTION] =		// �A�N�V������
{
	"jump",
	"swim",
};

// �񋓌^
enum class BUTTON			// �{�^��
{
	LEFT,
	RIGHT,
	ACTION,
	PAUSE,
	SEASON_BOOK
};

enum class ACTION			// �A�N�V����
{
	JUMP,
	SWIM
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

	void SetFullBright(bool full = true);								// �{�^���̖��x�ݒ�i�l�`�w���������j

	void ChangeActionFlg(ACTION action);								// �A�N�V�����t���O�̕ύX
	void ChangeButtonTexture(ACTION action);							// �{�^���̉摜��ς���

	inline const ACTION GetActionFlg() { return m_actionFlg; };			// �A�N�V�����t���O���擾����
};