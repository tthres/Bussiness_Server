#include "Thread.h"
#include <stdio.h>

CThread::CThread()
{
    m_function = nullptr;
    m_bpaused  = false;
    m_bStop    = false;
}

CThread::~CThread()
{
    Stop();
}

int CThread::Start()
{
    if (m_thread.joinable() || !m_function)
        return -1;

    m_bStop   = false;
    m_bpaused = false;

    // 一行代替 pthread 全套
    m_thread = std::thread(&CThread::ThreadRun, this);
    return 0;
}

int CThread::Pause()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_thread.joinable())
        return -1;

    m_bpaused = !m_bpaused;
    if (!m_bpaused)
        m_cv.notify_one();

    return 0;
}

int CThread::Stop()
{
    if (!m_thread.joinable())
        return 0;

    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_bStop   = true;
        m_bpaused = false;
    }
    m_cv.notify_all();

    if (m_thread.joinable())
        m_thread.join();

    return 0;
}

bool CThread::isValid() const
{
    return m_thread.joinable();
}

void CThread::ThreadRun()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        // 暂停：等待唤醒
        m_cv.wait(lock, [this]() { return !m_bpaused || m_bStop; });

        if (m_bStop)
            break;

        // 执行用户函数
        auto func = m_function;
        lock.unlock();

        if (func)
        {
            int ret = (*func)();
            if (ret != 0)
            {
                printf("%s(%d):[%s]ret = %d\n", __FILE__, __LINE__, __FUNCTION__, ret);
            }
        }
    }
}
