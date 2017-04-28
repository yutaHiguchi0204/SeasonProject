/* =====================================================================
//! @param		�uSignBoard�v�N���X�̃\�[�X�t�@�C��
//! @create		�؉��@�_��
//! @date		17/04/27
===================================================================== */

#include "SignBoard.h"

USING_NS_CC;

//�I�u�W�F�N�g�ԍ��̎擾
int SignBoard::GetObjectNumber()
{
	return m_objNumber;
}

//�I�u�W�F�N�g�ԍ��̒ǉ�(int)
void SignBoard::SetObjectNumber(int SetObj)
{
	//�擾�����ԍ���ǉ�����
	m_objNumber = SetObj;
}

/* =====================================================================
//! ���@�e		�I�u�W�F�N�g���̓Y���ƈ�v���Ă�������Ղ�\��
//! ���@��		�I�u�W�F�N�g���h�c�iint�j
//! �߂�l		�Ȃ�
===================================================================== */
void SignBoard::DrawBlackBoard(int objNum)
{
	if (GetObjectNumber() == objNum)
	{
		EnabledBlackBoard(true);
	}
}

//���̕\����\��(bool)
void SignBoard::EnabledBlackBoard(bool TorF)
{
	m_blackBoard->setVisible(TorF);
}

//���̉摜��ǉ�����(int)
void SignBoard::SetBlackBoardTexture(int num)
{
	std::stringstream sFileName;
	sFileName << "object/blackBoard_" << num + 1 << ".png";

	//�Ŕ̃t�@�C����ǉ�
	m_blackBoard->setTexture(sFileName.str());
}

bool SignBoard::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// �����Ղ̐���
	m_blackBoard = Sprite::create();
	m_blackBoard->setVisible(false);
	this->addChild(m_blackBoard);

	return true;
}

