/* =====================================================================
//! @param		�uOpeningScene�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/06/07
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "OpeningScene.h"
#include "TitleScene.h"

// ���O���
USING_NS_CC;

// �萔
const int HERF_COLOR = 127;
const int NUM_LINES = 19;
const int NUM_WINDOW_LINES = 7;
const float TIME_SCENE_TRANS = 72.0f;

// �V�[���Ǘ�
Scene* OpeningScene::createScene()
{
	// �V�[�����쐬����
	auto scene = Scene::create();

	// ���C���[���쐬����
	auto layer = OpeningScene::create();

	// ���C���[���V�[���ɒǉ�����
	scene->addChild(layer);

	// �V�[����Ԃ�
	return scene;
}

// ������
bool OpeningScene::init()
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

	// �w�i
	Sprite* back = Sprite::create("opening/back.png");
	back->setPosition(Vec2(0.0f, -WINDOW_HEIGHT));
	back->setAnchorPoint(Vec2(0.0f, 0.0f));
	back->setOpacity(0xff);
	this->addChild(back);
	Sprite* back2 = Sprite::create("opening/back2.png");
	back2->setPosition(Vec2(0.0f, -WINDOW_HEIGHT));
	back2->setAnchorPoint(Vec2(0.0f, 0.0f));
	back2->setOpacity(0x00);
	this->addChild(back2);

	// �{�^���摜
	m_pButtonSkip = Sprite::create("opening/button_skip.png");
	m_pButtonSkip->setPosition(Vec2(WINDOW_WIDTH - 128.0f, 32.0f));
	m_pButtonSkip->setOpacity(0x80);
	this->addChild(m_pButtonSkip);

	// �^�C�g����BGM����
	SoundManager& sm = SoundManager::getInstance();
	sm.PlayGameSound(static_cast<int>(SOUND::BGM_OP), false);

	// �Z���t��\��
	DrawLines();

	// �w�i�𓮂�������F��ς����肷��
	back->runAction(Sequence::create(
		MoveTo::create(20.0f, Vec2(0.0f, 0.0f)),
		DelayTime::create(14.0f),
		FadeOut::create(2.0f),
		nullptr
	));
	back2->runAction(Sequence::create(
		MoveTo::create(20.0f, Vec2(0.0f, 0.0f)),
		DelayTime::create(14.0f),
		FadeIn::create(2.0f),
		nullptr
	));

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(OpeningScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(OpeningScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

/* =====================================================================
//! ���@�e		�X�V����
//! ���@��		�_�~�[�����ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void OpeningScene::update(float delta)
{
	// �t�F�[�h
	if (m_time / HERF_COLOR % 2 == 0)	m_pButtonSkip->setOpacity(m_pButtonSkip->getOpacity() + 0x01);
	else								m_pButtonSkip->setOpacity(m_pButtonSkip->getOpacity() - 0x01);

	// ���Ԍv��
	m_time++;
}

/* =====================================================================
//! ���@�e		�Z���t��\��
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void OpeningScene::DrawLines()
{
	Sprite* lines[NUM_LINES];

	// �Z���t�̃��[�h
	for (int i = 0; i < NUM_LINES; i++)
	{
		std::stringstream sFileName;

		sFileName.str("");
		sFileName.clear();

		sFileName << "opening/lines" << i + 1 << ".png";

		lines[i] = Sprite::create(sFileName.str());
		lines[i]->setPosition(0.0f, WINDOW_HEIGHT - i % NUM_WINDOW_LINES * 64.0f);
		lines[i]->setAnchorPoint(Vec2(0.0f, 1.0f));
		lines[i]->setOpacity(0x00);
		this->addChild(lines[i]);
	}

	// �Z���t���o��
	for (int i = 0; i < NUM_LINES; i++)
	{
		if		(i < NUM_WINDOW_LINES)		lines[i]->runAction(Sequence::create(DelayTime::create(i * 3.0f + 2.0f), FadeIn::create(1.0f), DelayTime::create(22.0f - i * 3.0f), FadeOut::create(1.0f), nullptr));
		else if (i < NUM_WINDOW_LINES + 2)	lines[i]->runAction(Sequence::create(DelayTime::create((i - NUM_WINDOW_LINES) * 3.0f + 26.0f), FadeIn::create(1.0f), DelayTime::create(28.0f - (i - NUM_WINDOW_LINES) * 3.0f), FadeOut::create(1.0f), nullptr));
		else if (i < NUM_WINDOW_LINES * 2)	lines[i]->runAction(Sequence::create(DelayTime::create((i - (NUM_WINDOW_LINES + 2)) * 3.0f + 38.0f), FadeIn::create(1.0f), DelayTime::create(16.0f - (i - (NUM_WINDOW_LINES + 2)) * 3.0f), FadeOut::create(1.0f), nullptr));
		else								lines[i]->runAction(Sequence::create(DelayTime::create((i - (NUM_WINDOW_LINES * 2)) * 3.0f + 56.0f), FadeIn::create(1.0f), nullptr));
	}
	
	// �V�Q�b��Ƀ^�C�g���V�[����
	CallFuncAfter(TIME_SCENE_TRANS, [&]() {

		// ���̃V�[�����쐬����
		Scene* nextScene = TitleScene::create();

		// �t�F�[�h�g�����W�V����
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// ���̃V�[���Ɉڍs
		_director->replaceScene(nextScene);
	});
}

/* =====================================================================
//! ���@�e		�^�b�`�̏I������
//! ���@��		�^�b�`���iTouch*�j�A�C�x���g���iEvent*�j
//! �߂�l		�Ȃ�
===================================================================== */
void OpeningScene::onTouchEnded(Touch* touch, Event* event)
{
	// ���̃V�[�����쐬����
	Scene* nextScene = TitleScene::create();

	// �t�F�[�h�g�����W�V����
	nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

	// ���̃V�[���Ɉڍs
	_director->replaceScene(nextScene);
}