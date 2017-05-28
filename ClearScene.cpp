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

// �萔
const int HERF_COLOR = 127;

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

	// �����o�ϐ��̏�����
	m_time = 0;

	// �w�i
	m_pBack = Sprite::create("background/back_clear.png");
	m_pBack->setPosition(WINDOW_MIDDLE);
	this->addChild(m_pBack);

	// �{�^���摜
	m_pMsgBack = Sprite::create("object/button_clearBack.png");
	m_pMsgBack->setPosition(Vec2(WINDOW_WIDTH - 80.0f, WINDOW_HEIGHT - 32.0f));
	m_pMsgBack->setOpacity(0x80);
	this->addChild(m_pMsgBack);

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ClearScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	
	//���艹�̐���
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);
	// �N���A��BGM����
	sm.PlayGameSound(static_cast<int>(SOUND::BGM_CLEAR), false);

	return true;
}

/* =====================================================================
//! ���@�e		�X�V����
//! ���@��		�_�~�[�����ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void ClearScene::update(float delta)
{
	// �t�F�[�h
	if (m_time / HERF_COLOR % 2 == 0)	m_pMsgBack->setOpacity(m_pMsgBack->getOpacity() + 0x01);
	else								m_pMsgBack->setOpacity(m_pMsgBack->getOpacity() - 0x01);

	// ���Ԍv��
	m_time++;
}

/* =====================================================================
//! ���@�e		�^�b�`����
//! ���@��		�^�b�`���iTouch�j�A�C�x���g���iEvent�j
//! �߂�l		�^�b�`���ꂽ���ۂ��ibool�j
===================================================================== */
bool ClearScene::onTouchBegan(Touch* touch, Event* pEvent)
{
	//���艹�𐶐�
	SoundManager& sm = SoundManager::getInstance();
	sm.UncacheGameSound(SOUND::BGM_CLEAR);
	sm.PlayGameSound(static_cast<int>(SOUND::SE_DECISION), false);

	// ���̃V�[�����쐬����
	Scene* nextScene = StageSelectScene::create();

	// �t�F�[�h�g�����W�V����
	nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

	// ���̃V�[���Ɉڍs
	_director->replaceScene(nextScene);

	return false;
}