#ifndef INC_FILEMGR_H_
#define INC_FILEMGR_H_

#include "File.h"
#include "FileSearch.h"

class Pak;

class FileMgr
{
private:
	static const int MAX_PAKS = 64;

	Pak* m_paks[MAX_PAKS];
	int m_numPaks;

private:
	void Cleanup();

public:
	FileMgr();
	~FileMgr();

	void Init();
	void ReScan();

	File* Open(const char* fname);
	File* Create(const char* fname);

	void Delete(const char* fname);
	bool FileExists(const char* fname);
	bool Move(const char* src, const char* dst);
	bool DeleteFolder(const char* fname);
	bool MakePath(const char* path);

	void SearchFiles(const char* path, const char* pattern, FileSearch* fs);
};

extern FileMgr* FILEMGR;

#endif //INC_FILEMGR_H_
