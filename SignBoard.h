/* =====================================================================
//! @param		「SignBoard」クラスのヘッダファイル
//! @create		木下　浩暉
//! @date		17/04/27
===================================================================== */
#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class SignBoard : public cocos2d::Sprite
{
	private:
		//看板
		cocos2d::Sprite* m_blackBoard;
		//閉じるボタン
		cocos2d::ui::Button* m_pButtonClose;
		//オブジェクト番号
		int m_objNumber;

	public:

		CREATE_FUNC(SignBoard);
		virtual bool init();

		//オブジェクト番号の取得
		int GetObjectNumber();
		//オブジェクト番号の追加
		void SetObjectNumber(int SetObj);

		//看板の画像を追加する
		void SetBlackBoardTexture(int num);

		void DrawBlackBoard(int objNum);
		void EnabledBlackBoard(bool TorF);
};
