#ifndef INC_FILEUTILS_H_
#define INC_FILEUTILS_H_

class FileSearch;

class FileUtils
{
private:
	friend class FileMgr;

private:
	char m_dataPath[512];
	char m_docsPath[512];

private:
	void SearchFiles(const char* path, const char* pattern, FileSearch* fs);

	void Delete(const char* fname);
	bool FileExists(const char* fname);
	bool Move(const char* src, const char* dst);
	bool DeleteFolder(const char* fname);
	bool MakePath(const char* path);
	
public:
	void Init(const char* root);

	const char* GetDataPath() const {return m_dataPath;}
	const char* GetDocsPath() const {return m_docsPath;}
};

extern FileUtils* FILEUTILS;

#endif //INC_FILEUTILS_H_
