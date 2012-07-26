
#include "fs\FileDisk.h"
#include "fs\FileMgr.h"
#include "TankIncludes.h"

unsigned char *LoadFileBuffer(char *FileName,int &size)
{
	File * f = FILEMGR->Open(FileName);
	if (f == NULL)
	{
		return NULL;
	}
	size = f->Size();
	unsigned char *Data = new unsigned char[size];
	f->Read(Data,size);
	f->Close();
	delete f;
	return Data;
}
