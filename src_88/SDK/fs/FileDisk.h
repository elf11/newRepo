#ifndef INC_FILEDISK_H_
#define INC_FILEDISK_H_

#include "File.h"
#include <stdio.h>

class FileDisk: public File
{
private:
	friend class FileMgr;
	friend class Pak;

private:
	FILE* m_file;
	int m_size;
	char m_path[512];

	FileDisk();

	static FileDisk* Open(const char* fname);
	static FileDisk* Create(const char* fname);

public:
	virtual ~FileDisk();

	virtual void Close() override;
	virtual unsigned int Read(void *data, unsigned int size) override;
	virtual unsigned int Seek(int offset) override;
	virtual unsigned int Write(const void* data, unsigned int size) override;
	virtual const char* GetPath() const override {return m_path;}

	virtual int Size() const override {return m_size;}
	virtual int Pos() const override;
};

#endif //INC_FILEDISK_H_
