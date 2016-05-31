#ifndef D3DAPPTIMER_H
#define D3DAPPTIMER_H

#include <Windows.h>

// ������ 
class D3DAPPTIMER
{
public:

	D3DAPPTIMER(float TimeScale);
	~D3DAPPTIMER();

	// ��������� ������
	void Reset();
	// ��� ������� (������� ����)
	void Tick();
	// ��������� �������
	void Stop();
	// �������������
	void Resume();
	// ��������� �������� ������� (1.0f - ��������)
	void SetTimeScale(float TimeScalse);

	// ���������� ���������� ������ � �������
	int GetFPS();
	// ���������� ����� �����
	float GetPauseTime();
	// ���������� ����� �����(���� ������ ��������� �� � �����)
	float GetTotalTime();
	// ���������� ���������� ������ � �����
	float GetSecondsPerCount();
	// ���������� �������� �������
	float GetTimeScale();
	// ���������� (��������� ����� - ����� ����������� �����)
	float GetDeltaTime();
	// ���������� ��������� �����(�� � ��������!)
	__int64& GetCurrTime();

	// ����������: ������ �� �����?
	bool GetIsStoped();



private:
	// ��������� �����(�� � ��������!)
	__int64 mCurrTime;
	// ���������� �����(���������� ����)(�� � ��������!)
	__int64 mPrevTime;
	// ��������� ����� (�� � ��������!)
	__int64 mBaseTime;
	// ����� ��������� (�� � ��������!)
	__int64 mStopTime;
	// ����� � ����� (�� � ��������!)
	__int64 mPauseTime;
	// ����� � ���������� ����� (�� � ��������!)
	__int64 mPrevPauseTime;

	// ���������� ������ � �������
	int fps;
	// ���������� ��������� �������
	float mTimeScale;
	// ������ �����(��� ������� � �����)
	float mTotalTime;
	// ��������� ����� - ����� � ���������� �����
	float mDeltaTime;

private:

	int FrameCnt;
	float TimeElapsed;

	// ������ �� �����?
	bool mStoped;
};

#endif