#ifdef __GNUC__
#include <stdint.h>
typedef int64_t TimeVal;
#else
typedef __int64 TimeVal;
#endif

TimeVal getPerfTime();
int getPerfDeltaTimeUsec(const TimeVal start, const TimeVal end);


#if defined(WIN32)

// Win32
#include <windows.h>

TimeVal getPerfTime()
{
    __int64 count;
    QueryPerformanceCounter((LARGE_INTEGER*)&count);
    return count;
}

int getPerfDeltaTimeUsec(const TimeVal start, const TimeVal end)
{
    static __int64 freq = 0;
    if (freq == 0)
        QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    __int64 elapsed = end - start;
    return (int)(elapsed*1000000 / freq);
}

#else

// Linux, BSD, OSX

#include <sys/time.h>

TimeVal getPerfTime()
{
    timeval now;
    gettimeofday(&now, 0);
    return (TimeVal)now.tv_sec*1000000L + (TimeVal)now.tv_usec;
}

int getPerfDeltaTimeUsec(const TimeVal start, const TimeVal end)
{
    return (int)(end - start);
}

#endif
