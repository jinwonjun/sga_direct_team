#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() : _system(NULL), _channel(NULL), _sound(NULL)
{
}

SoundManager::~SoundManager()
{
}


HRESULT SoundManager::Init(void)
{
	//���� �ý��� ����
	System_Create(&_system);

	//maxchannels : fmod ���� ����ϴ� �ִ� ä���� ���� ����
	//���� ä�� �� ����
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//����, ä�� �����Ҵ�
	_sound = new Sound *[TOTALSOUNDBUFFER];
	_channel = new Channel *[TOTALSOUNDBUFFER];

	//�޸� �ʱ�ȭ
	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_sound, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));


	return S_OK;
}

void SoundManager::Destroy(void)
{
	//���� �� ä�� ����
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != NULL)
			{
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	//�޸� �����
	SAFE_DELETE(_channel);
	SAFE_DELETE(_sound);

	//�ý��� �ݱ�
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}

}

void SoundManager::Update()
{
	/*
	���� �ý����� ��� ������Ʈ �ؿ��� ������ �ٲ�ų�
	����� ���� ���带 ä�ο��� ������ �� �پ��� �۾��� �ڵ����� ���ش�.
	*/
	//���ΰ��ӿ��� ���� �Ŵ����� ������Ʈ ���ش�.
	_system->update();
}

void SoundManager::AddSound(string keyName, string soundName, bool bgm, bool loop)
{
	//������ ������
	if (loop)
	{
		//bgm
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		//����Ʈ
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	//�����ȵ��� ����Ʈ
	else
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	//�ʿ� ���带 Ű���� �Բ� ����ش�.
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void SoundManager::Play(string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷���
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
			//��������
			_channel[count]->setVolume(volume);
		}
	}
}

void SoundManager::Stop(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			_channel[count]->stop();
			break;
		}
	}
}

void SoundManager::Pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �Ͻ�����
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::Resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �ٽ����
			_channel[count]->setPaused(false);
			break;
		}
	}
}

void SoundManager::SetVolume(string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setVolume(volume);
		}
	}
}

bool SoundManager::IsPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//�÷��� ���̳�?
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool SoundManager::IsPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//�÷��� ���̳�? (�Ͻ�����)
			_channel[count]->isPlaying(&isPause);
			break;
		}
	}

	return isPause;
}
