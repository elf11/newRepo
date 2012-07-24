#ifndef INC_PAK_H_
#define INC_PAK_H_

class File;
class FileSearch;

class Pak
{
private:
	friend class FileMgr;

	typedef struct
	{
		unsigned int sig;
		unsigned int ver;
		unsigned int count;
		unsigned int nameSize;
		unsigned int unused1;
		unsigned int unused2;
		unsigned int unused3;
		unsigned int unused4;
	}THeader;

	typedef struct
	{
		unsigned int namePos;
		unsigned int flags;
		unsigned int start;
		unsigned int size;
		unsigned int unused1;
		unsigned int unused2;
		unsigned int unused3;
		unsigned int unused4;
	}TEntry;

private:
	THeader m_header;
	TEntry* m_entries;
	char* m_names;

	char m_path[512];

private:
	Pak(File* f);

public:
	~Pak();

	int GetFileIndex(const char* fname);
	File* GetFile(const char* fname);
	File* GetFile(int index);

	const char* GetFileName(int index);

	void SearchFiles(const char* path, const char* pattern, FileSearch* fs);
};

#endif //INC_PAK_H_
