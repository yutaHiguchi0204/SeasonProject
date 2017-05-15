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

	// �w�i
	Sprite* back = Sprite::create("background/back_stageSelect.png");
	back->setPosition(480, 270);
	this->addChild(back);

	// �{�^���摜
	cocos2d::ui::Button* selectButton = cocos2d::ui::Button::create("object/selectButton.png");
	selectButton->setPosition(Vec2(128.0f, 96.0f));
	this->addChild(selectButton);

	cocos2d::ui::Button* notSelectButton1 = cocos2d::ui::Button::create("object/Not_selectButton.png");
	notSelectButton1->setPosition(Vec2(WINDOW_WIDTH - 128.0f, 192.0f));
	this->addChild(notSelectButton1);

	cocos2d::ui::Button* notSelectButton2 = cocos2d::ui::Button::create("object/Not_selectButton.png");
	notSelectButton2->setPosition(Vec2(128.0f, WINDOW_HEIGHT - 192.0f));
	this->addChild(notSelectButton2);

	cocos2d::ui::Button* notSelectButton3 = cocos2d::ui::Button::create("object/Not_selectButton.png");
	notSelectButton3->setPosition(Vec2(WINDOW_WIDTH - 128.0f, WINDOW_HEIGHT - 96.0f));
	this->addChild(notSelectButton3);

	// �v���C���[
	m_pSprPlayer = Sprite::create("object/player.png");
	m_pSprPlayer->setPosition(selectButton->getPosition());
	this->addChild(m_pSprPlayer);

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	selectButton->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch, this));

	/// �f�o�b�O�p
	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* keyEvent)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			m_stageID--;
			if (m_stageID < static_cast<int>(STAGE::FLOWER)) m_stageID = static_cast<int>(STAGE::MOON);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			m_stageID++;
			if (m_stageID > static_cast<int>(STAGE::MOON)) m_stageID = static_cast<int>(STAGE::FLOWER);
		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	text = Label::createWithSystemFont(STAGE_NAME[m_stageID], "Arial", 48);
	text->setPosition(Vec2(WINDOW_WIDTH - 64.0f, 64.0f));
	this->addChild(text);

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

	/// �f�o�b�O�p ///
	text->setString(STAGE_NAME[m_stageID]);
}

void StageSelectScene::onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType)
{
	if (eventType == ui::Widget::TouchEventType::ENDED)
	{
		// ���̃V�[�����쐬����
		Scene* nextScene = PlayScene::create();

		//�t�F�[�h�g�����W�V����
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// ���̃V�[���Ɉڍs
		_director->replaceScene(nextScene);
	}
}

void StageSelectScene::animationPlayer()
{
	m_playerGrpX += SIZE_PLAYER;
	if (m_playerGrpX >= SIZE_PLAYER * 3)
	{
		m_playerGrpX = 0;
	}
}