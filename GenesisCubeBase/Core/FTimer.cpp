//
// Created on 2023/11/12.
//

#include "FTimer.h"

namespace GenesisCube
{
	
	const double_t FTimer::TimeDilationMinimum = 1e-5;
	
	const double_t FTimer::TimeDilationMaximum = 1e+3;
	
	double_t FTimer::secondsPerCount = 1.0 / (double_t) QueryPerformanceFrequency();
	
	int64_t FTimer::QueryPerformanceFrequency()
	{
		int64_t countsPerSec = 0;
		::QueryPerformanceFrequency((LARGE_INTEGER *) &countsPerSec);
		return countsPerSec;
	}
	
	double_t FTimer::TotalTime() const
	{
		if (bIsStopped)
		{
			return double_t(stopTime - pausedTime - baseTime) * secondsPerCount;
		}
		else
		{
			return double_t(currTime - pausedTime - baseTime) * secondsPerCount;
		}
	}
	
	SYSTEMTIME FTimer::SystemTime()
	{
		SYSTEMTIME st;
		GetSystemTime(&st);
		return st;
	}
	
	SYSTEMTIME FTimer::LocalTime()
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		return st;
	}
	
	double_t FTimer::NowSecond()
	{
		int64_t curr = 0;
		::QueryPerformanceCounter((LARGE_INTEGER *) &curr);
		return (double_t) curr * secondsPerCount;
	}
	
	void FTimer::Reset()
	{
		int64_t curr = 0;
		::QueryPerformanceCounter((LARGE_INTEGER *) &curr);
		baseTime = curr;
		prevTime = curr;
		stopTime = 0;
		bIsStopped = false;
		lastCalculatorFpsTime = curr;
	}
	
	void FTimer::Start()
	{
		int64_t startTime = 0;
		::QueryPerformanceCounter((LARGE_INTEGER *) &startTime);
		
		if (bIsStopped)
		{
			pausedTime += (startTime - stopTime);
			
			prevTime = startTime;
			
			stopTime = 0;
			bIsStopped = false;
		}
		
	}
	
	void FTimer::Stop()
	{
		if (!bIsStopped)
		{
			int64_t curr = 0;
			::QueryPerformanceCounter((LARGE_INTEGER *) &curr);
			
			stopTime = curr;
			bIsStopped = true;
		}
	}
	
	void FTimer::Tick()
	{
		if (bIsStopped)
		{
			deltaTime = 0.0;
			return;
		}
		
		int64_t curr = 0;
		::QueryPerformanceCounter((LARGE_INTEGER *) &curr);
		currTime = curr;
		
		deltaTime = double_t(currTime - prevTime) * secondsPerCount * timeDilation;
		
		prevTime = currTime;
		
		// deltaTime有可能为负值，非暂停时期DeltaTime不应为0
		if (deltaTime < 1E-5)
		{
			deltaTime = 1E-5;
		}
		
		tickCount++;
		double_t calculatorFpsDeltaTime = double_t(currTime - lastCalculatorFpsTime) * secondsPerCount;
		if (calculatorFpsDeltaTime > 1.0)
		{
			fps = double_t(tickCount) / calculatorFpsDeltaTime;
			
			tickCount = 0;
			lastCalculatorFpsTime = currTime;
		}
		
		
	}
	
	void FTimer::SetTimeDilation(double_t value)
	{
		if (_isnan(value))
		{
			this->timeDilation = 1.0;
			return;
		}
		this->timeDilation = value < TimeDilationMinimum ? TimeDilationMinimum : (
			value > TimeDilationMaximum ? TimeDilationMaximum : value
		);
	}
	
	void FTimer::SleepThisThreadSeconds(int64_t time)
	{
		std::this_thread::sleep_for(std::chrono::seconds(time));
	}
	
	void FTimer::SleepThisThreadMilliseconds(int64_t time)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}
	
	void FTimer::SleepThisThreadMicroseconds(int64_t time)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(time));
	}
	
	void FTimer::SleepThisThreadNanoseconds(int64_t time)
	{
		std::this_thread::sleep_for(std::chrono::nanoseconds(time));
	}
	
}