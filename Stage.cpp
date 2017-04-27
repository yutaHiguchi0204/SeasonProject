/* =====================================================================
//! @param		�uStage�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/04/01
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Stage.h"
#include "PlayScene.h"

// ���O���
USING_NS_CC;

// �ÓI�����o�̒�`
OperationButton* PlayScene::m_pButton[NUM_BUTTON];

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
	m_isChangeSeason = false;							// �G�߂����ւ��Ă邩�ǂ���
	m_numTiles = 0;
	m_numObjects = 0;
	m_numGimmicks = 0;

	// �w�i
	m_pBack = Background::create();
	this->addChild(m_pBack);

	// �}�b�v�`��
	m_pMap = TMXTiledMap::create("mapData/mapFlower.tmx");
	m_pMap->setAnchorPoint(Vec2(0, 0));
	m_pMap->setPosition(Vec2(0, 0));
	this->addChild(m_pMap);

	//���P�̕`��
	blackboard1 = Sprite::create("object\\blackboard1.png");
	blackboard1->setPosition(Vec2(500.0f, 400.0f));
	blackboard1->setVisible(false);
	this->addChild(blackboard1);

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

	// �I�u�W�F�N�g���C���[
	m_pMapObjectLayer = m_pMap->getLayer("objectLayer");

	// ���C���[���̐ݒ�
	SetLayerInfo();

	// �v���C���[
	m_pPlayer = Player::create();
	m_pPlayer->setPosition(Vec2(64.0f, 216.0f));
	this->addChild(m_pPlayer, 1);

	// �G�ߋL
	m_pSeasonBook = nullptr;

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
		ChangeSeason();
	}
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

	// �I�u�W�F�N�g���̏�����
	while (!m_objectInfo.empty())
	{
		m_objectInfo.pop_back();
	}

	// �M�~�b�N���̏�����
	while (!m_gimmickInfo.empty())
	{
		m_gimmickInfo.pop_back();
	}

	// �^�C�����̏�����
	m_numTiles = 0;
	m_numObjects = 0;
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

	// �I�u�W�F�N�g���̐ݒ�
	SetTileInfoWithLayer(m_pMapObjectLayer, KIND_TILE::OBJECT);

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

	case KIND_TILE::OBJECT:		// �I�u�W�F�N�g

		// �e�I�u�W�F�N�g�ݒ�
		if		(map["object"].asString() == "signBoard")	id = static_cast<int>(TILE::SIGN_BOARD);
		else if	(map["object"].asString() == "seasonBook")	id = static_cast<int>(TILE::SEASON_BOOK);
		else												id = static_cast<int>(TILE::NONE);

		// �I�u�W�F�N�g�����Z
		m_numObjects++;

		// �I�u�W�F�N�gID�̐ݒ�
		m_objectInfo.push_back(StageInfo{ id, pos });

		break;

	case KIND_TILE::GIMMICK:	// �M�~�b�N

		// �e�M�~�b�N�ݒ�
		if		(map["tree"].asString() == "block")			id = static_cast<int>(TILE::BLOCK);
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
		// �w�i�ړ�
		m_pBack->setPositionX(m_pPlayer->getPositionX());

		// �{�^���ړ�
		PlayScene::m_pButton[static_cast<int>(BUTTON::LEFT)]->setPositionX(m_pPlayer->getPositionX() - 384.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::RIGHT)]->setPositionX(m_pPlayer->getPositionX() - 192.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->setPositionX(m_pPlayer->getPositionX() + 384.0f);

		// �J�����ݒ�
		cameraPos = m_pPlayer->getPositionX();
	}

	// �J�����ړ�
	m_pCamera->setPositionX(cameraPos);
}

/* =====================================================================
//! ���@�e		�J�������Wx�̎擾
//! ���@��		�Ȃ�
//! �߂�l		�J�������Wx�ifloat�j
===================================================================== */
float Stage::GetCameraPosX()
{
	return m_pCamera->getPositionX();
}

/* =====================================================================
//! ���@�e		�����蔻��`�F�b�N
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::CheckCollision()
{
	// �^�C���Ƃ̓����蔻��
	for (int i = 0; i < m_numTiles; i++)
	{
		if (GameManager::isCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()))
		{
			// �^�C���ɉ����ď���
			m_pPlayer->Action(m_tileInfo[i].ID, m_tileInfo[i].pos, m_season);
		}
	}

	// �����Ղ��\���ɂ���
	blackboard1->setVisible(false);

	// �I�u�W�F�N�g�Ƃ̓����蔻��
	for (int i = 0; i < m_numObjects; i++)
	{

		//�I�u�W�F�N�g�ƃv���C���[�����������ꍇ
		if (GameManager::isCollision(m_objectInfo[i].pos, m_pPlayer->getPosition()))

		{
			// �G�ߋL�Ɠ��������ꍇ
			if (m_objectInfo[i].ID == static_cast<int>(TILE::SEASON_BOOK))
			{
				PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::SEASON_BOOK);
			}
			
			//�ŔƓ��������ꍇ
			if(m_objectInfo[i].ID == static_cast<int>(TILE::SIGN_BOARD))
			{
				//�摜��\������
				blackboard1->setVisible(true);
			}
			
			// �I�u�W�F�N�g�ɉ����ď���
			m_pPlayer->Action(m_objectInfo[i].ID, m_objectInfo[i].pos, m_season);
		}

	}

	// �M�~�b�N�Ƃ̓����蔻��
	for (int i = 0; i < m_numGimmicks; i++)
	{
		if (GameManager::isCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()))
		{
			// �M�~�b�N�ɉ����ď���
			m_pPlayer->Action(m_gimmickInfo[i].ID, m_gimmickInfo[i].pos, m_season);
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
		else
		{
			// �W�����v���ĂȂ��Ƃ��ɏ���
			if (!Player::m_isJump)
			{
				// �W�����v����
				if (PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::JUMP)
				{
					m_pPlayer->Jump();
					PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright(false);
				}
				// �G�ߋL����
				else
				{
					// �G�ߋL�̐���
					m_pSeasonBook = SeasonBook::create();
					m_pSeasonBook->setPosition(Vec2(GetCameraPosX(), WINDOW_HEIGHT_HERF));
					this->addChild(m_pSeasonBook, 4);

					// ���x���Â�����
					PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright(false);

					// �G�ߕω������Ă����Ԃɂ���
					m_isChangeSeason = true;
				}
			}
		}
	}
}