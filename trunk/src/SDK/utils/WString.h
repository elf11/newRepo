#ifndef INC_WSTRING_H_
#define INC_WSTRING_H_

typedef unsigned short WCHR;

int STRLEN(const WCHR* str);
int STRCPY(WCHR* dst, const WCHR* src);
int STRCPYs(WCHR* dst, const char* src);
int STRNCPY(WCHR* dst, const WCHR* src, int maxLen);
int STRNCPYs(WCHR* dst, const char* src, int maxLen);
int STRCAT(WCHR* dst, const WCHR* src);
int SPRINTF(WCHR* dst, const char* fmt, ...);
int SPRINTF(WCHR* dst, const WCHR* fmt, ...);
int STRCMP(const WCHR* s1, const WCHR* s2);

WCHR* STRDUP(const WCHR* str);
WCHR* STRDUPs(const char* str);

WCHR* TMPSTR(const char* str);
char* TMPSTRs(const WCHR* str);

const WCHR* SHORTENSTR(const WCHR* str, int len);

extern WCHR wstring_empty[1];

#endif //INC_WSTRING_H_
