#ifndef MUTEX_H
#define MUTEX_H

#ifdef _WIN32
#include "stdafx.h"
#include <intrin.h>

#pragma once
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedCompareExchange)
#endif

class Mutex
{
public:
    enum LockState
    {
        LS_LOCK_IS_FREE = 0,
        LS_LOCK_IS_TAKEN = 1
    };

    Mutex() : m_spinLock(LS_LOCK_IS_FREE)
    {
    }

    ~Mutex()
    {
    }

#ifdef _WIN32
    void Lock()
    {
        while(_InterlockedCompareExchange(&m_spinLock, LS_LOCK_IS_TAKEN, LS_LOCK_IS_FREE));
    }

    void Unlock()
    {
        _InterlockedExchange(&m_spinLock, LS_LOCK_IS_FREE);
    }
#elif __linux
    void Lock()
    {
        while(__sync_val_compare_and_swap(&m_spinLock, LS_LOCK_IS_TAKEN, LS_LOCK_IS_FREE));
    }

    void Unlock()
    {
        __sync_lock_test_and_set(&m_spinLock, LS_LOCK_IS_FREE);
    }
#endif

    volatile long m_spinLock;
};

class MutexLock
{
public:
    MutexLock(Mutex* aLock)
        : m_lock(aLock)
    {
        m_lock->Lock();
    }

    MutexLock(Mutex& aLock)
        : m_lock(&aLock)
    {
        m_lock->Lock();
    }

    ~MutexLock()
    {
        m_lock->Unlock();
    }

    Mutex* m_lock;
};

#endif // MUTEX_H
