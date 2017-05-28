/* =====================================================================
//! @param		�T�E���h�}�l�[�W��
//! @create		����@�T��
//! @date		17/05/22
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "audio\include\AudioEngine.h"
#include "cocos2d.h"

// �萔
/* �T�E���h��ǉ��������ꍇ�͗p�r�ƃt�@�C�����������ɓo�^���Ă������� */
const int NUM_SOUND =15;

enum class SOUND
{
	BGM_TITLE,
	BGM_FLOWER,
	BGM_BIRD,
	BGM_WIND,
	BGM_MOON,
	BGM_CLEAR,

	SE_DECISION,
	SE_SELECT,
	SE_CLOSE,
	SE_JUMP,
	SE_SWIM,
	SE_GET,
	SE_KAFUN,
	SE_CHANGE,
	SE_STAGESELECT,
};

const std::string SOUND_NAME[NUM_SOUND] = {
	"title",
	"flower_stage",
	"bird_stage",
	"wind_stage",
	"moon_stage",
	"clear",

	"decision",
	"select",
	"close",
	"jump",
	"swim",		
	"item_get",	
	"kafun",
	"change",
	"stage_select",
};

// �N���X�̒�`
class SoundManager
{
private:
	int soundID;				// ���y�i�[�p

private:
	SoundManager() { LoadGameSound(); };

public:

	// �T�E���h�}�l�[�W���̐���
	static SoundManager& getInstance()
	{
		static SoundManager sm;
		return sm;
	}

	// ���y�̃I�t���[�h
	void LoadGameSound()
	{
		// �g�p���鉹�y��S���[�h����
		std::stringstream soundFileName;
		for (int i = 0; i < NUM_SOUND; i++)
		{
			soundFileName.str("");
			soundFileName.clear();

			soundFileName << "sound/" << SOUND_NAME[i] << ".ogg";

			cocos2d::experimental::AudioEngine::preload(soundFileName.str());
		}
	}

	// �g�p���鉹�y�̓o�^�ƍĐ�
	void PlayGameSound(int id, bool loop)
	{
		std::stringstream soundFileName;
		soundFileName << "sound/" << SOUND_NAME[id] << ".ogg";

		// ���y��o�^
		soundID = cocos2d::experimental::AudioEngine::play2d(soundFileName.str());

		// ���[�v�ݒ�
		cocos2d::experimental::AudioEngine::setLoop(soundID, loop);
	}

	// ���y�̒�~
	void StopGameSound()
	{
		cocos2d::experimental::AudioEngine::stop(soundID);
	}

	// ���y�̃|�[�Y
	void PauseGameSound()
	{
		cocos2d::experimental::AudioEngine::pause(soundID);
	}

	// ���y�̍ĊJ
	void ResumeGameSound()
	{
		cocos2d::experimental::AudioEngine::resume(soundID);
	}

	// �L���b�V���폜�i�ꕔ�j
	void UncacheGameSound(SOUND id)
	{
		std::stringstream soundFileName;
		soundFileName << "sound/" << SOUND_NAME[static_cast<int>(id)] << ".ogg";

		cocos2d::experimental::AudioEngine::uncache(soundFileName.str());
	}

	// �L���b�V���폜�i�S���j
	void UncacheGameSoundAll()
	{
		cocos2d::experimental::AudioEngine::uncacheAll();
	}
};