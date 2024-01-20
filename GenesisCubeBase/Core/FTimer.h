//
// Created on 2023/11/12.
//

#pragma once

#include "Header.h"
#include "FCore.h"

namespace GenesisCube
{
	
	///
	/// 计时器
	///
	class FTimer
	{
	public:
		
		inline FTimer() { Reset(); }
		
		inline ~FTimer() = default;
	
	public:
		
		///
		/// 获取硬件支持的最大计数器频率
		///
		/// \return 频率（以每秒计数为单位）
		static int64_t QueryPerformanceFrequency();
		
		///
		/// 获取现在的系统时间
		///
		/// \return
		static SYSTEMTIME SystemTime();
		
		///
		/// 获取现在的地区时间
		///
		/// \return
		static SYSTEMTIME LocalTime();
		
		///
		/// 获取现在的时间
		///
		/// \return 单位：秒
		static double NowSecond();
		
		///
		/// 暂停当前线程
		/// \param time 单位：秒
		static void SleepThisThreadSeconds(int64_t time);
		
		///
		/// 暂停当前线程
		/// \param time 单位：毫秒
		static void SleepThisThreadMilliseconds(int64_t time);
		
		///
		/// 暂停当前线程
		/// \param time 单位：微秒
		static void SleepThisThreadMicroseconds(int64_t time);
		
		///
		/// 暂停当前线程
		/// \param time 单位：纳秒
		static void SleepThisThreadNanoseconds(int64_t time);
		
		///
		/// 重置
		///
		void Reset();
		
		///
		/// 解除暂停
		///
		void Start();
		
		///
		/// 暂停
		///
		void Stop();
		
		///
		/// 每帧调用
		///
		void Tick();
		
		///
		/// 获取从开始到上一次调用Tick的时间
		///
		/// \return 单位：秒
		[[nodiscard]]
		double TotalTime() const;
		
		///
		/// 设置时间膨胀倍数（仅对DeltaTime()有影响）
		///
		/// \param value 时间膨胀倍数。小于1.0为减速，大于1.0为加速。
		void SetTimeDilation(double value);
	
	public:
		
		///
		/// 时间膨胀最小值
		///
		static const double TimeDilationMinimum;
		
		///
		/// 时间膨胀最大值
		///
		static const double TimeDilationMaximum;
	
	private:
		
		static double secondsPerCount;
	
	public:
		
		///
		/// 获取时间膨胀倍数
		///
		/// \return 时间膨胀倍数
		[[nodiscard]]
		inline double GetTimeDilation() const noexcept { return this->timeDilation; }
		
		///
		/// 获取帧间隔时间
		///
		/// \return 单位：秒
		[[nodiscard]]
		inline double GetDeltaTime() const noexcept { return this->deltaTime; }
		
		///
		/// 获取帧率
		///
		/// \return 帧率
		[[nodiscard]]
		inline double GetFps() const noexcept { return this->fps; }
		
		///
		/// 是否已经暂停
		///
		/// \return 是否已经暂停
		[[nodiscard]]
		inline bool IsStop() const noexcept { return bIsStopped; }
	
	private:
		
		double deltaTime = 0.0;
		double fps = 0.0;
		double timeDilation = 1.0;
		
		int64_t baseTime = 0;
		int64_t pausedTime = 0;
		int64_t stopTime = 0;
		int64_t prevTime = 0;
		int64_t currTime = 0;
		
		int64_t lastCalculatorFpsTime = 0;
		int64_t tickCount = 0;
		
		bool bIsStopped = false;
		
	};
	
}

namespace std
{
	template<>
	struct formatter<SYSTEMTIME, GenesisCube::TChar> : formatter<WORD, GenesisCube::TChar>
	{
		template<class C>
		constexpr auto format(const SYSTEMTIME &systemTime, C &context)
		{
			typename C::iterator Ite = formatter<WORD, GenesisCube::TChar>::format(systemTime.wYear, context);
			Ite = TEXT('-');
			Ite = formatter<WORD, GenesisCube::TChar>::format(systemTime.wMonth, context);
			Ite = TEXT('-');
			Ite = formatter<WORD, GenesisCube::TChar>::format(systemTime.wDay, context);
			Ite = TEXT(' ');
			Ite = formatter<WORD, GenesisCube::TChar>::format(systemTime.wHour, context);
			Ite = TEXT(':');
			Ite = formatter<WORD, GenesisCube::TChar>::format(systemTime.wMinute, context);
			Ite = TEXT(':');
			Ite = formatter<WORD, GenesisCube::TChar>::format(systemTime.wSecond, context);
			Ite = TEXT('.');
			Ite = formatter<WORD, GenesisCube::TChar>::format(systemTime.wMilliseconds, context);
			return Ite;
		}
	};
}
