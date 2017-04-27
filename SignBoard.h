/* =====================================================================
//! @param		「SignBoard」クラスのヘッダファイル
//! @create		木下　浩暉
//! @date		17/04/27
===================================================================== */

#pragma once
#include "cocos2d.h"

class SignBoard:public cocos2d::Sprite
{
	private:
		//看板
		cocos2d::Sprite* m_blackBoard;
		//オブジェクト番号
		int m_objNumber;

	public:

		CREATE_FUNC(SignBoard);
		virtual bool init();

		//static SignBoard* create();

		//オブジェクト番号の取得
		int GetObjectNumber();
		//オブジェクト番号の追加
		void SignBoard::SetObjectNumber(int SetObj);
		//看板の画像を追加する
		void SetBlackBoardTexture(int num);

		void EnabledBlackBoard(bool TorF);

};
