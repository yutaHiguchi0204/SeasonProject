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
#include "OperationButton.h"
#include "Player.h"

// �񋓌^
enum class KIND_TILE
{
	TILE,
	OBJECT,
	GIMMICK
};

// �\����
struct StageInfo
{
	int ID;					// �^�C��ID
	cocos2d::Vec2 pos;		// ��`���W
};

// �N���X�̒�`
class Stage : public cocos2d::Node
{
private:
	int m_season;										// �G��
	int m_numTiles;										// ���^�C����
	int m_numObjects;									// ���I�u�W�F�N�g��
	int m_numGimmicks;									// ���M�~�b�N��

	Background* m_pBack;								// �w�i

	cocos2d::TMXTiledMap* m_pMap;						// �}�b�v
	cocos2d::TMXLayer* m_pMapTileLayer[NUM_SEASON];		// �}�b�v���C���[�i�^�C���j
	cocos2d::TMXLayer* m_pMapGimmickLayer[NUM_SEASON];	// �}�b�v���C���[�i�M�~�b�N�j
	cocos2d::TMXLayer* m_pMapObjectLayer;				// �}�b�v���C���[�i�I�u�W�F�N�g�j

	std::vector<StageInfo> m_tileInfo;					// �^�C�����
	std::vector<StageInfo> m_objectInfo;				// �^�C�����
	std::vector<StageInfo> m_gimmickInfo;				// �^�C�����

	cocos2d::Camera* m_pCamera;							// �J����

public:

	CREATE_FUNC(Stage);
	virtual bool init();

	void ReSetLayerInfo();																		// �^�C�����̏�����
	void SetLayerInfo();																		// ���C���[���̐ݒ�
	void SetTileInfoWithLayer(cocos2d::TMXLayer* layer, KIND_TILE tile);						// ���C���[����^�C������ݒ�
	void SetTileInfoWithProperty(cocos2d::ValueMap map, int row, int col, KIND_TILE tile);		// �v���p�e�B����^�C������ݒ�

	void ChangeSeason();																		// �G�߂̕ύX

	void Scroll(float playerX, OperationButton* button[]);										// �}�b�v�̃X�N���[��
	float GetCameraPosX();																		// �J�������Wx�̎擾

	void CheckCollision(Player* player);														// �����蔻��`�F�b�N
	void MoveButtonHighlighted(BUTTON button, Player* player);									// �ړ��{�^���������ꂽ���̏���

	// �^�b�`����
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};