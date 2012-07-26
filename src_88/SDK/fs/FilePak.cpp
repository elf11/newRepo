#include "stdinc.h"
#include "FilePak.h"

FilePak::FilePak(File* f, int pos, int size)
{
	m_file = f;
	m_pos = pos;
	m_size = size;
	m_fp = 0;

	f->Seek(pos);
}

FilePak::~FilePak()
{
	Close();
}

void FilePak::Close()
{
	if (m_file)
	{
		m_file->Close();
		delete m_file;
		m_file = NULL;
	}
}

unsigned int FilePak::Read(void *data, unsigned int size)
{
	if (m_fp + size > m_size)
		size = m_size - m_fp;

	if (!size)
		return 0;

	m_fp += size;

	return m_file->Read(data, size);
}

unsigned int FilePak::Seek(int offset)
{
	m_fp = offset;
	return m_file->Seek(m_pos + offset);
}

unsigned int FilePak::Write(const void* data, unsigned int size)
{
	m_fp += size;
	return m_file->Write(data, size);
}

int FilePak::Pos() const
{
	return m_fp;
}