#ifndef INC_FILEPAK_H_
#define INC_FILEPAK_H_

#include "File.h"

class FilePak: public File
{
private:
	friend class Pak;

private:
	File *m_file;
	int m_pos;
	int m_size;

	int m_fp;

	FilePak(File* f, int pos, int size);

public:
	virtual ~FilePak();

	virtual void Close() override;
	virtual unsigned int Read(void *data, unsigned int size) override;
	virtual unsigned int Seek(int offset) override;
	virtual unsigned int Write(const void* data, unsigned int size) override;
	virtual const char* GetPath() const override {return NULL;}

	virtual int Size() const override {return m_size;}
	virtual int Pos() const override;
};

#endif //INC_FILEPAK_H_
