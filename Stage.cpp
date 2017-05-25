/* =====================================================================
//! @param		�uStage�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/04/01
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Stage.h"
#include "ClearScene.h"
#include "PlayScene.h"
#include "StageSelectScene.h"

// ���O���
USING_NS_CC;

// �ÓI�����o�̒�`
OperationButton* PlayScene::m_pButton[NUM_BUTTON];
int StageSelectScene::m_stageID;
bool Pollen::m_isPollenFlg;

// �����o�֐��̒�`

bool Stage::init()
{
	if (!Node::init())
	{
		return false;
	}

	// �X�V��������
	scheduleUpdate();

	// �����o�̏����ݒ�
	m_season = static_cast<int>(SEASON::SPRING);		// �G��
	m_seasonBefore = m_season;							// �G�߂̊m��
	m_isShowObject = false;								// �I�u�W�F�N�g���Q�Ƃ��Ă��邩�ǂ���
	m_isPause = false;									// �|�[�Y�����ǂ���
	Pollen::m_isPollenFlg = false;						// �ԕ��t���O�����낵�Ă���
	m_numTiles = 0;										// �^�C����
	m_numSignBoards = 0;								// �Ŕ�
	m_numGimmicks = 0;									// �M�~�b�N��

	//�e�X�e�[�W�̉��̐���
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(StageSelectScene::m_stageID + static_cast<int>(SOUND::BGM_FLOWER), false);

	// �w�i
	m_pBack = Background::create();
	this->addChild(m_pBack,-1);

	// �p�[�e�B�N��
	m_pParticle = Particle::create();
	this->addChild(m_pParticle);

	// �}�b�v�`��
	std::stringstream sTMXFileName;
	sTMXFileName << "mapData/map_" << STAGE_NAME[StageSelectScene::m_stageID] << ".tmx";
	m_pMap = TMXTiledMap::create(sTMXFileName.str());
	m_pMap->setAnchorPoint(Vec2(0, 0));
	m_pMap->setPosition(Vec2(0, 0));
	this->addChild(m_pMap);

	// �v���C���[
	m_pPlayer = Player::create();
	m_pPlayer->setPosition(Vec2(192.0f, 216.0f));
	this->addChild(m_pPlayer, 1);

	// �G�ߋL
	m_pSeasonBook = nullptr;

	// ���C���[���̏����ݒ�
	InitLayerInfo();


	/// �f�o�b�O�p
	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(Stage::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(Stage::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	keyLeft = false;	keyRight = false;

	return true;
}

/* =====================================================================
//! ���@�e		�X�V����
//! ���@��		�_�~�[�����ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::update(float delta)
{
	// �G�߂̕ύX
	if (m_season != m_seasonBefore)
	{
		// �p�[�e�B�N���̔j��
		if (m_pParticle != nullptr)
		{
			m_pParticle->removeFromParent();
			m_pParticle = nullptr;
		}

		// �G�߂�ς���
		ChangeSeason();
	}


	/// �f�o�b�O�p
	if (!m_isPause)
	{
		// �{�^����������Ă�����v���C���[���ړ�������
		if (!m_isShowObject)
		{
			if (keyLeft && !m_leftFlag)
			{
				// �v���C���[�̌�����ݒ�
				m_pPlayer->setFlippedX(true);

				// �v���C���[�̈ړ�
				if (m_pPlayer->getPositionX() > SIZE_PLAYER_HERF)
				{
					m_pPlayer->Move(-SPEED_MOVE_PLAYER);
				}
			}
			if (keyRight && !m_rightFlag)
			{
				// �v���C���[�̌�����ݒ�
				m_pPlayer->setFlippedX(false);

				// �v���C���[�̈ړ�
				if (m_pPlayer->getPositionX() < STAGE_WIDTH - SIZE_PLAYER_HERF)
				{
					m_pPlayer->Move(SPEED_MOVE_PLAYER);
				}
			}
		}
	}
}

/* =====================================================================
//! ���@�e		���C���[���̏����ݒ�
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::InitLayerInfo()
{
	// ���C���[�ݒ�
	for (int i = 0; i < NUM_SEASON; i++)
	{
		std::stringstream sFileName;
		sFileName << "tileLayer_" << SEASON_NAME[i];

		// �^�C�����C���[
		m_pMapTileLayer[i] = m_pMap->getLayer(sFileName.str());
		m_pMapTileLayer[i]->setVisible(false);

		sFileName.str("");
		sFileName.clear();

		sFileName << "gimmickLayer_" << SEASON_NAME[i];

		// �M�~�b�N���C���[
		m_pMapGimmickLayer[i] = m_pMap->getLayer(sFileName.str());
		m_pMapGimmickLayer[i]->setVisible(false);
	}

	// �������C���[��\��
	m_pMapTileLayer[m_season]->setVisible(true);
	m_pMapGimmickLayer[m_season]->setVisible(true);

	// ���C���[���̐ݒ�
	ReSetLayerInfo();
}

/* =====================================================================
//! ���@�e		�^�C�����̍Đݒ�
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::ReSetLayerInfo()
{
	// �^�C�����̏�����
	while (!m_tileInfo.empty())
	{
		m_tileInfo.pop_back();
	}

	// �M�~�b�N���̏�����
	while (!m_gimmickInfo.empty())
	{
		m_gimmickInfo.pop_back();
	}

	// �^�C�����̏�����
	m_numTiles = 0;
	m_numGimmicks = 0;

	// �^�C�����̐ݒ�
	SetLayerInfo();
}

/* =====================================================================
//! ���@�e		���C���[���̐ݒ�
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::SetLayerInfo()
{
	// �^�C�����̐ݒ�
	SetTileInfoWithLayer(m_pMapTileLayer[m_season], KIND_TILE::TILE);

	// �M�~�b�N���̐ݒ�
	SetTileInfoWithLayer(m_pMapGimmickLayer[m_season], KIND_TILE::GIMMICK);
}

/* =====================================================================
//! ���@�e		���C���[����^�C������ݒ�
//! ���@��		���C���[�iTMXLayer�j�A�^�C���̎�ށiKIND_TILE�j
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::SetTileInfoWithLayer(TMXLayer* layer, KIND_TILE tile)
{
	for (int i = 0; i < NUM_ROW; i++)
	{
		for (int j = 0; j < NUM_COLUMN; j++)
		{
			auto gid = layer->getTileGIDAt(Vec2(j, i));

			// �v���p�e�B�����擾
			Value propertyValue = m_pMap->getPropertiesForGID(gid);

			if (!propertyValue.isNull())
			{
				// �v���p�e�B���}�b�v�z��Ƃ��ĕێ�
				ValueMap propertyMap = propertyValue.asValueMap();

				if (!propertyMap.empty())
				{
					// �v���p�e�B����^�C������ݒ�
					SetTileInfoWithProperty(propertyMap, i, j, tile);
				}
			}
		}
	}
}

/* =====================================================================
//! ���@�e		�v���p�e�B����^�C������ݒ�
//! ���@��		GID�iuint32_t�j�A�s�iint�j�A��iint�j�A�^�C���̎�ށiKIND_TILE�j
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::SetTileInfoWithProperty(ValueMap map, int row, int col, KIND_TILE tile)
{		
	// ���W�ݒ�
	Vec2 pos = Vec2(col * SIZE_TILE, (NUM_ROW - row) * SIZE_TILE - SIZE_TILE);

	int id;

	// �^�C�����̓o�^
	switch (tile)
	{
	case KIND_TILE::TILE:		// �^�C��

		// �e�^�C���ݒ�
		if		(map["collision"].asString() == "block")	id = static_cast<int>(TILE::BLOCK);
		else if (map["collision"].asString() == "water")	id = static_cast<int>(TILE::WATER);
		else												id = static_cast<int>(TILE::NONE);

		// �^�C�������Z
		m_numTiles++;

		// �^�C��ID�̐ݒ�
		m_tileInfo.push_back(StageInfo{ id, pos });

		break;

	case KIND_TILE::GIMMICK:	// �M�~�b�N

		// �e�M�~�b�N�ݒ�
		if		(map["tree"].asString() == "block")			id = static_cast<int>(TILE::BLOCK);
		else if (map["tree"].asString() == "pollen")		id = static_cast<int>(TILE::POLLEN);
		else if (map["bug"].asString() == "block")			id = static_cast<int>(TILE::BLOCK);
		else												id = static_cast<int>(TILE::NONE);

		// �M�~�b�N�����Z
		m_numGimmicks++;

		// �M�~�b�NID�̐ݒ�
		m_gimmickInfo.push_back(StageInfo{ id, pos });

		break;
	}
}

/* =====================================================================
//! ���@�e		�G�߂̕ύX
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::ChangeSeason()
{
	// ���݂̋G�߂̃��C���[���\���ɂ���
	m_pMapTileLayer[m_seasonBefore]->setVisible(false);
	m_pMapGimmickLayer[m_seasonBefore]->setVisible(false);

	// �w�i��ς���
	m_pBack->Change(m_season);
	if (m_season != static_cast<int>(SEASON::SUMMER))
	{
		m_pParticle = Particle::create();
		this->addChild(m_pParticle, -1);
	}

	// ���C���[���̍Đݒ�
	ReSetLayerInfo();

	// ���C���[��\������
	m_pMapTileLayer[m_season]->setVisible(true);
	m_pMapGimmickLayer[m_season]->setVisible(true);

	// �G�߂̕ύX���m�肳����
	m_seasonBefore = m_season;
}

/* =====================================================================
//! ���@�e		�}�b�v�̃X�N���[��
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::Scroll()
{
	// �J�����ݒ�
	m_pCamera = getScene()->getDefaultCamera();

	float cameraPos = m_pCamera->getPositionX();

	// �J�����ړ��̊�l��ݒ�
	const float CAMERA_BORDER = WINDOW_WIDTH_HERF;

	// �͂ݏo���m�F
	if (m_pPlayer->getPositionX() >= CAMERA_BORDER && m_pPlayer->getPositionX() <= STAGE_WIDTH - CAMERA_BORDER)
	{
		// �p�[�e�B�N���ړ�
		if (m_pParticle != nullptr) m_pParticle->ParticleScroll(GetCameraPosX());

		// �ԕ��ړ�
		if (Pollen::m_isPollenFlg)
		{
			m_pPollen->setPositionX(GetCameraPosX());
		}

		// �{�^���ړ�
		PlayScene::m_pButton[static_cast<int>(BUTTON::LEFT)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 96.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::RIGHT)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 288.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->setPositionX(m_pPlayer->getPositionX() + WINDOW_WIDTH_HERF - 96.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::PAUSE)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 88.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::SEASON_BOOK)]->setPositionX(m_pPlayer->getPositionX() + WINDOW_WIDTH_HERF - 208.0f);

		// �J�����ݒ�
		cameraPos = m_pPlayer->getPositionX();
	}

	// �J�����ړ�
	m_pCamera->setPositionX(cameraPos);
}

/* =====================================================================
//! ���@�e		�����蔻��`�F�b�N
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::CheckCollision()
{
	m_leftFlag = false;
	m_rightFlag = false;

	GameManager& gm = GameManager::GetInstance();

	// �^�C���Ƃ̓����蔻��
	for (int i = 0; i < m_numTiles; i++)
	{
		// ���n����
		if (gm.CheckCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::DOWN)
		{
			// �^�C���ɉ������v���C���[�̏���
			m_pPlayer->Action(m_tileInfo[i].ID, m_tileInfo[i].pos, m_season);
			break;
		}

		// ���E�̏Փ˔���
		if (gm.CheckCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::RIGHT && !m_tileInfo[i].ID == static_cast<int>(TILE::WATER))
		{
			m_rightFlag = true;
		}
		if (gm.CheckCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::LEFT && !m_tileInfo[i].ID == static_cast<int>(TILE::WATER))
		{
			m_leftFlag = true;
		}
	}

	// �M�~�b�N�Ƃ̓����蔻��
	for (int i = 0; i < m_numGimmicks; i++)
	{
		if (gm.isCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()))
		{
			// ���̏ꍇ�ԕ����o��
			if (m_gimmickInfo[i].ID == static_cast<int>(TILE::POLLEN) && !Pollen::m_isPollenFlg)
			{
				m_pPollen = Pollen::create();
				m_pPollen->setPosition(Vec2(GetCameraPosX(), WINDOW_HEIGHT_HERF));
				this->addChild(m_pPollen, 5);
			}

			// �M�~�b�N�ɉ������v���C���[�̏���
			m_pPlayer->Action(m_gimmickInfo[i].ID, m_gimmickInfo[i].pos, m_season);
		}

		// ���E�̏Փ˔���
		if (m_gimmickInfo[i].ID == static_cast<int>(TILE::BLOCK))
		{
			if (gm.CheckCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::RIGHT)
			{
				m_rightFlag = true;
			}
			if (gm.CheckCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::LEFT)
			{
				m_leftFlag = true;
			}
		}
	}
}

/* =====================================================================
//! ���@�e		�{�^���������ꂽ���̏���
//! ���@��		�{�^���iBUTTON�j
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::CheckButtonHighlighted(BUTTON button)
{
	// �{�^����������Ă邩�ǂ���
	if (PlayScene::m_pButton[static_cast<int>(button)]->isHighlighted())
	{
		// ���{�^��
		if (button == BUTTON::LEFT)
		{
			// �v���C���[�̌�����ݒ�
			m_pPlayer->setFlippedX(true);

			// �v���C���[�̈ړ�
			if (m_pPlayer->getPositionX() > SIZE_PLAYER_HERF)
			{
				m_pPlayer->Move(-SPEED_MOVE_PLAYER);
			}
		}
		// �E�{�^��
		else if (button == BUTTON::RIGHT)
		{
			// �v���C���[�̌�����ݒ�
			m_pPlayer->setFlippedX(false);

			// �v���C���[�̈ړ�
			if (m_pPlayer->getPositionX() < STAGE_WIDTH - SIZE_PLAYER_HERF)
			{
				m_pPlayer->Move(SPEED_MOVE_PLAYER);
			}
		}
		// �A�N�V�����{�^��
		else if (button == BUTTON::ACTION)
		{
			// �W�����v���ĂȂ��Ƃ��ɏ���
			if (!Player::m_isJump)
			{
				ActionButtonHighlighted(PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg());
			}
		}
		// �G�ߋL�{�^��
		else if (button == BUTTON::SEASON_BOOK)
		{
			if (!m_isShowObject)
			{
				// �G�ߋL�̐���
				m_pSeasonBook = SeasonBook::create();
				m_pSeasonBook->setPosition(Vec2(GetCameraPosX(), WINDOW_HEIGHT_HERF));
				this->addChild(m_pSeasonBook, 4);

				// ���x���Â�����
				PlayScene::m_pButton[static_cast<int>(BUTTON::SEASON_BOOK)]->SetFullBright(false);

				// �G�ߋL�����Ă����Ԃɂ���
				m_isShowObject = true;
			}
		}
	}
}

/* =====================================================================
//! ���@�e		�A�N�V�����{�^���������ꂽ���̏���
//! ���@��		�A�N�V�����iACTION�j
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::ActionButtonHighlighted(ACTION action)
{
	GameManager& gm = GameManager::GetInstance();

	switch (action)
	{
	case ACTION::JUMP:				// �W�����v�{�^��
	case ACTION::SWIM:				// �j���{�^��

		m_pPlayer->Jump();
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright(false);
		break;
	}
}

/* =====================================================================
//! ���@�e		�L�[�f�o�b�O
//! ���@��		���낢��
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!Stage::m_isPause)
	{
		// �{�^����������Ă�����v���C���[���ړ�������
		if (!Stage::m_isShowObject)
		{
			if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && !m_leftFlag)
			{
				keyLeft = true;
			}
			if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && !m_rightFlag)
			{
				keyRight = true;
			}
		}
	}
}

/* =====================================================================
//! ���@�e		�L�[�f�o�b�O
//! ���@��		���낢��
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		keyLeft = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		keyRight = false;
	}
}