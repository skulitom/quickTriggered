#include "Timer.h"

D3DAPPTIMER::D3DAPPTIMER(float timeScale)
{
	this->TimeScale = timeScale;
}

D3DAPPTIMER::~D3DAPPTIMER()
{

}

void D3DAPPTIMER::Tick()
{

	this->ComputeSecondsPerCount();
	this->ComputeCurrTime();
	/////////////////////////
	//TotalTime
	/////////////////////////
	if (this->IsInPause)
		this->PauseTime = this->CurrTime - this->StopTime + this->PrevPauseTime;
	
	this->TotalTime = ((this->CurrTime - this->BaseTime) - this->PauseTime) * this->SecondsPerCount;

	/////////////////////////
	//DeltaTime
	/////////////////////////
	this->DeltaTime = (this->CurrTime - this->PrevTime) * this->SecondsPerCount;

	this->PrevTime = this->CurrTime;

	/////////////////////////
	//fps
	/////////////////////////
	this->FrameCnt++;

	if ((this->TotalTime - this->TimeElapsed) >= 1.0f)
	{
		this->FPS = this->FrameCnt;
		this->TimeElapsed += 1.0f;
		this->FrameCnt = 0;
	}

}

void D3DAPPTIMER::Reset()
{
	this->ComputeCurrTime();
	this->BaseTime = this->CurrTime;
	this->PrevTime = this->CurrTime;
	this->StopTime = 0;
	this->PauseTime = 0;
	this->PrevPauseTime = 0;
	this->IsInPause = false;
	this->TimeElapsed = 0;
	this->FrameCnt = 0;
}

void D3DAPPTIMER::Resume()
{
	this->ComputeCurrTime();
	this->PauseTime = this->CurrTime - this->StopTime + this->PrevPauseTime;
	this->PrevPauseTime = this->PauseTime;
	this->IsInPause = false;
}

void D3DAPPTIMER::Stop()
{
	this->ComputeCurrTime();
	this->StopTime = this->CurrTime;
	this->IsInPause = true;
}

void D3DAPPTIMER::ComputeSecondsPerCount()
{

	QueryPerformanceFrequency((LARGE_INTEGER*)&this->CountsPerSecond);
	this->SecondsPerCount = 1.0 / (double)CountsPerSecond * TimeScale;

	//clock();
	//this->SecondsPerCount = 1.f / CLOCKS_PER_SEC * this->TimeScale;

}

float D3DAPPTIMER::GetPauseTime()
{

	this->ComputeSecondsPerCount();
	return this->PauseTime * this->SecondsPerCount;

}



