#pragma once

#define g_pSoundManager SoundManager::GetInstance()

#include "inc/fmod.hpp"
#pragma comment(lib,"lib/fmodex_vc.lib")	//lib 링크
using namespace FMOD;						//FMOD 네임스페이스 사용

//채널버퍼, 사운드버퍼
#define EXTRACHANNERBUFFER 5
#define SOUNDBUFFER 20
//총 사운드 버퍼 설정 : 버퍼서 작아서 씹히는 문제를 해결해주기 위함
#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNERBUFFER

class SoundManager
{
	SINGLETON(SoundManager)
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System* _system;			//fomd의 시스템 클래스
	Sound** _sound;				//fomd의 사운드 클래스
	Channel** _channel;			//fmod의 채널 클래스

	arrSounds _mTotalSounds;	//맵에 담긴 사운드 목록
public:	
	HRESULT Init(void);
	void Destroy(void);
	void Update();

	//사운드 추가(키값, 파일이름, BGM, 루프냐)
	void AddSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);
	
	//사운드 플레이(키값, 볼륨) 0.0f ~ 1.0f
	void Play(string keyName, float volume = 1.0f);
	//사운드 정지
	void Stop(string keyName);
	//사운드 일시정지
	void Pause(string keyName);
	//사운드 다시 재생
	void Resume(string keyName);
	void SetVolume(string keyName, float volume);


	bool IsPlaySound(string keyName);
	bool IsPauseSound(string keyName);
};

