#include "platform.h"

//needed for controlling framerate
struct			 											// Create A Structure For The Timer Information
{
  __int64       frequency;									// Timer Frequency
  float         resolution;									// Timer Resolution
  unsigned long mm_timer_start;								// Multimedia Timer Start Value
  unsigned long mm_timer_elapsed;							// Multimedia Timer Elapsed Time
  bool			performance_timer;							// Using The Performance Timer?
  __int64       performance_timer_start;					// Performance Timer Start Value
  __int64       performance_timer_elapsed;					// Performance Timer Elapsed Time
} timer;													// Structure Is Named timer

int		steps[6]={ 1, 2, 4, 5, 10, 20 };					// Stepping Values For Slow Video Adjustment


void TimerInit(void)										// Initialize Our Timer (Get It Ready)
{
	memset(&timer, 0, sizeof(timer));						// Clear Our Timer Structure

	// Check To See If A Performance Counter Is Available
	// If One Is Available The Timer Frequency Will Be Updated
	if (!QueryPerformanceFrequency((LARGE_INTEGER *) &timer.frequency))
	{
		// No Performace Counter Available
		timer.performance_timer	= FALSE;					// Set Performance Timer To FALSE
		timer.mm_timer_start	= timeGetTime();			// Use timeGetTime() To Get Current Time
		timer.resolution		= 1.0f/1000.0f;				// Set Our Timer Resolution To .001f
		timer.frequency			= 1000;						// Set Our Timer Frequency To 1000
		timer.mm_timer_elapsed	= timer.mm_timer_start;		// Set The Elapsed Time To The Current Time
	}
	else
	{
		// Performance Counter Is Available, Use It Instead Of The Multimedia Timer
		// Get The Current Time And Store It In performance_timer_start
		QueryPerformanceCounter((LARGE_INTEGER *) &timer.performance_timer_start);
		timer.performance_timer			= TRUE;				// Set Performance Timer To TRUE
		// Calculate The Timer Resolution Using The Timer Frequency
		timer.resolution				= (float) (((double)1.0f)/((double)timer.frequency));
		// Set The Elapsed Time To The Current Time
		timer.performance_timer_elapsed	= timer.performance_timer_start;
	}
}


float GetTime()										// Get Time In Milliseconds
{
	__int64 time;											// time Will Hold A 64 Bit Integer

	if (timer.performance_timer)							// Are We Using The Performance Timer?
	{
		QueryPerformanceCounter((LARGE_INTEGER *) &time);	// Grab The Current Performance Time
		// Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
		return ( (float) ( time - timer.performance_timer_start) * timer.resolution);
	}
	else
	{
		// Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
		return( (float) ( timeGetTime() - timer.mm_timer_start) * timer.resolution);
	}
}

void gettimeofday(struct timeval* tp, void* notused)
{
	static DWORD _ref = timeGetTime();
	DWORD now = timeGetTime();
	DWORD delta = now - _ref;
	tp->tv_sec = delta / 1000;
	tp->tv_usec = (delta - tp->tv_sec*1000)*1000;
}

const char *const GetUDID()
{
	return "qwertasdfgzxcvb123451qaz2wsx3edc4rfv5tgb";
}

int GetDefaultLanguage()
{
return 0;
}


void DoSleep(int milis)
{
	Sleep(milis);
}


void winassert(char *text, bool condition)
{
	if (!condition)
	{
		//DBG("### assert FAILED: %s ###\n", text);
		::MessageBox(NULL, text, "### assert FAILED ###", MB_OK);
		//exit(-1);
		//_CrtDbgBreak();
	}
}

