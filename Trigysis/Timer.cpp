#include "Timer.h"

D3DAPPTIMER::D3DAPPTIMER(float TimeScale)
{
	mTimeScale = TimeScale;
}

D3DAPPTIMER::~D3DAPPTIMER()
{

}

void D3DAPPTIMER::Tick()
{
	//__int64 CurrTime = GetCurrTime();

	/////////////////////////
	//TotalTime
	/////////////////////////


	if (mStoped)
	{
		mPauseTime = GetCurrTime() - mStopTime + mPrevPauseTime;
	}

	mTotalTime = ((GetCurrTime() - mBaseTime) - mPauseTime) * GetSecondsPerCount();

	/////////////////////////
	//DeltaTime
	/////////////////////////

	mDeltaTime = GetCurrTime() * this->GetSecondsPerCount() - mPrevTime * this->GetSecondsPerCount();

	mPrevTime = GetCurrTime();

	/////////////////////////
	//fps
	/////////////////////////

	this->FrameCnt++;

	if ((mTotalTime - this->TimeElapsed) >= 1.0f)
	{
		fps = this->FrameCnt;
		this->TimeElapsed += 1.0f;
		this->FrameCnt = 0;
	}

}

void D3DAPPTIMER::Reset()
{
	_int64 CurrTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&CurrTime);
	mBaseTime = CurrTime;
	mPrevTime = CurrTime;
	mStopTime = 0;
	mPauseTime = NULL;
	mPrevPauseTime = NULL;
	mStoped = false;
	this->TimeElapsed = 0;
	this->FrameCnt = 0;
}

void D3DAPPTIMER::Resume()
{
	mPauseTime = GetCurrTime() - mStopTime + mPrevPauseTime;
	mPrevPauseTime = mPauseTime;
	mStoped = false;
}

void D3DAPPTIMER::Stop()
{
	mStopTime = GetCurrTime();
	mStoped = true;
}

void D3DAPPTIMER::SetTimeScale(float TimeScale)
{
	mTimeScale = TimeScale;
}

int D3DAPPTIMER::GetFPS()
{
	return fps;
}

float D3DAPPTIMER::GetPauseTime()
{
	return mPauseTime * GetSecondsPerCount();
}

float D3DAPPTIMER::GetTotalTime()
{
	return mTotalTime;
}

float D3DAPPTIMER::GetTimeScale()
{
	return mTimeScale;
}

float D3DAPPTIMER::GetSecondsPerCount()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&this->CountsPerSecond);
	return 1.0 / (double)CountsPerSecond * mTimeScale;
}

float D3DAPPTIMER::GetDeltaTime()
{
	return mDeltaTime;
}

__int64& D3DAPPTIMER::GetCurrTime()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&this->CurrTime);
	return CurrTime;
}

bool D3DAPPTIMER::GetIsStoped()
{
	return mStoped;
}


