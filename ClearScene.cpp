/* =====================================================================
//! @param		�uClearScene�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/05/05
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "ClearScene.h"
#include "StageSelectScene.h"

// ���O���
USING_NS_CC;
using namespace std;

// �����o�֐��̒�`

// �V�[���Ǘ�
Scene* ClearScene::createScene()
{
	// �V�[�����쐬����
	auto scene = Scene::create();

	// ���C���[���쐬����
	auto layer = ClearScene::create();

	// ���C���[���V�[���ɒǉ�����
	scene->addChild(layer);

	// �V�[����Ԃ�
	return scene;
}

// ������
bool ClearScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// �X�V��������
	scheduleUpdate();

	// �w�i
	m_pBack = Sprite::create("background/back_clear.png");
	m_pBack->setPosition(WINDOW_MIDDLE);
	this->addChild(m_pBack);

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ClearScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// �N���A��BGM����
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::BGM_CLEAR), false);

	return true;
}

/* =====================================================================
//! ���@�e		�^�b�`����
//! ���@��		�^�b�`���iTouch�j�A�C�x���g���iEvent�j
//! �߂�l		�^�b�`���ꂽ���ۂ��ibool�j
===================================================================== */
bool ClearScene::onTouchBegan(Touch* touch, Event* pEvent)
{
	// ���̃V�[�����쐬����
	Scene* nextScene = StageSelectScene::create();

	// �t�F�[�h�g�����W�V����
	nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

	// ���̃V�[���Ɉڍs
	_director->replaceScene(nextScene);

	return false;
}