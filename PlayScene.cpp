/* =====================================================================
//! @param		�uPlayScene�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/03/04
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "PlayScene.h"
#include "PauseScene.h"
#include "TitleScene.h"



// ���O���
USING_NS_CC;
using namespace std;

// �ÓI�����o�̒�`
bool Stage::m_isShowObject;

// �����o�֐��̒�`

// �V�[���Ǘ�
Scene* PlayScene::createScene()
{
	// �V�[�����쐬����
	auto scene = Scene::create();

	// ���C���[���쐬����
	auto layer = PlayScene::create();

	// ���C���[���V�[���ɒǉ�����
	scene->addChild(layer);

	// �V�[����Ԃ�
	return scene;
}

//�|�[�Y��ʕ\����\��(bool)
void PlayScene::EnabledPauseback(bool TorF)
{
	Pauseback->setVisible(TorF);
	m_pTitleButton->setVisible(TorF);
	m_pGameBackButton->setVisible(TorF);
}


// ������
bool PlayScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// �X�V��������
	scheduleUpdate();

	// �e�f�[�^�̏����ݒ�
	m_timeCnt = 0;								// ���Ԍv��

	// �X�e�[�W
	m_pStage = Stage::create();
	this->addChild(m_pStage);

	// �{�^������
	m_pButton[static_cast<int>(BUTTON::LEFT)] = OperationButton::create(BUTTON::LEFT);
	m_pButton[static_cast<int>(BUTTON::RIGHT)] = OperationButton::create(BUTTON::RIGHT);
	m_pButton[static_cast<int>(BUTTON::ACTION)] = OperationButton::create(BUTTON::ACTION);

	//Pause�{�^���̍쐬
	m_pPauseButton = ui::Button::create("object/PauseButton.png");
	m_pPauseButton->setPosition(Vec2(70,500));
	m_pPauseButton->setVisible(true);
	this->addChild(m_pPauseButton);

	//�|�[�Y��ʂ̍쐬
	Pauseback = Sprite::create("object/Pause.png");
	Pauseback->setPosition(480, 270);
	Pauseback->setVisible(false);
	this->addChild(Pauseback);

	//�^�C�g���ɖ߂�{�^���̍쐬
	m_pTitleButton = ui::Button::create("object/TitleButton.png");
	m_pTitleButton->setPosition(Vec2(480, 250));
	m_pTitleButton->setVisible(false);
	this->addChild(m_pTitleButton);


	//�Q�[���ɖ߂�{�^���̍쐬
	m_pGameBackButton = ui::Button::create("object/GameBackButton.png");
	m_pGameBackButton->setPosition(Vec2(480, 100));
	m_pGameBackButton->setVisible(false);
	this->addChild(m_pGameBackButton);
	
	

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	m_pPauseButton->addTouchEventListener(CC_CALLBACK_2(PlayScene::onButtonTouch, this));

	// �{�^�����V�[���ɂȂ�
	for (int i = 0; i < NUM_BUTTON; i++) this->addChild(m_pButton[i]);

	return true;
}

/* =====================================================================
//! ���@�e		�X�V����
//! ���@��		�_�~�[�����ifloat�j
//! �߂�l		�Ȃ�
===================================================================== */
void PlayScene::update(float delta)
{
	// �X�N���[��
	m_pStage->Scroll();

	// �A�N�V�����{�^���̏������i�W�����v�{�^���j
	m_pButton[static_cast<int>(BUTTON::ACTION)]->ChangeActionFlg(ACTION::JUMP);

	// �����蔻��
	m_pStage->CheckCollision();

	// ���Ԍv��
	m_timeCnt++;

	// �{�^����������Ă�����v���C���[���ړ�������
	if (!Stage::m_isShowObject)
	{
		// �ړ��{�^���������ꂽ�Ƃ��̏���
		m_pStage->CheckButtonHighlighted(BUTTON::LEFT);
		m_pStage->CheckButtonHighlighted(BUTTON::RIGHT);

		// �A�N�V�����{�^���������ꂽ�Ƃ��̏���
		m_pStage->CheckButtonHighlighted(BUTTON::ACTION);
	}

	// �A�N�V�����{�^���̖��x��߂�
	if ((!Player::m_isJump && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::JUMP)				||
		(!Stage::m_isShowObject && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::SEASON_BOOK)	||
		(!Stage::m_isShowObject && m_pButton[static_cast<int>(BUTTON::ACTION)]->GetActionFlg() == ACTION::SIGN_BOARD))
	{
		m_pButton[static_cast<int>(BUTTON::ACTION)]->SetFullBright();
	}
}

//�|�[�Y�֘A
void PlayScene::onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType)
{
	if (eventType == ui::Widget::TouchEventType::ENDED)
	{
		
		//�|�[�Y�{�^���������ꂽ��
		m_pPauseButton->addClickEventListener([&](Ref* ref)
		{
			EnabledPauseback(true);

		});

		// �Q�[���ɖ߂�{�^���������ꂽ��
		m_pGameBackButton->addClickEventListener([&](Ref* ref)
		{
			EnabledPauseback(false);

		});

		//�^�C�g���ɖ߂邪�����ꂽ�Ƃ�
		m_pTitleButton->addClickEventListener([&](Ref* ref)
		{

			// ���̃V�[�����쐬����
			Scene* nextScene = TitleScene::createScene();

			//�t�F�[�h�g�����W�V����
			nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

			// ���̃V�[���Ɉڍs
			_director->replaceScene(nextScene);

		});
	}
}


