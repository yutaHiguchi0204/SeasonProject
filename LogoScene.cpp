/* =====================================================================
//! @param		�uLogoScene�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/05/23
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "LogoScene.h"
#include "TitleScene.h"

// ���O���
USING_NS_CC;

// �V�[���Ǘ�
Scene* LogoScene::createScene()
{
	// �V�[�����쐬����
	auto scene = Scene::create();

	// ���C���[���쐬����
	auto layer = LogoScene::create();

	// ���C���[���V�[���ɒǉ�����
	scene->addChild(layer);

	// �V�[����Ԃ�
	return scene;
}

// ������
bool LogoScene::init()
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

	// ���S�摜
	m_pLogo = Sprite::create("background/back_logo.png");
	m_pLogo->setPosition(WINDOW_MIDDLE);
	m_pLogo->setOpacity(0x00);
	this->addChild(m_pLogo);

	// �t�F�[�h
	m_pLogo->runAction(Sequence::create(
		FadeIn::create(2.0f),
		FadeOut::create(2.0f),
		CallFunc::create([&]() {
			// ���̃V�[�����쐬����
			Scene* nextScene = TitleScene::create();
			// ���̃V�[���Ɉڍs
			_director->replaceScene(nextScene);
		}),
		nullptr
		)
	);

	return true;
}