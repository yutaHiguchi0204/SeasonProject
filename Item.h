/* =====================================================================
//! @param		uItemvNXΜwb_t@C
//! @create		σϋ@TΎ
//! @date		17/05/26
===================================================================== */
#pragma once

// wb_t@CΜCN[h
#include "GameManager.h"

// Xe[WAGί²ΖΜACe
const int NUM_PLACE = NUM_SEASON * NUM_STAGE;
const int NUM_ITEM_PLACE[NUM_PLACE] = {
	6,		// ΤΜt
	6,		// ΤΜΔ
	6,		// ΤΜH
	7,		// ΤΜ~
	7,		// ΉΜt
	6,		// ΉΜΔ
	5,		// ΉΜH
	7,		// ΉΜ~
	5,		// Μt
	6,		// ΜΔ
	6,		// ΜH
	8,		// Μ~
	7,		// Μt
	7,		// ΜΔ
	7,		// ΜH
	4,		// Μ~
};

// NXΜθ`
class Item : public cocos2d::Sprite
{
public:
	CREATE_FUNC(Item);
	virtual bool init();
};