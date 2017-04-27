/* =====================================================================
//! @param		�uSignBoard�v�N���X�̃w�b�_�t�@�C��
//! @create		�؉��@�_��
//! @date		17/04/27
===================================================================== */

#pragma once
#include "cocos2d.h"

class SignBoard:public cocos2d::Sprite
{
	private:
		//�Ŕ�
		cocos2d::Sprite* m_blackBoard;
		//�I�u�W�F�N�g�ԍ�
		int m_objNumber;

	public:

		CREATE_FUNC(SignBoard);
		virtual bool init();

		//static SignBoard* create();

		//�I�u�W�F�N�g�ԍ��̎擾
		int GetObjectNumber();
		//�I�u�W�F�N�g�ԍ��̒ǉ�
		void SignBoard::SetObjectNumber(int SetObj);
		//�Ŕ̉摜��ǉ�����
		void SetBlackBoardTexture(int num);

		void EnabledBlackBoard(bool TorF);

};
