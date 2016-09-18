#include "Sound.h"

SoundBasic::SoundBasic(HWND* hwnd)
{
	this->HWnd = hwnd;

	this->Error = (this->Init() ? false : true);

}

SoundBasic::~SoundBasic()
{
	if (this->SoundBuffer)
		this->SoundBuffer->Release();

	if (this->Sound)
		this->Sound->Release();

	if (this->FManager)
		delete this->FManager;

	this->SoundList.clear();

}

bool SoundBasic::LoadSounds(std::string& path, std::vector<std::string>** files)
{

	if (this->Error)
		return false;

	this->Path = path;

	if (!this->Path.size())
	{
		return false;
	}

	bool Success = false;

	std::vector<std::string>* Files = new std::vector<std::string>;
	*Files = FileHelp::FindFiles(std::string(this->Path) + "\\*.wav");

	if (!Files->size())
		return true;

	for (int i = 0; i < Files->size(); i++)
	{
		Success = (this->InitSound(Files->at(i)) ? true : Success);
	}

	this->Error = Success ? false : true;
	if (Success)
	{
		if (*files)
			*files = Files;
		else
			delete Files;

		return true;
	}
	
	delete Files;

}

bool SoundBasic::Init()
{

	DSBUFFERDESC BD;
	WAVEFORMATEX WaveFormat;

	HRESULT HR = S_OK;

	HR = DirectSoundCreate8(NULL, &this->Sound, NULL);
	if (FAILED(HR))
	{
		return false;
	}

	HR = this->Sound->SetCooperativeLevel( this->HWnd ? *this->HWnd : nullptr, DSSCL_PRIORITY);

	if (FAILED(HR))
	{
		return false;
	}

	BD.dwSize = sizeof(DSBUFFERDESC);
	BD.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	BD.dwBufferBytes = 0;
	BD.dwReserved = 0;
	BD.lpwfxFormat = NULL;
	BD.guid3DAlgorithm = GUID_NULL;

	HR = this->Sound->CreateSoundBuffer(&BD, &this->SoundBuffer, NULL);
	if (FAILED(HR))
	{
		return false;
	}

	WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
	WaveFormat.nSamplesPerSec = 44100;
	WaveFormat.wBitsPerSample = 16;
	WaveFormat.nChannels = 2;
	WaveFormat.nBlockAlign = (WaveFormat.wBitsPerSample / 8)*WaveFormat.nChannels;
	WaveFormat.nAvgBytesPerSec = WaveFormat.nSamplesPerSec * WaveFormat.nBlockAlign;
	WaveFormat.cbSize = 0;

	HR = this->SoundBuffer->SetFormat(&WaveFormat);
	if (FAILED(HR))
	{
		return false;
	}

	return true;

}

bool SoundBasic::InitSound(std::string& fileName)
{

	if (this->SoundList.count(fileName))
		return true;

	FILE* PFile;

	DSBUFFERDESC BD;
	WAVEFORMATEX WaveFormat;
	IDirectSoundBuffer* TBuffer = nullptr;
	IDirectSoundBuffer8* NewSBuffer = nullptr;
	unsigned char* WaveData;
	unsigned char* PBuffer;
	unsigned long BufferSize;

	std::string TStr = std::string(this->Path) + "\\" +std::string(fileName);
	const char* FullFName = TStr.c_str();

	HRESULT HR = S_OK;

	if (fopen_s(&PFile, FullFName, "rb"))
	{
		return false;
	}
	if (fread(&this->WStruct, sizeof(WaveStruct), 1, PFile) != 1)
	{
		return false;
	}

	if (this->WStruct.ChunkId[0] != 'R' || this->WStruct.ChunkId[1] != 'I' ||
		this->WStruct.ChunkId[2] != 'F' || this->WStruct.ChunkId[3] != 'F')
	{
		return false;
	}

	if (this->WStruct.Format[0] != 'W' || this->WStruct.Format[1] != 'A' ||
		this->WStruct.Format[2] != 'V' || this->WStruct.Format[3] != 'E')
	{
		return false;
	}

	if (this->WStruct.SubChunk1Id[0] != 'f' || this->WStruct.SubChunk1Id[1] != 'm' ||
		this->WStruct.SubChunk1Id[2] != 't')
	{
		return false;
	}

	if (this->WStruct.AudioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}

	if (this->WStruct.SampleRate != 44100)
	{
		return false;
	}

	if (this->WStruct.BitsPerSample != 16)
	{
		return false;
	}

	if (this->WStruct.SubChunk2Id[0] != 'd' || this->WStruct.SubChunk2Id[1] != 'a' ||
		this->WStruct.SubChunk2Id[2] != 't' || this->WStruct.SubChunk2Id[3] != 'a')
	{
		return false;
	}

	if (this->WStruct.NumChannels != 2)
	{
		return false;
	}

	WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
	WaveFormat.nSamplesPerSec = 44100;
	WaveFormat.wBitsPerSample = 16;
	WaveFormat.nChannels = 2;
	WaveFormat.nBlockAlign = (WaveFormat.wBitsPerSample / 8) * WaveFormat.nChannels;
	WaveFormat.nAvgBytesPerSec = WaveFormat.nSamplesPerSec * WaveFormat.nBlockAlign;
	WaveFormat.cbSize = 0;

	BD.dwSize = sizeof(DSBUFFERDESC);
	BD.dwFlags = DSBCAPS_CTRLVOLUME;
	BD.dwBufferBytes = this->WStruct.SubChunk2Size;
	BD.dwReserved = 0;
	BD.lpwfxFormat = &WaveFormat;
	BD.guid3DAlgorithm = GUID_NULL;

	HR = this->Sound->CreateSoundBuffer(&BD, &TBuffer, NULL);
	if (FAILED(HR))
	{
		return false;
	}

	HR = TBuffer->QueryInterface(IID_IDirectSoundBuffer8,
		(void**)&NewSBuffer);
	if (FAILED(HR))
	{
		return false;
	}

	TBuffer->Release();
	TBuffer = nullptr;

	fseek(PFile, sizeof(WaveStruct), SEEK_SET);
	WaveData = new unsigned char[this->WStruct.SubChunk2Size];
	if (!WaveData)
	{
		return false;
	}
	if (fread(WaveData, 1, this->WStruct.SubChunk2Size, PFile) != this->WStruct.SubChunk2Size)
	{
		return false;
	}

	if (fclose(PFile))
	{
		return false;
	}

	HR = NewSBuffer->Lock(0, this->WStruct.SubChunk2Size,
		(void**)&PBuffer, (DWORD*)&BufferSize, NULL, 0, 0);
	if (FAILED(HR))
	{
		return false;
	}

	memcpy(PBuffer, WaveData, this->WStruct.SubChunk2Size);

	HR = NewSBuffer->Unlock((void*)PBuffer, BufferSize, NULL, 0);
	if (FAILED(HR))
	{
		return false;
	}

	delete[] WaveData;
	WaveData = 0;

	this->SoundList.insert(std::pair<std::string, IDirectSoundBuffer8*>(fileName, NewSBuffer));

	return true;

}

