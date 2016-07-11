#ifndef D3DAPPTIMER_H
#define D3DAPPTIMER_H

#include <Windows.h>

class D3DAPPTIMER
{
public:

	D3DAPPTIMER(float timeScale);
	~D3DAPPTIMER();

	// Reset Timer
	void Reset();
	
	// Update Timer
	// Must be executed every cycle
	void Tick();
	
	void Stop();
	void Resume();
	
	// Change Timer Speed
	// TimeScale = 1.f - default
	void SetTimeScale(float timeScale) { TimeScale = timeScale; }

	// Return Fraps(cycles) per second
	int GetFPS(){ return FPS; }
	// Return Pause Time
	float GetPauseTime();
	// Return non-Pause Time
	float GetTotalTime() { return this->TotalTime; }
	
	float GetSecondsPerCount() { return this->SecondsPerCount; }
	void ComputeSecondsPerCount();
	
	float GetTimeScale() { return this->TimeScale; }
	
	//Return seconds in one cycle
	float GetDeltaTime() { return this->DeltaTime; }
	
	void ComputeCurrTime() { QueryPerformanceCounter((LARGE_INTEGER*)&this->CurrTime); }
	
	//Return Time (Processor cycles) 
	__int64& GetCurrTime() { return this->CurrTime; }

	
	bool GetIsStoped() { return this->IsInPause; }



private:

	///////////////////////////////////
	//**Processor Counts
	///////////////////////////////////
	// Current Time
	__int64 CurrTime;
	// Previous Time
	__int64 PrevTime;
	// Start Time
	__int64 BaseTime;
	// Stop Time
	__int64 StopTime;
	// In Pause Time
	__int64 PauseTime;
	// In Previuos Pause Time
	__int64 PrevPauseTime;

	__int64 CountsPerSecond;
	double SecondsPerCount;

	///////////////////////////////////
	//**Non-Processor Counts
	///////////////////////////////////
	int FPS;
	
	float TimeScale;
	// non-Pause Time
	float TotalTime;
	
	float DeltaTime;

private:

	int FrameCnt;
	float TimeElapsed;

	bool IsInPause;
};

#endif