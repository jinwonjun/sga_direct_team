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
	//���� �ý��� ����
	System_Create(&m_system);

	//maxchannels : fmod ���� ����ϴ� �ִ� ä���� ���� ����
	//���� ä�� �� ����
	m_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//����, ä�� �����Ҵ�
	m_sound = new Sound *[TOTALSOUNDBUFFER];
	m_channel = new Channel *[TOTALSOUNDBUFFER];

	//�޸� �ʱ�ȭ
	memset(m_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(m_sound, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));

	//����� ���� ��� AddSound("Ű�̸�", "��ġ", "BGM����", "��������");
	//												-> �⺻���� false, false
	AddSound("gameScene", "resources/sound/warFrame.mp3", true, true);
	AddSound("gunFire", "resources/sound/AK47_SW_Fire.mp3", false, false);

	return S_OK;
}

void SoundManager::Destroy(void)
{
	//���� �� ä�� ����
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

	//�޸� �����
	SAFE_DELETE(m_channel);
	SAFE_DELETE(m_sound);

	//�ý��� �ݱ�
	if (m_system != NULL)
	{
		m_system->release();
		m_system->close();
	}

}

void SoundManager::Update()
{
	/*
	���� �ý����� ��� ������Ʈ �ؿ��� ������ �ٲ�ų�
	����� ���� ���带 ä�ο��� ������ �� �پ��� �۾��� �ڵ����� ���ش�.
	*/

	m_system->update();
}

void SoundManager::AddSound(string keyName, string soundName, bool bgm, bool loop)
{
	//������ ������
	if (loop)
	{
		//bgm
		if (bgm)
		{
			//createStream : �������
			m_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_sound[m_mapSounds.size()]);
		}
		//����Ʈ
		else
		{
			//createSound : ȿ����(createSound�� ������ ����� �� ������ ��뷮 ���� ������ �ε��Ű�� �޸� ����)
			m_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_sound[m_mapSounds.size()]);
		}
	}
	//�����ȵ��� ����Ʈ
	else
	{
		m_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &m_sound[m_mapSounds.size()]);
	}

	//�ʿ� ���带 Ű���� �Բ� ����ش�.
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
			//���� �÷���
			m_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &m_channel[count]);
			//��������
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
			//���� ����
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
			//���� �Ͻ�����
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
			//���� �ٽ����
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