#include "PauseScene.h"
#include "PlayScene.h"

// ���O���
USING_NS_CC;
using namespace std;

// �V�[���Ǘ�


//������
bool PauseScene::init()
{
	if (!Node::init())
	{
		return false;
	}

	// �X�V��������
	scheduleUpdate();

	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(PauseScene::onTouchBegan, this);

	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	
}


void PauseScene::update(float delta)
{

}

