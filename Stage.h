/* =====================================================================
//! @param		�uStage�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/04/01
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <vector>
#include "Background.h"
#include "GameManager.h"
#include "Player.h"
#include "ui/CocosGUI.h"

// �\����
struct TileInfo
{
	int ID;					// �^�C��ID
	cocos2d::Vec2 pos;		// ��`���W
};

// �N���X�̒�`
class Stage : public cocos2d::Node
{
private:
	int m_season;										// �G��

	Background* m_pBack;								// �w�i

	cocos2d::TMXTiledMap* m_pMap;						// �}�b�v
	cocos2d::TMXLayer* m_pMapTileLayer[NUM_SEASON];		// �}�b�v���C���[�i�^�C���j
	cocos2d::TMXLayer* m_pMapGimmickLayer[NUM_SEASON];	// �}�b�v���C���[�i�M�~�b�N�j
	cocos2d::TMXLayer* m_pMapObjectLayer;				// �}�b�v���C���[�i�I�u�W�F�N�g�j

public:

	CREATE_FUNC(Stage);
	virtual bool init();

	void ReSetLayerInfo();											// �^�C�����̏�����
	void SetLayerInfo();											// ���C���[���̐ݒ�
	void SetTileInfoWithProperty(uint32_t gid, int row, int col);	// �v���p�e�B����^�C������ݒ�

	void ChangeSeason();											// �G�߂̕ύX

	void Scroll(float playerX, cocos2d::ui::Button* button[]);		// �}�b�v�̃X�N���[��

	void CheckCollision(Player* player);							// �����蔻��`�F�b�N

	// �^�b�`����
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	// �ÓI�����o
	static std::vector<TileInfo> m_tileInfo;						// �^�C�����
	static int m_numTiles;											// ���^�C����
};