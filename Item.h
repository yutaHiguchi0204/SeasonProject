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
	0,		// ΉΜt
	0,		// ΉΜΔ
	0,		// ΉΜH
	0,		// ΉΜ~
	0,		// Μt
	0,		// ΜΔ
	0,		// ΜH
	0,		// Μ~
	0,		// Μt
	0,		// ΜΔ
	0,		// ΜH
	0,		// Μ~
};

// NXΜθ`
class Item : public cocos2d::Sprite
{
public:
	CREATE_FUNC(Item);
	virtual bool init();
};