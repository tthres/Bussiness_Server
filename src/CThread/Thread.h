#pragma once

#include <thread>
#include <map>
#include "Function/Function.h"
#include <mutex>
#include <condition_variable>

class CThread
{
public:
    CThread();
    ~CThread();
    CThread(const CThread&)           = delete;
    CThread operator=(const CThread&) = delete;

    template<typename _FUNCTION_, typename... _ARGS_>
    CThread(_FUNCTION_ func, _ARGS_... args) : m_function(new CFunction<_FUNCTION_, _ARGS_...>(func, args...))
    {
        m_bpaused = false;
        m_bStop   = false;
    }

    template<typename _FUNCTION_, typename... _ARGS_>
    int SetThreadFunc(_FUNCTION_ func, _ARGS_... args)
    {
        m_function = new CFunction<_FUNCTION_, _ARGS_...>(func, args...);
        if (!m_function)
            return -1;
        return 0;
    }

    int Start();

    int Pause();

    int Stop();

    bool isValid() const;

private:
    void ThreadRun();

private:
    CFunctionBase*          m_function;
    std::thread             m_thread; // 替换 pthread_t
    bool                    m_bpaused;
    bool                    m_bStop; // 安全停止标记
    std::mutex              m_mutex; // 锁
    std::condition_variable m_cv;    // 暂停/恢复
};