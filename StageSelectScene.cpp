/* =====================================================================
//! @param		�uStageSelectScene�v�N���X�̃\�[�X�t�@�C��
//! @create		���ہ@�E�P
//! @date		17/05/01
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "StageSelectScene.h"
#include "ClearScene.h"
#include "PlayScene.h"

// ���O���
USING_NS_CC;
using namespace std;

// �ÓI�����o�̒�`
int StageSelectScene::m_stageID;

// �V�[���Ǘ�
Scene* StageSelectScene::createScene()
{
	// �V�[�����쐬����
	auto scene = Scene::create();

	// ���C���[���쐬����
	auto layer = StageSelectScene::create();

	// ���C���[���V�[���ɒǉ�����
	scene->addChild(layer);

	// �V�[����Ԃ�
	return scene;
}

// ������
bool StageSelectScene::init()
{
	// ���N���X�̏�����
	if (!Scene::init())
	{
		// ���N���X�̏����������s�Ȃ�A�ُ�I��
		return false;
	}

	// �X�V��������
	scheduleUpdate();

	// �����o�ϐ��̏�����
	m_stageID = static_cast<int>(STAGE::FLOWER);
	m_touchID = static_cast<int>(STAGE::FLOWER);

	// �w�i
	Sprite* back = Sprite::create("background/back_stageSelect.png");
	back->setPosition(480, 270);
	this->addChild(back);

	// �{�^���摜
	for (int i = 0; i < STAGEMAX_NUM; i++)
	{
		selectButton[i]= cocos2d::ui::Button::create("object/selectButton.png");
		selectButton[i]->setPosition(Vec2(i % 2 * 704.0f + 128.0f, i * 112.0f + 96.0f));
		addChild(selectButton[i]);
	}
	
	// �v���C���[
	m_pSprPlayer = Sprite::create("object/player.png");
	m_pSprPlayer->setPosition(selectButton[static_cast<int>(STAGE::FLOWER)]->getPosition());
	this->addChild(m_pSprPlayer);

	// �A�C�e���t�h�ݒ�
	GameManager& gm = GameManager::GetInstance();
	m_pItemUIspr = Sprite::create("object/item_page.png");
	m_pItemUInum = Label::create("0 /100", "HGP�s����", 60);

	std::stringstream strNum;
	strNum << gm.GetPageNum() << " /100";
	m_pItemUInum->setString(strNum.str());

	m_pItemUIspr->setPosition(48.0f, WINDOW_HEIGHT - 48.0f);
	m_pItemUInum->setPosition(192.0f, WINDOW_HEIGHT - 48.0f);
	m_pItemUIspr->setScale(2.0f);
	m_pItemUInum->setColor(Color3B(255, 255, 255));
	this->addChild(m_pItemUIspr);
	this->addChild(m_pItemUInum);
	m_pItemUIspr->runAction(RepeatForever::create(RotateBy::create(4.0f, Vec3(0.0f, 360.0f, 0.0f))));

	// �Z�[�u�{�^��
	m_pSaveButton = cocos2d::ui::Button::create("object/button_dataSave.png");
	m_pSaveButton->setPosition(Vec2(WINDOW_WIDTH - 80.0f, 48.0f));
	this->addChild(m_pSaveButton);

	// �f�[�^�̕ۑ�
	m_pSaveButton->addClickEventListener([&](Ref* ref) { gm.ExportPageInfo(); });

	if (gm.GetPageNum() == NUM_ITEM)
	{
		// �N���A
		cocos2d::ui::Button* clearButton = cocos2d::ui::Button::create("object/clearObj.png");
		clearButton->setPosition(WINDOW_MIDDLE);
		this->addChild(clearButton);

		// ��]������
		clearButton->runAction(RepeatForever::create(RotateBy::create(2.0f, Vec3(0.0f, 0.0f, 360.0f))));

		// �N���A�J��
		clearButton->addClickEventListener([&](Ref* ref) {

			Scene* nextScene = ClearScene::create();
			nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));
			_director->replaceScene(nextScene);
		});
	}

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	selectButton[0]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch, this));
	selectButton[1]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch2, this));
	selectButton[2]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch3, this));
	selectButton[3]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch4, this));

	//�X�e�[�W�Z���N�g��ʂł̉�����
	SoundManager& sm = SoundManager::getInstance();
	sm.UncacheGameSound(SOUND::BGM_TITLE);
	sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);

	return true;
}

void StageSelectScene::update(float delta)
{
	// �v���C���[�A�j���[�V����
	if (m_time % SPEED_ANIMATION == 0) animationPlayer();

	// �摜�̕ύX
	m_pSprPlayer->setTextureRect(Rect(m_playerGrpX, 0, SIZE_PLAYER, SIZE_PLAYER));

	// ���Ԍv��
	m_time++;
}

// �v���C���[�A�j���[�V����
void StageSelectScene::animationPlayer()
{
	m_playerGrpX += SIZE_PLAYER;
	if (m_playerGrpX >= SIZE_PLAYER * 3)
	{
		m_playerGrpX = 0;
	}
}

// �v���C���[�̈ړ�
void StageSelectScene::CharactorMove()
{
	if (m_pSprPlayer->getPosition() == selectButton[m_touchID]->getPosition())
	{
		// �X�e�[�W���艹�̐���
		SoundManager& sm = SoundManager::getInstance();
		sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);
		
		// ���̃V�[�����쐬����
		Scene* nextScene = PlayScene::create();

		// �t�F�[�h�g�����W�V����
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// ���̃V�[���Ɉڍs
		_director->replaceScene(nextScene);

		return;
	}

	//MoveTo* move_action[STAGEMAX_NUM - 1];
	Spawn* move_action[STAGEMAX_NUM - 1];

	int move_distance = m_touchID - m_stageID;

	for (int i = 0; i < STAGEMAX_NUM - 1; i++)
	{
		move_action[i] = nullptr;
	}

	if (move_distance > 0)
	{
		for (int i = 0; i < move_distance; i++)
		{
			MoveTo* move = MoveTo::create(1.0f, selectButton[m_stageID + i + 1]->getPosition());
			
			CallFunc* func = nullptr;

			if (selectButton[m_stageID + i]->getPositionX() > selectButton[m_stageID + i + 1]->getPositionX())
				func = CallFunc::create([&]() { m_pSprPlayer->setFlippedX(true); });
			else
				func = CallFunc::create([&]() { m_pSprPlayer->setFlippedX(false); });

			move_action[i] = Spawn::create(move, func, nullptr);
		}
	}
	else
	{
		move_distance *= -1;

		for (int i = 0; i < move_distance; i++)
		{
			MoveTo* move = MoveTo::create(1.0f, selectButton[m_stageID - i - 1]->getPosition());

			CallFunc* func = nullptr;

			if (selectButton[m_stageID - i]->getPositionX() > selectButton[m_stageID - i - 1]->getPositionX())
				func = CallFunc::create([&]() { m_pSprPlayer->setFlippedX(true); });
			else
				func = CallFunc::create([&]() { m_pSprPlayer->setFlippedX(false); });

			move_action[i] = Spawn::create(move, func, nullptr);
		}
	}

	m_move_action_sequence = Sequence::create(move_action[0], move_action[1], move_action[2], nullptr);

	if (!m_pSprPlayer->getActionByTag(1))
	{
		m_pSprPlayer->stopActionByTag(1);
		m_move_action_sequence->setTag(1);
		m_pSprPlayer->runAction(m_move_action_sequence);

		m_stageID = m_touchID;

		// �X�e�[�W�Z���N�g���̐���
		SoundManager& sm = SoundManager::getInstance();
		sm.UncacheGameSound(SOUND::SE_DECISION);
		sm.PlayGameSound(static_cast<int>(SOUND::SE_STAGESELECT), false);
	}

}