#ifndef SOUND_H
#define SOUND_H

#include <Windows.h>
#include <map>
#include <string>

#include "DXInclude\dsound.h"

#include "Files.h"

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


#define SLIMIT(x,floor,ceil) ((x < floor) ? floor : ((x > ceil) ? ceil : x))

struct WaveStruct
{
	char ChunkId[4]; //4
	char ChunkSize[4]; //4
	char Format[4]; //4
	char SubChunk1Id[4]; //4
	__int32 SubChunk1Size; //4
	__int16 AudioFormat; //2
	__int16 NumChannels; //2
	__int32 SampleRate; //4
	__int32 ByteRate; //4
	__int16 BlockAlign; //2
	__int16 BitsPerSample; //2
	char SubChunk2Id[4]; //4
	__int32 SubChunk2Size; //4
	//44...

};

class SoundBasic
{

public:

	SoundBasic(HWND* hwnd);
	~SoundBasic();

	bool LoadSounds(std::string& path, std::vector<std::string>** files = nullptr);
	bool Init();

	bool Play(std::string& soundName, __int16 volume, bool isLooping = false, DWORD pos = 0);
	bool Play(IDirectSoundBuffer8* ptrSound, __int16 volume, bool isLooping = false, DWORD pos = 0);

	bool Stop(std::string& soundName);
	bool Stop(IDirectSoundBuffer8* ptrSound);

	bool SetVolume(std::string& soundName, __int32 volume);
	bool SetVolume(IDirectSoundBuffer8* ptrSound, __int32 volume);

	bool GetIsPlaying(IDirectSoundBuffer8* ptrSound);

	__int16 GetVolume(std::string& soundName);
	__int16 GetVolume(IDirectSoundBuffer8* ptrSound);

	bool GetError() { return this->Error; }

	IDirectSoundBuffer8* GetSound(std::string& soundName) { return this->FindSound(soundName); }

private:

	IDirectSoundBuffer8* FindSound(std::string& soundName);
	bool InitSound(std::string& fileName);
	__int32 VolumeToBStandart(__int16 volume) { return DSBVOLUME_MIN + SLIMIT(volume, 0, 100) * (100); }
	__int16 BStandartToVolume(__int32 bsVolume) { return (bsVolume - DSBVOLUME_MIN) / 100.f; }

private:

	FileManager* FManager;
	WaveStruct WStruct;

	IDirectSound8* Sound;
	IDirectSoundBuffer* SoundBuffer;

	HWND* HWnd;

	std::map<std::string, IDirectSoundBuffer8*> SoundList;
	std::string Path;

	bool Error;

};

#endif //!SOUND_H