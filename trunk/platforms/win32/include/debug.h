/*
 * =============================================================================
 * 
 *       Filename:  debug.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  10/06/2010 04:07:43 PM EEST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  Ing. Hanganu Andrei (ah), ahanganu@revo-solutions.ro
 *        Company:  Revo Solutions SRL
 * 
 * =============================================================================
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif
#define  DEBUG_OUT(...){\
	char  _tmp[1024];\
	snprintf(_tmp, 1024,"\n"  __VA_ARGS__);\
	_tmp[1023] = '\0';\
	OutputDebugString(_tmp);\
}
#ifdef __cplusplus
}
#define DUMP_DEBUG(...)
#define DUMP_DEBUG_BIN(var)

#define DEBUG_OUT_FILE( ... ) {\
	char __msg[2048];\
	sprintf(__msg, __VA_ARGS__);\
	char __filepid[64];\
	sprintf(__filepid, "rog.log");\
	FILE* __f = fopen(__filepid, "a+");\
	if( __f ){\
	fwrite( __msg, strlen(__msg), 1, __f );\
	fclose(__f);\
	fflush(NULL);\
	}\
}

#endif

#endif // __DEBUG_H__

