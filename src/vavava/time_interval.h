#ifndef _TEST_TOOLS_TIME_INTERVAL_H_
#define _TEST_TOOLS_TIME_INTERVAL_H_

#ifdef _LINUX
#  include <sys/time.h>
#  include <unistd.h>
#else
#  include <wtypes.h>
#  include <time.h>
#endif

namespace testtools
{

#ifdef _LINUX

    class TimeInterval
    {
    public:
        TimeInterval()
        {
            Reset();
        }

        void Reset()
        {
            mLastTime = 0;
            mThisTime = 0;
            mLast     = this->GetTickCount();
        }

        void tick()
        {
            unsigned int nThis = this->GetTickCount();
            mInterval = nThis - mLast;
            mLast     = nThis;
            mLastTime = mThisTime;
            mThisTime = time(NULL);
        }

        unsigned int getfloatInterval() const
        {
            return mInterval;
        }

        float getfloatInterval() const
        {
            return float(mInterval) / 1000.f;
        }

        time_t getlasttime() const
        {
            return mLastTime;
        }

        time_t getthistime() const
        {
            return mThisTime;
        }

    protected:
        unsigned int GetTickCount()
        {
            timeBeginPeriod(1);
            unsigned int time = timeGetTime() + G_STARTTICKREF;
            timeEndPeriod(1);
            return time;
        }
    protected:
        unsigned int   mLast;
        unsigned int   mInterval;
        time_t         mLastTime;
        time_t         mThisTime;
    };


#else

    class TimeInterval
    {
    public:
        TimeInterval();
        double getfloatInterval();
        void tick();

    protected:
        long long GetMilliseconds();
        long long GetMicroseconds();
        void      Reset();

    private:
        long          mZeroClock;
        long long     mStartTick;
        long long     mLastTime;
        unsigned int  mTimerMask;

        LARGE_INTEGER mStartTime;
        LARGE_INTEGER mFrequency;

        long long     mLastIntervalBase;
        long long     mInterval;
    };

    inline TimeInterval::TimeInterval() : mTimerMask(0)
    {
        Reset();
    }
    inline double TimeInterval::getfloatInterval()
    {
        return mInterval / 1000.f;
    }
    inline void TimeInterval::tick()
    {
        long long tmp = GetMicroseconds();
        mInterval = tmp - mLastIntervalBase;
        mLastIntervalBase = tmp;
    }
    inline long long TimeInterval::GetMicroseconds()
    {
        return 1000 * GetMilliseconds();
    }
    inline long long TimeInterval::GetMilliseconds()
    {
        LARGE_INTEGER curTime;
        HANDLE thread = GetCurrentThread();
        DWORD oldMask = SetThreadAffinityMask(thread, mTimerMask);
        QueryPerformanceCounter(&curTime);
        SetThreadAffinityMask(thread, oldMask);
        long long newTime = curTime.QuadPart - mStartTime.QuadPart;
        unsigned long newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);
        unsigned long check = (unsigned long) (GetTickCount() - mStartTick);
        signed long msecOff = (signed long) (newTicks - check);
        if (msecOff <-100 || msecOff > 100)
        {
            long long adjust = std::min(msecOff * mFrequency.QuadPart / 1000, newTime - mLastTime);
            mStartTime.QuadPart += adjust;
            newTime -= adjust;
            newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);
        }
        mLastTime = newTime;
        return newTicks;
    }
    inline void TimeInterval::Reset()
    {
        long long procMask;
        long long sysMask;
        GetProcessAffinityMask(GetCurrentThread(), (PDWORD_PTR)&procMask, (PDWORD_PTR)&sysMask);
        if (procMask == 0)
        {
            procMask = 1;
        }

        if (mTimerMask == 0)
        {
            mTimerMask = 1;
            while((mTimerMask & procMask) == 0)
            {
                mTimerMask <<= 1;
            }
        }
        HANDLE thread = GetCurrentThread();
        DWORD oldMask = SetThreadAffinityMask(thread, mTimerMask);
        QueryPerformanceFrequency(&mFrequency);
        QueryPerformanceCounter(&mStartTime);
        mStartTick = GetTickCount();
        SetThreadAffinityMask(thread, oldMask);
        mLastTime = 0;
        mZeroClock = clock();

        mInterval = 0;
        mLastIntervalBase = 0;
    };
#endif

}


#endif // EOF _TEST_TOOLS_TIME_INTERVAL_H_