#ifndef SOUNDENGINE_H_
#define SOUNDENGINE_H_

#include"Sound.h"
class SoundEngine
{
	SoundClass *sound;
	HWND hwnd;
public:
	bool On;
	SoundEngine()
	{
		On = true;
		sound = new SoundClass();
	}
	void SetWindowHandler(HWND hwnd)
	{
		this->hwnd = hwnd;
	}
	void StartBackMusic(char* path)
	{
		if(On)
		PlaySound(charToWChar(path),NULL, SND_ASYNC );
	}
	void PlayShortSound(char* path)
	{
		 if(On)
			sound->Initialize(hwnd,path);
	}
private:
	wchar_t* charToWChar(const char* text)
	{
		size_t size = strlen(text) + 1;
		wchar_t* wa = new wchar_t[size];
		mbstowcs(wa,text,size);
		return wa;
	}
};
#endif