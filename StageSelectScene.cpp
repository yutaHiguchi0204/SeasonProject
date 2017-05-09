/* =====================================================================
//! @param		�uStageSelectScene�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
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

	Sprite* back = Sprite::create("background/back_spring.png");
	back->setPosition(480, 270);
	this->addChild(back);

	// �{�^���摜
	ui::Button* selectButton = ui::Button::create("object/selectButton.png");
	selectButton->setPosition(Vec2(128.0f, 96.0f));
	this->addChild(selectButton);

	ui::Button* NotselectButton1 = ui::Button::create("object/Not_selectButton.png");
	NotselectButton1->setPosition(Vec2(WINDOW_WIDTH - 128.0f, 192.0f));
	this->addChild(NotselectButton1);

	ui::Button* NotselectButton2 = ui::Button::create("object/Not_selectButton.png");
	NotselectButton2->setPosition(Vec2(128.0f, WINDOW_HEIGHT - 192.0f));
	this->addChild(NotselectButton2);

	ui::Button* NotselectButton3 = ui::Button::create("object/Not_selectButton.png");
	NotselectButton3->setPosition(Vec2(WINDOW_WIDTH - 128.0f, WINDOW_HEIGHT - 96.0f));
	this->addChild(NotselectButton3);

	// �v���C���[
	m_pSprPlayer = Sprite::create(("object/player.png"));
	m_pSprPlayer->setPosition(selectButton->getPosition());
	this->addChild(m_pSprPlayer);

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	m_selectButton->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::onButtonTouch, this));

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

void StageSelectScene::onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType)
{
	if (eventType == ui::Widget::TouchEventType::ENDED)
	{
		// ���̃V�[�����쐬����
		Scene* nextScene = PlayScene::createScene();

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
