/* =====================================================================
//! @param		�uStageSelectScene�v�N���X�̃\�[�X�t�@�C��
//! @create		���ہ@�E�P
//! @date		17/05/01
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "StageSelectScene.h"
#include "PlayScene.h"

// ���O���
USING_NS_CC;
using namespace std;

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
	m_touchID = 0;

	// �w�i
	Sprite* back = Sprite::create("background/back_stageSelect.png");
	back->setPosition(480, 270);
	this->addChild(back);

	// �{�^���摜
	for (int i = 0; i < STAGEMAX_NUM; i++)
	{
		selectButton[i]= cocos2d::ui::Button::create("object/selectButton.png");
		selectButton[i]->setPosition(Vec2(i % 2 * 704.0f + 128.0f, i * 88.0f + 96.0f));
		addChild(selectButton[i]);
	}
	
	// �v���C���[
	m_pSprPlayer = Sprite::create("object/player1.png");
	m_pSprPlayer->setPosition(selectButton[static_cast<int>(STAGE::FLOWER)]->getPosition());
	this->addChild(m_pSprPlayer);

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	
	
	selectButton[0]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch, this));
	selectButton[1]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch2, this));
	selectButton[2]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch3, this));
	selectButton[3]->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch4, this));

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

//�v���C���[�̈ړ�
void StageSelectScene::CharactorMove()
{
	if (m_pSprPlayer->getPosition() == selectButton[m_touchID]->getPosition())
	{
		// ���̃V�[�����쐬����
		Scene* nextScene = PlayScene::create();

		//�t�F�[�h�g�����W�V����
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// ���̃V�[���Ɉڍs
		_director->replaceScene(nextScene);

		return;
	}

	MoveTo* move_action[STAGEMAX_NUM - 1];

	int move_distance = m_touchID - m_stageID;

	for (int i = 0; i < STAGEMAX_NUM - 1; i++)
	{
		move_action[i] = nullptr;
	}

	if (move_distance > 0)
	{

		for (int i = 0; i < move_distance; i++)
		{

			move_action[i] = MoveTo::create(1.0f, selectButton[m_stageID + i + 1]->getPosition());

		}
	}
	else
	{
		move_distance *= -1;

		for (int i = 0; i < move_distance; i++)
		{
			move_action[i] = MoveTo::create(1.0f, selectButton[m_stageID - i - 1]->getPosition());
		}
	}

	m_move_action_sequence = Sequence::create(move_action[0], move_action[1], move_action[2], nullptr);

	if (!m_pSprPlayer->getActionByTag(1))
	{
		m_pSprPlayer->stopActionByTag(1);
		m_move_action_sequence->setTag(1);
		m_pSprPlayer->runAction(m_move_action_sequence);

		m_stageID = m_touchID;
	}

}
