/* =====================================================================
//! @param		�uStage�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/04/01
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Stage.h"

// ���O���
USING_NS_CC;

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
//! ���@�e		���C���[���̐ݒ�
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::SetLayerInfo()
{
	for (int i = 0; i < NUM_ROW; i++)
	{
		for (int j = 0; j < NUM_COLUMN; j++)
		{
			auto gid = m_pMapTileLayer[m_season]->getTileGIDAt(Vec2(j, i));

			// �^�C�����̐ݒ�
			SetTileInfoWithProperty(gid, i, j);
		}
	}
}

/* =====================================================================
//! ���@�e		�v���p�e�B����^�C������ݒ�
//! ���@��		GID�iuint32_t�j�A�s�iint�j�A��iint�j
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::SetTileInfoWithProperty(uint32_t gid, int row, int col)
{
	// �v���p�e�B�����擾
	Value propertyValue = m_pMap->getPropertiesForGID(gid);

	if (!propertyValue.isNull())
	{
		// �v���p�e�B���}�b�v�z��Ƃ��ĕێ�
		ValueMap propertyMap = propertyValue.asValueMap();

		if (!propertyMap.empty())
		{
			// �^�C�����̓o�^
			// asInt�֐����g����Έ�s�ōςނ��A�o�O�邽�ߕۗ�
			//m_tileInfo.push_back(TileInfo{ propertyValue.asInt(), Vec2(j * SIZE_TILE, (NUM_ROW - i) * SIZE_TILE - SIZE_TILE) });

			// ���W�ݒ�
			Vec2 pos = Vec2(col * SIZE_TILE, (NUM_ROW - row) * SIZE_TILE - SIZE_TILE);

			int id;

			// �^�C��ID�̎擾
			if		(propertyMap["collision"].asString() == "block")	id = static_cast<int>(TILE::BLOCK);
			else if (propertyMap["collision"].asString() == "water")	id = static_cast<int>(TILE::WATER);
			else if (propertyMap["tree"].asString() == "block")			id = static_cast<int>(TILE::BLOCK);

			// �^�C��ID�̐ݒ�
			m_tileInfo.push_back(TileInfo{ id, pos });

			// ���^�C�������Z
			m_numTiles++;
		}
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

	// ���C���[��\������
	m_pMapTileLayer[m_season]->setVisible(true);
	m_pMapGimmickLayer[m_season]->setVisible(true);
}

/* =====================================================================
//! ���@�e		�}�b�v�̃X�N���[��
//! ���@��		�v���C���[��x���W�ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::Scroll(float playerX, cocos2d::ui::Button* button[])
{
	// �J�����ݒ�
	Camera* camera = getScene()->getDefaultCamera();

	float cameraPos = camera->getPositionX();

	// �J�����ړ��̊�l��ݒ�
	const float CAMERA_BORDER = WINDOW_WIDTH / 2.0f;

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
	camera->setPositionX(cameraPos);
}

/* =====================================================================
//! ���@�e		�����蔻��`�F�b�N
//! ���@��		�v���C���[�iPlayer*�j
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::CheckCollision(Player* player)
{
	for (int i = 0; i < Stage::m_numTiles; i++)
	{
		// �����蔻��`�F�b�N
		if (GameManager::isCollision(Stage::m_tileInfo[i].pos, player->getPosition()))
		{
			switch (Stage::m_tileInfo[i].ID)
			{
			case static_cast<int>(TILE::BLOCK) :			// �u���b�N

				// ����
				player->setPositionY(Stage::m_tileInfo[i].pos.y + SIZE_TILE + SIZE_PLAYER / 2);

				player->Fall(static_cast<int>(TILE::BLOCK), m_season);

				break;

			case static_cast<int>(TILE::WATER) :			// ��

				player->Fall(static_cast<int>(TILE::WATER), m_season);
				break;
			}
		}
	}
}



bool Stage::onTouchBegan(Touch* touch, Event* unused_event)
{
	ChangeSeason();

	return true;
}