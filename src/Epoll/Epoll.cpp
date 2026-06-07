#pragma once
#include <sys/epoll.h>
#include <vector>

using EPEvents = std::vector<epoll_event>;

class EpollData
{
public:
    EpollData() { m_data.u64 = 0; }
    EpollData(void* ptr) { m_data.ptr = ptr; }

    explicit EpollData(int fd) { m_data.fd = fd; }
    explicit EpollData(uint32_t u32) { m_data.u32 = u32; }
    explicit EpollData(uint64_t u64) { m_data.u64 = u64; }
    EpollData(const EpollData& data) { m_data.u64 = data.m_data.u64; }

public:
    EpollData& operator=(const EpollData& data)
    {
        if (this != &data)
            m_data.u64 = data.m_data.u64;
        return *this;
    }
    EpollData& operator=(void* data)
    {
        m_data.ptr = data;
        return *this;
    }
    EpollData& operator=(int data)
    {
        m_data.fd = data;
        return *this;
    }
    EpollData& operator=(uint32_t data)
    {
        m_data.u32 = data;
        return *this;
    }
    EpollData& operator=(uint64_t data)
    {
        m_data.u64 = data;
        return *this;
    }
    operator epoll_data_t() { return m_data; }
    operator epoll_data_t() const { return m_data; }
    operator epoll_data_t*() { return &m_data; }
    operator const epoll_data_t*() const { return &m_data; }
private:
    epoll_data_t m_data;
};

class CEpoll
{
};