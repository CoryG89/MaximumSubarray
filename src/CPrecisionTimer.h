/**
 * This file is available open source under the GNU GPL v3 license from
 * a tool called gpufrustrum which does real-time frustrum culling and
 * uses this for a precision timer. (Simply a wrapper class for the 
 * performance counter functionality included in windows.h)
 *
 * The file can be obtained on the web here:
 * http://code.google.com/p/gpufrustum/source/browse/v2/test/LibTest/CPrecisionTimer.h
 **/

#ifndef _PRECISIONTIMER_H_
#define _PRECISIONTIMER_H_

#include <windows.h>

class CPrecisionTimer
{
  LARGE_INTEGER lFreq, lStart;

public:
  CPrecisionTimer()
  {
    QueryPerformanceFrequency(&lFreq);
  }

  inline void Start()
  {
    QueryPerformanceCounter(&lStart);
  }

  inline double Stop()
  {
    // Return duration in seconds...
    LARGE_INTEGER lEnd;
    QueryPerformanceCounter(&lEnd);
    return (double(lEnd.QuadPart - lStart.QuadPart) / lFreq.QuadPart);
  }
};

#endif // _PRECISIONTIMER_H_
