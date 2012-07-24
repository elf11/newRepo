#ifndef _SECURITY_H_
#define _SECURITY_H_

#include "stdinc.h"
#define CHECK_NUMBER 1


class Security
{
public:
	Security(){};

	static void Encrypt (unsigned int* v, unsigned int* k);
	static void Decrypt (unsigned int* v, unsigned int* k);
	static void EncryptString(char *str, int &len);
	static bool DecryptString(char *str, int &len,bool defaultkey = false);
	static const char* defaultEncryptKey;

};
#endif