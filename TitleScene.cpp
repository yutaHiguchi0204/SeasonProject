/* =====================================================================
//! @param		�uTitleScene�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/05/01
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "TwoOptionWindow.h"

// ���O���
USING_NS_CC;
using namespace std;

// �萔
const int HERF_COLOR = 127;

// �V�[���Ǘ�
Scene* TitleScene::createScene()
{
	// �V�[�����쐬����
	auto scene = Scene::create();

	// ���C���[���쐬����
	auto layer = TitleScene::create();

	// ���C���[���V�[���ɒǉ�����
	scene->addChild(layer);

	// �V�[����Ԃ�
	return scene;
}

// ������
bool TitleScene::init()
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
	m_time = 0;

	// �w�i�摜
	Sprite* back = Sprite::create("background/back_title.png");
	back->setPosition(WINDOW_WIDTH_HERF, WINDOW_HEIGHT_HERF);
	this->addChild(back);

	// �{�^���摜
	m_pMsgTitle = Sprite::create("object/start.png");
	m_pMsgTitle->setPosition(Vec2(WINDOW_WIDTH - 192.0f, 64.0f));
	m_pMsgTitle->setScale(1.5f);
	m_pMsgTitle->setOpacity(0x80);
	this->addChild(m_pMsgTitle);

	// ���Z�b�g�{�^��
	m_pResetButton = cocos2d::ui::Button::create("object/button_dataReset.png");
	m_pResetButton->setPosition(Vec2(WINDOW_WIDTH - 80.0f, WINDOW_HEIGHT - 32.0f));
	this->addChild(m_pResetButton);
	
	// �f�[�^���Z�b�g
	m_pResetButton->addClickEventListener([&](Ref* ref) {

		// ���艹�̐���
		SoundManager& sm = SoundManager::getInstance();
		sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);
		
		// �E�C���h�E�\��
		TwoOptionWindow* window = TwoOptionWindow::create();
		window->setPosition(WINDOW_MIDDLE);
		window->setScale(0.0f);
		this->addChild(window);
		window->runAction(ScaleTo::create(0.5f, 1.0f));

	});

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(TitleScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// �^�C�g����BGM����
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::BGM_TITLE), false);
	sm.UncacheGameSound(SOUND::BGM_OP);
	
	return true;
}

void TitleScene::update(float delta)
{
	// �t�F�[�h
	if (m_time / HERF_COLOR % 2 == 0)	m_pMsgTitle->setOpacity(m_pMsgTitle->getOpacity() + 0x01);
	else								m_pMsgTitle->setOpacity(m_pMsgTitle->getOpacity() - 0x01);

	// ���Ԍv��
	m_time++;
}

void TitleScene::onTouchEnded(Touch* touch, Event* event)
{
	if (!TwoOptionWindow::m_isResetCheck)
	{
		// ���̃V�[�����쐬����
		Scene* nextScene = StageSelectScene::create();

		// �t�F�[�h�g�����W�V����
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// ���̃V�[���Ɉڍs
		_director->replaceScene(nextScene);
	}
}