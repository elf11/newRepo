#ifndef INC_FILE_H_
#define INC_FILE_H_

class File
{
public:
    virtual ~File() {};
	virtual void Close() = 0;
	virtual unsigned int Read(void *data, unsigned int size) = 0;
	virtual unsigned int Seek(int offset) = 0;
	virtual unsigned int Write(const void* data, unsigned int size) = 0;
	virtual const char* GetPath() const = 0;

	virtual int Size() const = 0;
	virtual int Pos() const = 0;

	int ReadLine(char* buf, int maxLen);
	char ReadChar();
	unsigned short ReadU16();
	unsigned int ReadU32();
};

#endif //INC_FILE_H_
