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

	// �����o�̏����ݒ�
	m_season = static_cast<int>(SEASON::SPRING);		// �G��
	m_numTiles = 0;

	// �w�i
	m_pBack = Background::create();
	this->addChild(m_pBack);

	// �}�b�v�`��
	m_pMap = TMXTiledMap::create("mapData/mapFlower.tmx");
	m_pMap->setAnchorPoint(Vec2(0, 0));
	m_pMap->setPosition(Vec2(0, 0));
	this->addChild(m_pMap);

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

	// �C�x���g���X�i�[�쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	// �C�x���g���X�i�[�Ɋe�R�[���o�b�N�֐����Z�b�g����
	listener->onTouchBegan = CC_CALLBACK_2(Stage::onTouchBegan, this);

	// �C�x���g���X�i�[�o�^
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
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
	m_pMapTileLayer[m_season]->setVisible(false);
	m_pMapGimmickLayer[m_season]->setVisible(false);

	// �G�߂�ς���
	m_season++;
	if (m_season >= NUM_SEASON) m_season = static_cast<int>(SEASON::SPRING);

	// �w�i��ς���
	m_pBack->Change(m_season);

	// ���C���[���̍Đݒ�
	//ReSetLayerInfo();

	// ���C���[��\������
	m_pMapTileLayer[m_season]->setVisible(true);
	m_pMapGimmickLayer[m_season]->setVisible(true);
}

/* =====================================================================
//! ���@�e		�}�b�v�̃X�N���[��
//! ���@��		�v���C���[��x���W�ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::Scroll(float playerX, OperationButton* button[])
{
	// �J�����ݒ�
	m_pCamera = getScene()->getDefaultCamera();

	float cameraPos = m_pCamera->getPositionX();

	// �J�����ړ��̊�l��ݒ�
	const float CAMERA_BORDER = WINDOW_WIDTH_HERF;

	// �͂ݏo���m�F
	if (playerX >= CAMERA_BORDER && playerX <= STAGE_WIDTH - CAMERA_BORDER)
	{
		// �w�i�ړ�
		m_pBack->setPositionX(playerX);

		// �{�^���ړ�
		button[static_cast<int>(BUTTON::LEFT)]->setPositionX(playerX - 384.0f);
		button[static_cast<int>(BUTTON::RIGHT)]->setPositionX(playerX - 192.0f);
		button[static_cast<int>(BUTTON::ACTION)]->setPositionX(playerX + 384.0f);

		// �J�����ݒ�
		cameraPos = playerX;
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
//! ���@��		�v���C���[�iPlayer*�j
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::CheckCollision(Player* player)
{
	// �^�C���Ƃ̓����蔻��
	for (int i = 0; i < m_numTiles; i++)
	{
		if (GameManager::isCollision(m_tileInfo[i].pos, player->getPosition()))
		{
			// �^�C���ɉ����ď���
			player->Action(m_tileInfo[i].ID, m_tileInfo[i].pos, m_season);
		}
	}

	// �I�u�W�F�N�g�Ƃ̓����蔻��
	for (int i = 0; i < m_numObjects; i++)
	{
		if (GameManager::isCollision(m_objectInfo[i].pos, player->getPosition()))
		{
			// �G�ߋL�Ɠ��������ꍇ
			if (m_objectInfo[i].ID == static_cast<int>(TILE::SEASON_BOOK))
			{
				PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::SEASON_BOOK);
			}

			// �I�u�W�F�N�g�ɉ����ď���
			player->Action(m_objectInfo[i].ID, m_objectInfo[i].pos, m_season);
		}
	}

	// �M�~�b�N�Ƃ̓����蔻��
	for (int i = 0; i < m_numGimmicks; i++)
	{
		if (GameManager::isCollision(m_gimmickInfo[i].pos, player->getPosition()))
		{
			// �M�~�b�N�ɉ����ď���
			player->Action(m_gimmickInfo[i].ID, m_gimmickInfo[i].pos, m_season);
		}
	}
}

/* =====================================================================
//! ���@�e		�ړ��{�^���������ꂽ���̏���
//! ���@��		�{�^���iBUTTON�j�A�v���C���[�iPlayer*�j
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::MoveButtonHighlighted(BUTTON button, Player* player)
{
	// �{�^����������Ă邩�ǂ���
	if (PlayScene::m_pButton[static_cast<int>(button)]->isHighlighted())
	{
		// ���{�^��
		if (button == BUTTON::LEFT)
		{
			// �v���C���[�̌�����ݒ�
			player->setFlippedX(true);

			// �v���C���[�̈ړ�
			if (player->getPositionX() > SIZE_PLAYER_HERF)
			{
				player->Move(-SPEED_MOVE_PLAYER);
			}
		}
		// �E�{�^��
		else
		{
			// �v���C���[�̌�����ݒ�
			player->setFlippedX(false);

			// �v���C���[�̈ړ�
			if (player->getPositionX() < STAGE_WIDTH - SIZE_PLAYER_HERF)
			{
				player->Move(SPEED_MOVE_PLAYER);
			}
		}
	}
}

bool Stage::onTouchBegan(Touch* touch, Event* unused_event)
{
	ChangeSeason();

	return true;
}