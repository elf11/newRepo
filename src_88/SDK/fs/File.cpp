#include "stdinc.h"
#include "File.h"

int File::ReadLine(char* buf, int maxLen)
{
	char c = ReadChar();

	while ((c=='\n') || (c=='\r'))
		c = ReadChar();

	int p = 0;
	while ((p<maxLen) && (c != '\n') && (c != '\r') && c)
	{
		buf[p++] = c;
		c = ReadChar();
	}

	buf[p] = 0;

	return p;
}

char File::ReadChar()
{
	char v;
	if (Read(&v, sizeof(v)))
		return v;
	return 0;
}

unsigned short File::ReadU16()
{
	unsigned short v;
	if (Read(&v, sizeof(v)))
		return v;

	return 0;
}

unsigned int File::ReadU32()
{
	unsigned int v;
	if (Read(&v, sizeof(v)))
		return v;
	return 0;
}
