#include "stdinc.h"
#include "FileDisk.h"


FileDisk::FileDisk()
{
	m_file = NULL;
	m_size = 0;
}

FileDisk* FileDisk::Open(const char* fname)
{
	FILE* f = fopen(fname, "rb");
	if (!f)
		return NULL;

	FileDisk* fd = new FileDisk();
	fd->m_file = f;

	fseek(fd->m_file, 0, SEEK_END);
	fd->m_size = ftell(fd->m_file);
	fseek(fd->m_file, 0, SEEK_SET);

	strncpy(fd->m_path, fname, 512);
	return fd;
}

FileDisk* FileDisk::Create(const char* fname)
{
	FILE* f = fopen(fname, "wb");
	if (!f)
		return NULL;

	FileDisk* fd = new FileDisk();
	fd->m_file = f;

	fd->m_size = 0;

	strncpy(fd->m_path, fname, 512);
	return fd;
}


FileDisk::~FileDisk()
{
	Close();
}

void FileDisk::Close()
{
	if (m_file)
	{
		fclose(m_file);
		m_file = NULL;
	}
}

unsigned int FileDisk::Read(void *data, unsigned int size)
{
	if (!m_file)
		return -1;

	return fread(data, 1, size, m_file);
}

unsigned int FileDisk::Seek(int offset)
{
	if (!m_file)
		return -1;

	return fseek(m_file, offset, SEEK_SET);
}

unsigned int FileDisk::Write(const void* data, unsigned int size)
{
	if (!m_file)
		return -1;

	return fwrite(data, 1, size, m_file);
}

int FileDisk::Pos() const
{
	if (!m_file)
		return -1;

	return ftell(m_file);
}
