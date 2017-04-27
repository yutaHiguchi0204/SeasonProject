/* =====================================================================
//! @param		�uSignBoard�v�N���X�̃\�[�X�t�@�C��
//! @create		�؉��@�_��
//! @date		17/04/27
===================================================================== */

#include "SignBoard.h"

USING_NS_CC;

//�N���G�C�g

//SignBoard* SignBoard::create()
//{
//	SignBoard *pRet = new(std::nothrow) SignBoard();  
//		if (pRet && pRet->init())  
//		{  
//			pRet->autorelease();  
//			return pRet;  
//		}  
//		else  
//		{  
//			delete pRet;  
//			pRet = nullptr;  
//			return nullptr;  
//		}  
//}

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

	return true;
}

