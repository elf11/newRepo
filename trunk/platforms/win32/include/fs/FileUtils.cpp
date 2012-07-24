#include "stdinc.h"
#include "FileUtils.h"

static FileUtils st_fileUtils;
FileUtils* FILEUTILS = &st_fileUtils;

void FileUtils::Init(const char* root)
{
	strncpy(m_dataPath, root, 512);

	int p = strlen(root);
	while (p && (m_dataPath[p] != '/'))
		p--;
	m_dataPath[p+1] = 0;
	strcpy(m_docsPath, m_dataPath);
	strcat(m_docsPath,"Documents/");
}

void FileUtils::SearchFiles(const char* path, const char* pattern, FileSearch* fs)
{
#if 0
    HANDLE dirp;
	WIN32_FIND_DATA FindFileData;
	struct dirent* direntp;
    
	int totalLen = 0;
	int fileCount = 0;
    
	char tmp[512];
    
	for (int i=0; i<2; i++)
	{
		tmp[0] = 0;
        
		if ((flags & STREAM_FIND_DOCS) && (i==0))
		{
			sprintf(tmp, "%s%s/*",write_pwd, path);
		}
        
		if ((flags & STREAM_FIND_APP) && (i==1))
		{
			sprintf(tmp, "%s%s/*",pwd, path);
		}
        
		if (tmp[0])
		{		
			if((dirp = FindFirstFile(tmp, &FindFileData)) != INVALID_HANDLE_VALUE){
				do{
                    char* name = FindFileData.cFileName;//direntp->d_name;
                    
                    if (wildcardMatch(name, pattern))
                    {
                        int len = strlen(name);
                        if (totalLen + len < maxSize)
                        {
                            strcpy(output, name);
                            output+=len+1;
                            totalLen+=len+1;
                            fileCount++;
                        }
                    }
                } while(FindNextFile(dirp, &FindFileData));
                //closedir(dirp);
            }
            FindClose(dirp);
        }
        
        
    }
    
	return fileCount;
#endif
}

void FileUtils::Delete(const char* fname)
{
	remove(fname);
}

bool FileUtils::FileExists(const char* fname)
{
	FILE* f = fopen(fname, "rb");

	if (!f)
		return false;

	fclose(f);
	return true;
}

bool FileUtils::Move(const char* src, const char* dst)
{
	int ret = rename(src, dst);

	return (ret == 0);
}

bool FileUtils::DeleteFolder(const char* fname)
{
    HANDLE dirp;
	WIN32_FIND_DATA FindFileData;
	struct dirent* direntp;
    
	int totalLen = 0;
	int fileCount = 0;
    
	char tmp[512];
    
    tmp[0] = 0;
    
    sprintf(tmp, "%s/*", fname);
    
    if (tmp[0])
    {		
        if((dirp = FindFirstFile(tmp, &FindFileData)) != INVALID_HANDLE_VALUE){
            do{
                char* name = FindFileData.cFileName;//direntp->d_name;
                if(strcmp(name, ".") != 0 && strcmp(name, "..") != 0){
                    char full_name[MAX_PATH];
                    snprintf(full_name, MAX_PATH, "%s/%s", fname, name );
                    if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
                        //have folder
                        DeleteFolder(full_name);
                    } else {
                        Delete(full_name);
                    }
                }
            } while(FindNextFile(dirp, &FindFileData));
            //closedir(dirp);
        }
        FindClose(dirp);
        tmp[strlen(tmp)-2]='\0';
        int r = rmdir(tmp);
        printf(" %d ", r);
    }

	return true;
}

bool FileUtils::MakePath(const char* path)
{
    char _full_path[512];
	snprintf(_full_path, 512, "%s", path);
	char* start = _full_path;
	char* n = start;
	char* end = _full_path+strlen(_full_path);
	while(n!=end){
		if(*n=='/'){
			*n = '\0';
			mkdir(start, 0888);
			*n = '/';
		}
		++n;
	}

	return true;
}
