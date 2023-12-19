//
// Created on 2023/11/12.
//

#pragma once

#include "GenesisCubeEngine.h"

namespace GenesisCubeEngine
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
        static double_t NowSecond();
        
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
        double_t TotalTime() const;
        
        ///
        /// 设置时间膨胀倍数（仅对DeltaTime()有影响）
        ///
        /// \param value 时间膨胀倍数。小于1.0为减速，大于1.0为加速。
        void SetTimeDilation(double_t value);
    
    public:
        
        ///
        /// 时间膨胀最小值
        ///
        static const double_t TimeDilationMinimum;
        
        ///
        /// 时间膨胀最大值
        ///
        static const double_t TimeDilationMaximum;
    
    private:
        
        static double_t secondsPerCount;
    
    public:
        
        ///
        /// 获取时间膨胀倍数
        ///
        /// \return 时间膨胀倍数
        inline double_t GetTimeDilation() const noexcept { return this->timeDilation; }
        
        ///
        /// 获取帧间隔时间
        ///
        /// \return 单位：秒
        inline double_t GetDeltaTime() const noexcept { return this->deltaTime; }
        
        ///
        /// 获取帧率
        ///
        /// \return 帧率
        inline double_t GetFps() const noexcept { return this->fps; }
        
        ///
        /// 是否已经暂停
        ///
        /// \return 是否已经暂停
        inline bool IsStop() const noexcept { return bIsStopped; }
    
    private:
        
        double_t deltaTime = 0.0;
        double_t fps = 0.0;
        double_t timeDilation = 1.0;
        
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
