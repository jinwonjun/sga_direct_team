#include "stdafx.h"
#include "soundManager.h"

SoundManager::SoundManager() : m_system(NULL), m_channel(NULL), m_sound(NULL)
{
}

SoundManager::~SoundManager()
{
}


HRESULT SoundManager::Init(void)
{
	//사운드 시스템 생성
	System_Create(&m_system);

	//maxchannels : fmod 에서 사용하는 최대 채널의 수를 뜻함
	//사운드 채널 수 생성
	m_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//사운드, 채널 동적할당
	m_sound = new Sound *[TOTALSOUNDBUFFER];
	m_channel = new Channel *[TOTALSOUNDBUFFER];

	//메모리 초기화
	memset(m_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(m_sound, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));

	//사용할 사운드 등록 AddSound("키이름", "위치", "BGM여부", "루프여부");
	//												-> 기본으로 false, false
	//BGM
	AddSound("gameScene", "resources/sound/warFrame.mp3", true, true);
	AddSound("bossScene", "resources/sound/boss_theme.mp3", true, true);



	//Effect
	AddSound("swing", "resources/sound/swing.mp3", false, false);

	AddSound("m4al_1", "resources/sound/m4a1_1.mp3", false, false);
	//AddSound("m4a1_2", "resources/sound/m4a1_2.mp3", false, false);
	AddSound("m4a1_reload", "resources/sound/m4a1_reload.mp3", false, false);
	AddSound("m4a1_reload2", "resources/sound/m4a1_reload2.mp3", false, false);

	AddSound("zod_gun", "resources/sound/zod_gun.mp3", false, false);

	//AddSound("laser_gun", "resources/sound/laser.mp3", false, false);
	AddSound("laser_gun", "resources/sound/laser2.mp3", false, false);

	AddSound("footstep", "resources/sound/footstep.mp3", false, false);
	AddSound("teleport", "resources/sound/teleport.mp3", false, false);

	AddSound("clothEquip_inventory", "resources/sound/clothEquip_inventory.mp3", false, false);
	AddSound("buyItem_inventory", "resources/sound/buyItem_inventory.mp3", false, false);

	AddSound("zealot_apply", "resources/sound/zealot_apply.mp3", false, false);
	AddSound("Zealot_Death00", "resources/sound/Zealot_Death00.mp3", false, false);
	AddSound("Zealot_Death02", "resources/sound/Zealot_Death02.mp3", false, false);
	AddSound("Zealot_Death03", "resources/sound/Zealot_Death03.mp3", false, false);

	AddSound("zealot_death", "resources/sound/zealot_death.mp3", false, false);
	//AddSound("zealot_attack", "resources/sound/zealot_attack.mp3", false, false);
	AddSound("zealot_attack", "resources/sound/zealot_attack3.mp3", false, false);



	AddSound("boss_apply", "resources/sound/boss_apply.mp3", false, false);
	AddSound("boss_death", "resources/sound/Zealot_Death04.mp3", false, false);
	return S_OK;
}

void SoundManager::Destroy(void)
{
	//사운드 및 채널 삭제
	if (m_channel != NULL || m_sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (m_channel != NULL)
			{
				if (m_channel[i]) m_channel[i]->stop();
			}

			if (m_sound != NULL)
			{
				if (m_sound[i]) m_sound[i]->release();
			}
		}
	}

	//메모리 지우기
	SAFE_DELETE(m_channel);
	SAFE_DELETE(m_sound);

	//시스템 닫기
	if (m_system != NULL)
	{
		m_system->release();
		m_system->close();
	}

}

void SoundManager::Update()
{
	/*
	사운드 시스템을 계속 업데이트 해워야 볼륨이 바뀌거나
	재생이 끝난 사운드를 채널에서 빼내는 등 다양한 작업을 자동으로 해준다.
	*/

	m_system->update();
}

void SoundManager::AddSound(string keyName, string soundName, bool bgm, bool loop)
{
	//루프를 돌릴떄
	if (loop)
	{
		//bgm
		if (bgm)
		{
			//createStream : 배경음악
			m_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_sound[m_mapSounds.size()]);
		}
		//이펙트
		else
		{
			//createSound : 효과음(createSound로 여러개 재생할 수 있지만 대용량 음악 파일을 로드시키면 메모리 낭비)
			m_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_sound[m_mapSounds.size()]);
		}
	}
	//루프안돌릴 이펙트
	else
	{
		m_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &m_sound[m_mapSounds.size()]);
	}

	//맵에 사운드를 키값과 함께 담아준다.
	m_mapSounds.insert(make_pair(keyName, &m_sound[m_mapSounds.size()]));
}

void SoundManager::Play(string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = m_mapSounds.begin();
	for (iter; iter != m_mapSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이
			m_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &m_channel[count]);
			//볼륨셋팅
			m_channel[count]->setVolume(volume);
		}
	}
}

void SoundManager::Stop(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_mapSounds.begin();
	for (iter; iter != m_mapSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			m_channel[count]->stop();
			break;
		}
	}
}

void SoundManager::Pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_mapSounds.begin();
	for (iter; iter != m_mapSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 일시정지
			m_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::Resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_mapSounds.begin();
	for (iter; iter != m_mapSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 다시재생
			m_channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::IsPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = m_mapSounds.begin();
	for (iter; iter != m_mapSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool SoundManager::IsPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = m_mapSounds.begin();
	for (iter; iter != m_mapSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_channel[count]->isPlaying(&isPause);
			break;
		}
	}

	return isPause;
}

void SoundManager::VolumeUp(string keyName, const float volume)
{
	int count = 0;
	arrSoundIter iter = m_mapSounds.begin();
	for (iter; iter != m_mapSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			float preVolume;
			m_channel[count]->getVolume(&preVolume);
			preVolume = preVolume + volume;
			if (preVolume > 1.0f) preVolume = 1.0f;
			m_channel[count]->setVolume(preVolume);
			break;
		}
	}
}

void SoundManager::VolumeDown(string keyName, const float volume)
{
	int count = 0;
	arrSoundIter iter = m_mapSounds.begin();
	for (iter; iter != m_mapSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			float preVolume;
			m_channel[count]->getVolume(&preVolume);
			preVolume = preVolume - volume;
			if (preVolume < 0.0f) preVolume = 0.0f;
			m_channel[count]->setVolume(preVolume);
			break;
		}
	}
}