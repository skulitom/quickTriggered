#ifndef D3DAPPTIMER_H
#define D3DAPPTIMER_H

#include <Windows.h>

// Таймер 
class D3DAPPTIMER
{
public:

	D3DAPPTIMER(float TimeScale);
	~D3DAPPTIMER();

	// Отчистить таймер
	void Reset();
	// Шаг таймера (Главный цикл)
	void Tick();
	// Остановка таймера
	void Stop();
	// Возобновление
	void Resume();
	// Изменение скорости таймера (1.0f - стандарт)
	void SetTimeScale(float TimeScalse);

	// Возвращает количество кадров в секунде
	int GetFPS();
	// Возвращает время паузы
	float GetPauseTime();
	// Возвращает общее время(пока таймер находился не в паузе)
	float GetTotalTime();
	// Возвращает количество секунд в кадре
	float GetSecondsPerCount();
	// Возвращает скорость таймера
	float GetTimeScale();
	// Возвращает (настоящее время - время предыдущего кадра)
	float GetDeltaTime();
	// Возвращает настоящее время(не в секундах!)
	__int64& GetCurrTime();

	// Возвращает: Таймер на паузе?
	bool GetIsStoped();



private:
	// настоящее время(не в секундах!)
	__int64 mCurrTime;
	// предыдущее время(предыдущий кадр)(не в секундах!)
	__int64 mPrevTime;
	// Начальное время (не в секундах!)
	__int64 mBaseTime;
	// Время остановки (не в секундах!)
	__int64 mStopTime;
	// Время в паузе (не в секундах!)
	__int64 mPauseTime;
	// Время в предыдущей паузе (не в секундах!)
	__int64 mPrevPauseTime;

	// количество кадров в секунде
	int fps;
	// Коэфициент изменения времени
	float mTimeScale;
	// Полное время(без времени в паузе)
	float mTotalTime;
	// настоящее время - время в предыдущем кадре
	float mDeltaTime;

private:

	int FrameCnt;
	float TimeElapsed;

	// таймер на паузе?
	bool mStoped;
};

#endif