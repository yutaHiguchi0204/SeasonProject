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
int Stage::m_season;
bool Stage::m_isLeftCollision;
bool Stage::m_isRightCollision;
bool Stage::m_isTopCollision;
bool Stage::m_isShowObject;
bool Stage::m_isPause;

// �����o�֐��̒�`

// ������
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
	m_isLeftCollision = false;							// ������t���O
	m_isRightCollision = false;							// �E����t���O
	m_isTopCollision = false;							// �㔻��t���O
	m_isShowObject = false;								// �I�u�W�F�N�g���Q�Ƃ��Ă��邩�ǂ���
	m_isPause = false;									// �|�[�Y�����ǂ���
	Pollen::m_isPollenFlg = false;						// �ԕ��t���O�����낵�Ă���
	m_numTiles = 0;										// �^�C����
	m_numItems = 0;										// �A�C�e����
	m_numGimmicks = 0;									// �M�~�b�N��
	m_Leftnum	  = 0;
	m_Rightnum	  = 0;
	m_Topnum	  = 0;

	// �e�X�e�[�W�̉��̐���
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);
	sm.PlayGameSound(StageSelectScene::m_stageID + static_cast<int>(SOUND::BGM_FLOWER), true);

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
	if		(StageSelectScene::m_stageID == static_cast<int>(STAGE::FLOWER))	m_pPlayer->setPosition(Vec2(192.0f, 216.0f));
	else if (StageSelectScene::m_stageID == static_cast<int>(STAGE::BIRD))		m_pPlayer->setPosition(Vec2(64.0f, 440.0f));
	else if (StageSelectScene::m_stageID == static_cast<int>(STAGE::WIND))		m_pPlayer->setPosition(Vec2(64.0f, 216.0f));
	else if (StageSelectScene::m_stageID == static_cast<int>(STAGE::MOON))		m_pPlayer->setPosition(Vec2(64.0f, 504.0f));
	this->addChild(m_pPlayer, 1);

	// �G�ߋL
	m_pSeasonBook = nullptr;

	// �A�C�e���t�h�ݒ�
	m_pItemUIspr = Sprite::create("object/item_page.png");
	m_pItemUInum = Label::create("0 /25", "HGP�s����", 60);
	m_pItemUIspr->setPosition(192.0f, WINDOW_HEIGHT - 48.0f);
	m_pItemUInum->setPosition(320.0f, WINDOW_HEIGHT - 48.0f);
	m_pItemUIspr->setScale(2.0f);
	m_pItemUInum->setColor(Color3B(0, 0, 0));
	this->addChild(m_pItemUIspr, 2);
	this->addChild(m_pItemUInum, 2);
	m_pItemUIspr->runAction(RepeatForever::create(RotateBy::create(4.0f, Vec3(0.0f, 360.0f, 0.0f))));

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

	// �A�C�e���t�h���x���̕ύX
	GameManager& gm = GameManager::GetInstance();
	std::stringstream strNum;
	strNum << gm.GetPageStageNum(StageSelectScene::m_stageID) << " /25";
	m_pItemUInum->setString(strNum.str());

	/// �f�o�b�O�p
	if (!m_isPause)
	{
		// �{�^����������Ă�����v���C���[���ړ�������
		if (!m_isShowObject)
		{
			if (keyLeft)
			{
				// �v���C���[�̌�����ݒ�
				m_pPlayer->setFlippedX(true);

				// �v���C���[�̈ړ�
				if (m_pPlayer->getPositionX() > SIZE_PLAYER_HERF && !m_isLeftCollision)
				{
					m_pPlayer->Move(-SPEED_MOVE_PLAYER);
				}
			}
			if (keyRight)
			{
				// �v���C���[�̌�����ݒ�
				m_pPlayer->setFlippedX(false);

				// �v���C���[�̈ړ�
				if (m_pPlayer->getPositionX() < STAGE_WIDTH - SIZE_PLAYER_HERF && !m_isRightCollision)
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

		sFileName << "itemLayer_" << SEASON_NAME[i];

		// �A�C�e�����C���[
		m_pMapItemLayer[i] = m_pMap->getLayer(sFileName.str());
		m_pMapItemLayer[i]->setVisible(false);

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

	// �A�C�e�����̏�����
	while (!m_itemInfo.empty())
	{
		m_itemInfo.pop_back();
	}
	while (!m_item.empty())
	{
		if (m_item[m_item.size() - 1] != nullptr)
		{
			m_item[m_item.size() - 1]->removeFromParent();
			m_item[m_item.size() - 1] = nullptr;
		}
		m_item.pop_back();
	}

	// �M�~�b�N���̏�����
	while (!m_gimmickInfo.empty())
	{
		m_gimmickInfo.pop_back();
	}

	// �^�C�����̏�����
	m_numTiles = 0;
	m_numItems = 0;
	m_numGimmicks = 0;

	// �^�C�����̐ݒ�
	SetLayerInfo();

	// �A�C�e���ݒ�
	SetItem();
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

	// �A�C�e�����̐ݒ�
	SetTileInfoWithLayer(m_pMapItemLayer[m_season], KIND_TILE::ITEM);

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

	case KIND_TILE::ITEM:		// �A�C�e��

		// �A�C�e���ݒ�
		if		(map["item"].asString() == "page")			id = static_cast<int>(TILE::ITEM);
		else												id = static_cast<int>(TILE::NONE);

		// �A�C�e��ID�̐ݒ�
		m_itemInfo.push_back(StageInfo{ id, pos });

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
//! ���@�e		�A�C�e������ݒ�
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::SetItem()
{
	GameManager& gm = GameManager::GetInstance();

	// �A�C�e���̂h�c���ǂ̗v�f�ԍ�����n�܂邩�𒲂ׂ�
	int idStart = 0;
	for (int i = 0; i < StageSelectScene::m_stageID * NUM_STAGE + m_season; i++)
	{
		idStart += NUM_ITEM_PLACE[i];
	}

	for (int i = 0; i < NUM_ITEM_PLACE[StageSelectScene::m_stageID * NUM_STAGE + m_season]; i++)
	{
		m_item.push_back(Item::create());
		m_item[m_item.size() - 1]->setPosition(Vec2(m_itemInfo[i].pos.x + SIZE_TILE / 2, m_itemInfo[i].pos.y));
		this->addChild(m_item[m_item.size() - 1], -1);

		if (gm.GetPage()[idStart + i])
		{
			m_item[m_item.size() - 1]->removeFromParent();
			m_item[m_item.size() - 1] = nullptr;
		}

		// �A�C�e�������Z
		m_numItems++;
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
		// �A�C�e���t�h�ړ�
		m_pItemUIspr->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 192.0f);
		m_pItemUInum->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 320.0f);

		// �p�[�e�B�N���ړ�
		if (m_pParticle != nullptr) m_pParticle->ParticleScroll(GetCameraPosX());

		// �ԕ��ړ�
		if (Pollen::m_isPollenFlg)
		{
			m_pPollen->setPositionX(GetCameraPosX());
		}

		// �{�^���ړ�
		PlayScene::m_pButton[static_cast<int>(BUTTON::LEFT)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 80.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::RIGHT)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 208.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->setPositionX(m_pPlayer->getPositionX() + WINDOW_WIDTH_HERF - 80.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::PAUSE)]->setPositionX(m_pPlayer->getPositionX() - WINDOW_WIDTH_HERF + 88.0f);
		PlayScene::m_pButton[static_cast<int>(BUTTON::SEASON_BOOK)]->setPositionX(m_pPlayer->getPositionX() + WINDOW_WIDTH_HERF - 184.0f);

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
	// �����蔻��t���O�̏�����
	Stage::m_isLeftCollision = false;
	Stage::m_isRightCollision = false;
	Stage::m_isTopCollision = false;

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

		// �e�����蔻��
		if (gm.CheckCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::LEFT && m_tileInfo[i].ID != static_cast<int>(TILE::WATER))
		{
			m_Leftnum = static_cast<int>(COLLISION::LEFT);
			m_isLeftCollision = true;
		}
		else if (gm.CheckCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::RIGHT && m_tileInfo[i].ID != static_cast<int>(TILE::WATER))
		{
			m_Rightnum = static_cast<int>(COLLISION::RIGHT);
			m_isRightCollision = true;
		}
		else if (gm.CheckCollision(m_tileInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::UP && m_tileInfo[i].ID != static_cast<int>(TILE::WATER))
		{
			m_Topnum = static_cast<int>(COLLISION::UP);
			m_pPlayer->SetSpdY(-1.0f);
			m_isTopCollision = true;
		}
		else
		{
			m_Leftnum = static_cast<int>(COLLISION::NONE);
			m_Rightnum = static_cast<int>(COLLISION::NONE);
			m_Topnum = static_cast<int>(COLLISION::NONE);
		}

		// �߂荞�ݔ���
		if (m_tileInfo[i].ID != static_cast<int>(TILE::WATER))
		{
			if ((m_Leftnum == static_cast<int>(COLLISION::LEFT)) &&
				(m_Rightnum == static_cast<int>(COLLISION::RIGHT)) &&
				(m_Topnum == static_cast<int>(COLLISION::UP)))
			{
				if (!Player::m_isJump)
				{
					m_pPlayer->SetSpdY(0.0f);
					m_isLeftCollision = true;
					m_isRightCollision = true;
				}
			}
			else if ((m_Rightnum == static_cast<int>(COLLISION::RIGHT)) &&
					(m_Topnum == static_cast<int>(COLLISION::UP)))
			{
				if (!Player::m_isJump)
				{
					m_pPlayer->SetSpdY(0.0f);
					m_isLeftCollision = true;
					m_isRightCollision = true;
				}
			}
			else if ((m_Leftnum == static_cast<int>(COLLISION::LEFT)) &&
				(m_Topnum == static_cast<int>(COLLISION::UP)))
			{
				if (!Player::m_isJump)
				{
					m_pPlayer->SetSpdY(0.0f);
					m_isLeftCollision = true;
					m_isRightCollision = true;
				}
			}
		}

	}

	if (m_season == m_seasonBefore)
	{
		// �A�C�e���̂h�c���ǂ̗v�f�ԍ�����n�܂邩�𒲂ׂ�
		int idStart = 0;
		for (int i = 0; i < StageSelectScene::m_stageID * NUM_STAGE + m_season; i++)
		{
			idStart += NUM_ITEM_PLACE[i];
		}

		// �A�C�e���Ƃ̓����蔻��
		for (int i = 0; i < m_numItems; i++)
		{
			if (!gm.GetPage()[idStart + i])
			{
				if (gm.isCollision(m_itemInfo[i].pos, m_pPlayer->getPosition()))
				{
					// �y�[�W�擾
					gm.SetPage(idStart + i);

					// �A�C�e�����擾�������̉��̐���
					SoundManager& sm = SoundManager::getInstance();
					sm.PlayGameSound(static_cast<int>(SOUND::SE_GET), false);

					// �y�[�W������
					m_item[i]->removeFromParent();
					m_item[i] = nullptr;
				}
			}
		}
	}

	// �M�~�b�N�Ƃ̓����蔻��
	for (int i = 0; i < m_numGimmicks; i++)
	{
		// ���̏ꍇ�ԕ����o��
		if (m_gimmickInfo[i].ID == static_cast<int>(TILE::POLLEN) && !Pollen::m_isPollenFlg)
		{
			if (gm.isCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()))
			{
				m_pPollen = Pollen::create();
				m_pPollen->setPosition(Vec2(GetCameraPosX(), WINDOW_HEIGHT_HERF));
				this->addChild(m_pPollen, 5);
			}
		}
		else
		{
			// ���n����
			if (m_gimmickInfo[i].ID == static_cast<int>(TILE::BLOCK) && gm.CheckCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::DOWN)
			{
				// �^�C���ɉ������v���C���[�̏���
				m_pPlayer->Action(m_gimmickInfo[i].ID, m_gimmickInfo[i].pos, m_season);
				break;
			}

			// �e�����蔻��
			if		(m_gimmickInfo[i].ID == static_cast<int>(TILE::BLOCK) && gm.CheckCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::LEFT)		m_isLeftCollision = true;
			else if (m_gimmickInfo[i].ID == static_cast<int>(TILE::BLOCK) && gm.CheckCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::RIGHT)		m_isRightCollision = true;
			else if (m_gimmickInfo[i].ID == static_cast<int>(TILE::BLOCK) && gm.CheckCollision(m_gimmickInfo[i].pos, m_pPlayer->getPosition()) == COLLISION::UP)
			{
				m_pPlayer->SetSpdY(-1.0f);
				m_isTopCollision = true;
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
			if (m_pPlayer->getPositionX() > SIZE_PLAYER_HERF && !m_isLeftCollision)
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
			if (m_pPlayer->getPositionX() < STAGE_WIDTH - SIZE_PLAYER_HERF && !m_isRightCollision)
			{
				m_pPlayer->Move(SPEED_MOVE_PLAYER);
			}
		}
		// �A�N�V�����{�^��
		else if (button == BUTTON::ACTION)
		{
			// �W�����v���ĂȂ��Ƃ��ɏ���
			if (!Player::m_isJump && !m_isTopCollision)
			{
				m_pPlayer->Jump();
				PlayScene::m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright(false);
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
//! ���@�e		�L�[�f�o�b�O
//! ���@��		���낢��
//! �߂�l		�Ȃ�
===================================================================== */
void Stage::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		keyLeft = true;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		keyRight = true;
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