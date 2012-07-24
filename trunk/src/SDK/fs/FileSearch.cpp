#include "stdinc.h"
#include "FileSearch.h"
#include "Pak.h"
#include "FileMgr.h"


FileSearch::FileSearch()
{
	Clean();
}

void FileSearch::Clean()
{
	m_count = 0;
	m_lastPos = 0;
	m_path[0] = 0;
}

void FileSearch::SetPath(const char* path)
{
	strncpy(m_path, path, 512);
}

bool FileSearch::AddFile(const char* name)
{
	for (int i=0; i<m_count; i++)
	{
		if (!strcmp(name, m_names+m_files[i]))
			return true;
	}

	int len = strlen(name);
	if (m_lastPos + len >= MAX_DATA)
		return false;

	m_files[m_count++]= m_lastPos;

	strncpy(m_names+m_lastPos, name, len);
	m_lastPos += len+1;

	return true;
}

const char* FileSearch::GetName(int index) const
{
	return m_names + m_files[index];
}

File* FileSearch::GetFile(int index) const
{
	char tmp[512];

	sprintf(tmp, "%s%s", m_path, m_names + m_files[index]);
	return FILEMGR->Open(tmp);
}
