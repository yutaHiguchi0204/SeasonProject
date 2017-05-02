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

	Sprite* back = Sprite::create("Stageselect.png");
	back->setPosition(480, 270);
	this->addChild(back);

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(StageSelectScene::onTouchBegan, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void StageSelectScene::update(float delta)
{

}

bool StageSelectScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent)
{
	// ���̃V�[�����쐬����
	Scene* nextScene = PlayScene::create();

	//�t�F�[�h�g�����W�V����
	nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

	// ���̃V�[���Ɉڍs
	_director->replaceScene(nextScene);

	return false;
}
