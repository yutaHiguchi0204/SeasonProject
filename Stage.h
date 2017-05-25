/* =====================================================================
//! @param		�uStage�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/04/01
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <vector>
#include "Background.h"
#include "Particle.h"
#include "GameManager.h"
#include "OperationButton.h"
#include "Pause.h"
#include "Player.h"
#include "Pollen.h"
#include "SeasonBook.h"

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
	int m_seasonBefore;									// �ύX�O�̋G��
	int m_numTiles;										// ���^�C����
	int m_numSignBoards;								// ���Ŕ�
	int m_numGimmicks;									// ���M�~�b�N��

	Background* m_pBack;								// �w�i
	Particle* m_pParticle;								// �p�[�e�B�N��
	Player* m_pPlayer;									// �v���C���[
	SeasonBook* m_pSeasonBook;							// �G�ߋL
	Pollen* m_pPollen;									// �ԕ�

	cocos2d::TMXTiledMap* m_pMap;						// �}�b�v
	cocos2d::TMXLayer* m_pMapTileLayer[NUM_SEASON];		// �}�b�v���C���[�i�^�C���j
	cocos2d::TMXLayer* m_pMapGimmickLayer[NUM_SEASON];	// �}�b�v���C���[�i�M�~�b�N�j

	std::vector<StageInfo> m_tileInfo;					// �^�C�����
	std::vector<StageInfo> m_gimmickInfo;				// �M�~�b�N���

	cocos2d::Camera* m_pCamera;							// �J����

public:

	CREATE_FUNC(Stage);
	virtual bool init();

	void update(float delta);

	void InitLayerInfo();																		// ���C���[���̏����ݒ�
	void ReSetLayerInfo();																		// �^�C�����̏�����
	void SetLayerInfo();																		// ���C���[���̐ݒ�
	void SetTileInfoWithLayer(cocos2d::TMXLayer* layer, KIND_TILE tile);						// ���C���[����^�C������ݒ�
	void SetTileInfoWithProperty(cocos2d::ValueMap map, int row, int col, KIND_TILE tile);		// �v���p�e�B����^�C������ݒ�

	void ChangeSeason();																		// �G�߂̕ύX

	void Scroll();																				// �}�b�v�̃X�N���[��
	inline const float GetCameraPosX() { return m_pCamera->getPositionX(); };					// �J�������Wx�̎擾

	void CheckCollision();																		// �����蔻��`�F�b�N

	void CheckButtonHighlighted(BUTTON button);													// �{�^���������ꂽ���̏���
	void ActionButtonHighlighted(ACTION action);												// �A�N�V�����{�^���������ꂽ���̏���

	// �ÓI�����o
	static int m_season;																		// �G��
	static bool m_isShowObject;																	// �Ŕ�G�ߋL�ȂǃI�u�W�F�N�g���Q�Ƃ��Ă����Ԃ��ǂ���
	static bool m_leftFlag;																		// �Փ˔���p�t���O�i���j
	static bool m_rightFlag;																	// �Փ˔���p�t���O�i�E�j
	static bool m_isPause;																		// �|�[�Y�����ǂ���


	/// �f�o�b�O�p
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	cocos2d::EventListenerKeyboard* keyListener;
	bool keyLeft, keyRight;
};