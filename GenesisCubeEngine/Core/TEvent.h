//
// Created by admin on 2023/12/19.
//

#pragma once

#include "GenesisCubeEngine.h"

namespace GenesisCubeEngine
{
    ///
    /// 事件类
    ///
    template<class...Args>
    class TEvent
    {
    public:
        
        ///
        /// 事件的观察者。各个观察者之间不应该有顺序，不应该耦合。
        ///
        typedef void(*Observer)(Args...);
    
    public:
        
        TEvent();
        
        explicit TEvent(std::initializer_list<Observer> observers);
        
        explicit TEvent(Observer observer);
        
        ~TEvent();
    
    public:
        
        /// 
        /// 添加观察者
        /// 
        /// \param observer 观察者
        void operator+=(Observer observer);
        
        /// 
        /// 删除观察者
        /// 
        /// \param  observer 观察者
        void operator-=(Observer observer);
        
        /// 
        /// 触发事件
        /// 
        /// \param  args 参数
        void Trigger(Args... args) const;
    
    private:
        
        std::vector<Observer> observers;
        
    };
    
    template<class... Args>
    TEvent<Args...>::TEvent(std::initializer_list<Observer> observers)
        : observers(observers)
    {
    
    }
    
    template<class... Args>
    void TEvent<Args...>::Trigger(Args... args) const
    {
        for (auto *observer: observers)
        {
            observer(args...);
        }
    }
    
    template<class... Args>
    void TEvent<Args...>::operator-=(TEvent::Observer const observer)
    {
        this->observers.erase(std::find(this->observers.begin(), this->observers.end(), observer));
    }
    
    template<class... Args>
    void TEvent<Args...>::operator+=(TEvent::Observer const observer)
    {
        this->observers.push_back(observer);
    }
    
    template<class... Args>
    TEvent<Args...>::TEvent() = default;
    
    template<class... Args>
    TEvent<Args...>::TEvent(const Observer observer)
    {
        observers.push_back(observer);
    }
    
    template<class... Args>
    TEvent<Args...>::~TEvent() = default;
    
} // GenesisCubeEngine
