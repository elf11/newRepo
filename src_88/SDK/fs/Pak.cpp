#include "stdinc.h"
#include "Pak.h"

#include "File.h"
#include "FilePak.h"
#include "FileMgr.h"
#include "FileDisk.h"


#define FLAG_FOLDER  0x0001

Pak::Pak(File* f)
{
	m_entries = NULL;
	m_names = NULL;

	f->Read(&m_header, sizeof(m_header));

	m_entries = new TEntry[m_header.count];
	f->Read(m_entries, sizeof(TEntry) * m_header.count);
	
	m_names = new char[m_header.nameSize];
	f->Read(m_names, m_header.nameSize);

	strncpy(m_path, f->GetPath(), 512);
}

Pak::~Pak()
{
	SAFE_DEL_ARRAY(m_entries);
	SAFE_DEL_ARRAY(m_names);
}

File* Pak::GetFile(const char* fname)
{
	int idx = GetFileIndex(fname);

	if (idx >= 0)
		return GetFile(idx);

	return NULL;
}

int Pak::GetFileIndex(const char* fname)
{
	int eStart = m_entries[0].start;
	int eEnd = eStart+m_entries[0].size;

	while (*fname)
	{
		int n = 0;
		while (fname[n] && (fname[n] != '\\') && (fname[n] != '/'))
			n++;

		for (int i=eStart; i<eEnd; i++)
		{
			if (!strncmp(m_names + m_entries[i].namePos, fname, n))
			{
				if (m_entries[i].flags & FLAG_FOLDER)
				{
					eStart = m_entries[i].start;
					eEnd = eStart + m_entries[i].size;
				}
				else
				{
					return i;
				}

				break;
			}
		}

		fname += n+1;
	}

	return -1;
}

File* Pak::GetFile(int index)
{
	return new FilePak(FileDisk::Open(m_path), m_entries[index].start, m_entries[index].size);
}

const char* Pak::GetFileName(int index)
{
	return m_names+m_entries[index].namePos;
}

void Pak::SearchFiles(const char* path, const char* pattern, FileSearch* fs)
{

}
