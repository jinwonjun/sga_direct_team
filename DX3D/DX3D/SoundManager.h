#pragma once

#include "inc/fmod.hpp"
#pragma comment(lib,"lib/fmodex_vc.lib")	//lib ��ũ
using namespace FMOD;	//FMOD ���ӽ����̽� ���

#define g_pSoundManager SoundManager::GetInstance()

//ä�ι���, �������
#define EXTRACHANNERBUFFER 5
#define SOUNDBUFFER 20
//�� ���� ���� ���� : ���ۼ� �۾Ƽ� ������ ������ �ذ����ֱ� ����
#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNERBUFFER

class SoundManager
{
	SINGLETON(SoundManager)
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System*		m_system;		//fomd�� ����̽� ������
	Sound**		m_sound;		//���� ���� ���� ��ü
	Channel**	m_channel;		//���� ����Ǵ� ����

	arrSounds	m_mapSounds;	//��� ���� ���

public:	
	HRESULT Init(void);
	void Destroy(void);
	void Update();

	//���� �߰�(Ű��, �����̸�, BGM, ����)
	void AddSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);
	
	//���� �÷���(Ű��, ����) 0.0f ~ 1.0f
	void Play(string keyName, float volume = 1.0f);
	//���� ����
	void Stop(string keyName);
	//���� �Ͻ�����
	void Pause(string keyName);
	//���� �ٽ� ���
	void Resume(string keyName);

	bool IsPlaySound(string keyName);
	bool IsPauseSound(string keyName);

	void VolumeUp(string keyName, const float volume);
	void VolumeDown(string keyName, const float volume);
};

