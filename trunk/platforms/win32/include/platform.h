#ifndef __WIN32_PLATFORM_H__
#define __WIN32_PLATFORM_H__
#include <malloc.h>
#include <math.h>


#define _WINSOCKAPI_
#include <windows.h>
#include <stdarg.h>
#include <Mmsystem.h>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <Winsock2.h>

#define copysign _copysign
inline double roundf(double x) { return floor(x + 0.5); }
inline float truncf(float x) { return ((float)((int)x));}
inline float expm1f(float x) { return exp(x)-1.f; }
inline float exp2f(float x){ return powf(2,x); } //this can be taken from FreeBS// 
#define log2f(x) (logf(x)*1.4426950408889634f)
#define remainderf fmodf
#define alloca _alloca
#define snprintf _snprintf

void TimerInit(void);
int GetDefaultLanguage();
float GetTime();

#define GL_ADD_SIGNED                     0x8574
#define GL_MODULATE                       0x2100
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )

#define mkdir(dir, mode) _mkdir(dir)
#define rmdir(dir, mode) _rmdir(dir)
void gettimeofday(struct timeval* tp, void* notused);
void DoSleep(int milis);
void EnableDeviceSleep(bool doSleep);
const char* const  GetUDID();

void EnableDeviceSleep(bool val);

void winassert(char *text, bool condition);

#define Assert(Condition,Message) winassert(Message,Condition)

#ifndef OS_WINDOWS
#define OS_WINDOWS
#endif

#define APPLE_DEMO_MODE 0
#define APPLE_STAGE_DEMO 0

#endif

