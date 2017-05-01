/* =====================================================================
//! @param		�uTitleScene�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/05/01
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "TitleScene.h"
#include "StageSelectScene.h"

// ���O���
USING_NS_CC;
using namespace std;

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

	// �w�i�摜
	Sprite* back = Sprite::create("title.png");
	back->setPosition(480, 270);
	this->addChild(back);

	//�{�^���摜
	ui::Button* m_tButton = ui::Button::create("start.png");
	m_tButton->setPosition(Vec2(480, 100));
	m_tButton->setScale(1.5f);
	this->addChild(m_tButton);

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	m_tButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::onButtonTouch, this));

	return true;
}

void TitleScene::update(float delta)
{

}

void TitleScene::onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType)
{
	if (eventType == ui::Widget::TouchEventType::ENDED)
	{
		// ���̃V�[�����쐬����
		Scene* nextScene = StageSelectScene::createScene();

		//�t�F�[�h�g�����W�V����
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// ���̃V�[���Ɉڍs
		_director->replaceScene(nextScene);
	}
}
