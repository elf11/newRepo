#ifndef INC_FILESEARCH_H_
#define INC_FILESEARCH_H_

class File;
class Pak;

class FileSearch
{
private:
	friend class FileUtils;
	friend class FileMgr;

	static const int MAX_FILES = 1024;
	static const int MAX_DATA = MAX_FILES * 32;

	int m_files[MAX_FILES];
	char m_names[MAX_DATA];
	int m_lastPos;

	char m_path[512];
	int m_count;

private:
	void Clean();
	bool AddFile(const char* name);
	void SetPath(const char* path);

public:
	FileSearch();

	int GetFileCount() const {return m_count;}
	const char* GetName(int index) const;
	File* GetFile(int index) const;
};

#endif //INC_FILESEARCH_H_