IDirectSoundBuffer8* SoundBasic::FindSound(std::string& soundName)
{

	if (!soundName.size())
		return nullptr;

	auto It = this->SoundList.find(soundName);
	if (It != std::end(this->SoundList))
	{
		return It->second;
	}
	return nullptr;

}

bool SoundBasic::Play(std::string& soundName, __int16 volume, bool isLooping, DWORD pos)
{

	IDirectSoundBuffer8* CBuffer = this->FindSound(soundName);
	if (!CBuffer || this->Error)
		return false;

	return this->Play(CBuffer, volume, isLooping, pos);

}

bool SoundBasic::Play(IDirectSoundBuffer8* ptrSound, __int16 volume, bool isLooping, DWORD pos)
{

	HRESULT HR = S_OK;

	HR = ptrSound->SetCurrentPosition(pos);
	if (FAILED(HR))
	{
		return false;
	}

	HR = ptrSound->SetVolume(this->VolumeToBStandart(volume));
	if (FAILED(HR))
	{
		return false;
	}

	HR = ptrSound->Play(0, 0, isLooping ? DSBPLAY_LOOPING : 0);
	if (FAILED(HR))
	{
		return false;
	}

	return true;

}

bool SoundBasic::Stop(std::string& soundName)
{


	IDirectSoundBuffer8* CBuffer = this->FindSound(soundName);
	if (!CBuffer || this->Error)
		return false;

	this->Stop(CBuffer);

}

bool SoundBasic::Stop(IDirectSoundBuffer8* ptrSound)
{

	HRESULT HR = S_OK;
	HR = ptrSound->Stop();
	if (FAILED(HR))
	{
		return false;
	}

	return true;

}

bool SoundBasic::SetVolume(IDirectSoundBuffer8* ptrSound, __int32 volume)
{

	HRESULT HR = S_OK;
	
	HR = ptrSound->SetVolume(this->VolumeToBStandart(volume));
	if (FAILED(HR))
	{
		return false;
	}

	return true;

}

bool SoundBasic::SetVolume(std::string& soundName, __int32 volume)
{

	IDirectSoundBuffer8* CBuffer = this->FindSound(soundName);
	if (!CBuffer || this->Error)
		return false;

	return this->SetVolume(CBuffer, volume);

}

__int16 SoundBasic::GetVolume(IDirectSoundBuffer8* ptrSound)
{

	HRESULT HR = S_OK;
	LONG Volume;
	HR = ptrSound->GetVolume(&Volume);
	if (FAILED(HR))
	{
		return -1;
	}

	return this->BStandartToVolume(Volume);

}

__int16 SoundBasic::GetVolume(std::string& soundName)
{

	IDirectSoundBuffer8* CBuffer = this->FindSound(soundName);
	if (!CBuffer || this->Error)
		return -1;

	return this->GetVolume(CBuffer);

}

bool SoundBasic::GetIsPlaying(IDirectSoundBuffer8* ptrSound)
{

	if (!ptrSound)
		return false;

	DWORD Status;

	ptrSound->GetStatus(&Status);
	return (Status & DSBSTATUS_PLAYING) ? true : false;

}
