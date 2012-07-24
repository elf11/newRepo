#include "stdinc.h"
#include "FileMgr.h"
#include "FileUtils.h"
#include "FileDisk.h"
#include "Pak.h"

static FileMgr st_fileMgr;
FileMgr* FILEMGR = &st_fileMgr;

FileMgr::FileMgr()
{
	m_numPaks = 0;
}

FileMgr::~FileMgr()
{
	Cleanup();
}

void FileMgr::Cleanup()
{
	for (int i=0; i<m_numPaks; i++)
		SAFE_DEL(m_paks[i]);
}

void FileMgr::Init()
{
	ReScan();
}

void FileMgr::ReScan()
{
	Cleanup();

	char tmp[512];
	sprintf(tmp, "%spaks/base.pak", FILEUTILS->GetDataPath());
	File* f = FileDisk::Open(tmp);
	if (f)
    {
		m_paks[m_numPaks++] = new Pak(f);
        f->Close();
        delete f;
    }
}


File* FileMgr::Open(const char* fname)
{
	char tmp[512];

	sprintf(tmp, "%s%s", FILEUTILS->GetDocsPath(), fname);
	FileDisk *fd = FileDisk::Open(tmp);
    
    if (fd)
        return fd;

    sprintf(tmp, "%s%s", FILEUTILS->GetDataPath(), fname);
    fd = FileDisk::Open(tmp);
    
    if (fd)
        return fd;

	for (int i=0; i<m_numPaks; i++)
	{
		int idx = m_paks[i]->GetFileIndex(fname);

		if (idx >= 0)
			return m_paks[i]->GetFile(idx);
	}

	return NULL;
}

File* FileMgr::Create(const char* fname)
{
	char tmp[512];

	sprintf(tmp, "%s%s", FILEUTILS->GetDocsPath(), fname);
	FileDisk *fd = FileDisk::Create(tmp);

	return fd;
}

void FileMgr::Delete(const char* fname)
{
	char tmp[512];
	sprintf(tmp, "%s%s", FILEUTILS->GetDocsPath(), fname);

	FILEUTILS->Delete(tmp);
}

bool FileMgr::FileExists(const char* fname)
{
	char tmp[512];
	sprintf(tmp, "%s%s", FILEUTILS->GetDocsPath(), fname);

	if (FILEUTILS->FileExists(tmp))
		return true;

	sprintf(tmp, "%s%s", FILEUTILS->GetDataPath(), fname);

	if (FILEUTILS->FileExists(tmp))
		return true;

	for (int i=0; i<m_numPaks; i++)
	{
		if (m_paks[i]->GetFileIndex(fname) >= 0)
			return true;
	}

	return false;
}

bool FileMgr::Move(const char* src, const char* dst)
{
    MakePath(dst);
    
	char tmpSrc[512];
	sprintf(tmpSrc, "%s%s", FILEUTILS->GetDocsPath(), src);

	char tmpDst[512];
	sprintf(tmpDst, "%s%s", FILEUTILS->GetDocsPath(), dst);

	return FILEUTILS->Move(tmpSrc, tmpDst);
}

bool FileMgr::DeleteFolder(const char* fname)
{
	char tmp[512];
	sprintf(tmp, "%s%s", FILEUTILS->GetDocsPath(), fname);

	return FILEUTILS->DeleteFolder(tmp);
}

bool FileMgr::MakePath(const char* path)
{
	char tmp[512];
	sprintf(tmp, "%s%s", FILEUTILS->GetDocsPath(), path);

	return FILEUTILS->MakePath(tmp);
}

void FileMgr::SearchFiles(const char* path, const char* pattern, FileSearch* fs)
{
	fs->Clean();
	fs->SetPath(path);

	char tmp[512];
	sprintf(tmp, "%s%s", FILEUTILS->GetDocsPath(), path);
	FILEUTILS->SearchFiles(tmp, pattern, fs);

	sprintf(tmp, "%s%s", FILEUTILS->GetDataPath(), path);
	FILEUTILS->SearchFiles(tmp, pattern, fs);

	for (int i=0; i<m_numPaks; i++)
		m_paks[i]->SearchFiles(path, pattern, fs);
}
