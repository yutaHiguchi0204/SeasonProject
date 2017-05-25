/* =====================================================================
//! @param		サウンドマネージャ
//! @create		樋口　裕太
//! @date		17/05/22
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "audio\include\AudioEngine.h"
#include "cocos2d.h"

// 定数
/* サウンドを追加したい場合は用途とファイル名をここに登録してください */
const int NUM_SOUND = 5;

enum class SOUND
{
	
};

const std::string SOUND_NAME[NUM_SOUND] = {
	
};

// クラスの定義
class SoundManager
{
private:
	int soundID;				// 音楽格納用

private:
	SoundManager() { LoadGameSound(); };

public:

	// サウンドマネージャの生成
	static SoundManager& getInstance()
	{
		static SoundManager sm;
		return sm;
	}

	// 音楽のオフロード
	void LoadGameSound()
	{
		// 使用する音楽を全ロードする
		std::stringstream soundFileName;
		for (int i = 0; i < NUM_SOUND; i++)
		{
			soundFileName.str("");
			soundFileName.clear();

			soundFileName << "sound/" << SOUND_NAME[i] << ".ogg";

			cocos2d::experimental::AudioEngine::preload(soundFileName.str());
		}
	}

	// 使用する音楽の登録と再生
	void PlayGameSound(int id, bool loop)
	{
		std::stringstream soundFileName;
		soundFileName << "sound/" << SOUND_NAME[id] << ".ogg";

		// 音楽を登録
		soundID = cocos2d::experimental::AudioEngine::play2d(soundFileName.str());

		// ループ設定
		cocos2d::experimental::AudioEngine::setLoop(soundID, loop);
	}

	// 音楽の停止
	void StopGameSound()
	{
		cocos2d::experimental::AudioEngine::stop(soundID);
	}

	// 音楽のポーズ
	void PauseGameSound()
	{
		cocos2d::experimental::AudioEngine::pause(soundID);
	}

	// 音楽の再開
	void ResumeGameSound()
	{
		cocos2d::experimental::AudioEngine::resume(soundID);
	}

	// キャッシュ削除（一部）
	void UncacheGameSound(SOUND id)
	{
		std::stringstream soundFileName;
		soundFileName << "sound/" << SOUND_NAME[static_cast<int>(id)] << ".ogg";

		cocos2d::experimental::AudioEngine::uncache(soundFileName.str());
	}

	// キャッシュ削除（全部）
	void UncacheGameSoundAll()
	{
		cocos2d::experimental::AudioEngine::uncacheAll();
	}
};