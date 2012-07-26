#include "WString.h"
#include "stdinc.h"
#include <stdarg.h>

#define MAX_TMP_POOL  (8 * 1024)
static WCHR tmp_pool[MAX_TMP_POOL];
static char	tmp_pool_s[MAX_TMP_POOL];
static int tmp_pool_pos = 0;
static int tmp_pool_pos_s = 0;

WCHR wstring_empty[1] = {0};

int STRLEN(const WCHR* str)
{
	int len = 0;
	while (str[len])
		len++;

	return len;
}

int STRCPY(WCHR* dst, const WCHR* src)
{
	int len = 0;

	while (src[len])
	{
		dst[len] = src[len];
		len++;
	}

	dst[len] = 0;
	return len;
}

int STRCPYs(WCHR* dst, const char* src)
{
	int len = 0;

	while (src[len])
	{
		dst[len] = src[len];
		len++;
	}

	dst[len] = 0;
	return len;
}

int STRNCPYs(WCHR* dst, const char* src, int maxLen)
{
	int len = 0;
    
	while (src[len])
	{
		dst[len] = src[len];
		len++;
		if(len==maxLen-1){
			break;
		}
	}
    
	dst[len] = 0;
	return len;
}


int STRNCPY(WCHR* dst, const WCHR* src, int maxLen)
{
	int len = 0;

	while (src[len])
	{
		dst[len] = src[len];
		len++;
		if(len==maxLen-1){
			break;
		}
	}

	dst[len] = 0;
	return len;
}

int STRCAT(WCHR* dst, const WCHR* src)
{
	int len = 0;
	int ps = 0;

	while (dst[len])
		len++;

	while (src[ps])
		dst[len++] = src[ps++];

	dst[len] = 0;

	return len;
}

int STRCMP(const WCHR* s1, const WCHR* s2)
{
	int p = 0;

	while (s1[p] && s2[p])
	{
		if (s1[p] < s2[p])
			return -1;
		if (s1[p] > s2[p])
			return 1;

		p++;
	}

	return 0;
}

static WCHR* m_pool;
static int m_len;

void printD(int val, int digCnt, bool fillZero)
{
	bool minus = false;
	if (val < 0)
	{
		minus = true;
		val = -val;
	}

	char tmp[32];
	int len = 0;

	if (val == 0)
	{
		tmp[len++] = '0';
	}
	else
	{
		while (val > 0)
		{
			tmp[len++] = val % 10 + '0';
			val /= 10;
		}
	}

	if (fillZero)
	{
		if (minus)
			digCnt--;

		while (len < digCnt)
			tmp[len++] = '0';

		if (minus)
			tmp[len++] = '-';
	}
	else
	{
		if (minus)
			tmp[len++] = '-';

		while (len < digCnt)
			tmp[len++] = ' ';
	}

	len--;

	while (len>=0)
	{
		m_pool[m_len++] = tmp[len--];
	}
}

void printU(unsigned int val, int digCnt, bool fillZero)
{
	char tmp[32];
	int len = 0;

	if (val == 0)
	{
		tmp[len++] = '0';
	}
	else
	{
		while (val > 0)
		{
			tmp[len++] = val % 10 + '0';
			val /= 10;
		}
	}

	if (fillZero)
	{
		while (len < digCnt)
			tmp[len++] = '0';
	}
	else
	{
		while (len < digCnt)
			tmp[len++] = ' ';
	}

	len--;

	while (len>=0)
	{
		m_pool[m_len++] = tmp[len--];
	}
}

void printX(unsigned int val, int digCnt, bool fillZero, bool uppercase)
{
	static const char* hex_lo = "0123456789abcdef";
	static const char* hex_up = "0123456789ABCDEF";
	
	const char* hex;

	if (uppercase)
		hex = hex_up;
	else
		hex = hex_lo;

	char tmp[32];
	int len = 0;

	if (val == 0)
	{
		tmp[len++] = '0';
	}
	else
	{
		while (val > 0)
		{
			tmp[len++] = hex[val & 0x0000000f];
			val >>= 4;
		}
	}

	if (fillZero)
	{
		while (len < digCnt)
			tmp[len++] = '0';
	}
	else
	{
		while (len < digCnt)
			tmp[len++] = ' ';
	}

	len--;

	while (len>=0)
	{
		m_pool[m_len++] = tmp[len--];
	}
}

void printF(double val, int digCnt, int precCnt, bool fillZero)
{
	bool minus = false;
	if (val < 0)
	{
		minus = true;
		val = -val;
	}

	int vi = (int)val;
	double left = val - vi;

	char tmp[64];
	int len = 0;

	if (precCnt > 0)
	{
		len = precCnt-1;
		while (len >= 0)
		{
			left = left * 10.0;
			int li = (int)left;
			left = left - li;
			tmp[len] = li + '0';
			len--;
		}
		len = precCnt;
		tmp[len++] = '.';
	}

	if (vi == 0)
	{
		tmp[len++] = '0';
	}
	else
	{
		while (vi > 0)
		{
			tmp[len++] = vi % 10 + '0';
			vi /= 10;
		}
	}

	if (fillZero)
	{
		if (minus)
			digCnt--;

		while (len < digCnt)
			tmp[len++] = '0';

		if (minus)
			tmp[len++] = '-';
	}
	else
	{
		if (minus)
			tmp[len++] = '-';

		while (len < digCnt)
			tmp[len++] = ' ';
	}

	len--;

	while (len>=0)
	{
		m_pool[m_len++] = tmp[len--];
	}
}

void printS(const void* val, int len, int eSize)
{
	if (eSize == 1)
	{
		const char* s = (const char*)val;
		
		char tmp[] = {'(', 'n', 'u', 'l', 'l', ')', 0};
		if (!s) //check for NULL pointer
			s = tmp;

		int n = 0;
		while (s[n])
			n++;

		while (n < len)
		{
			m_pool[m_len++] = ' ';
			n++;
		}

		for (int i=0; s[i]; s++)
			m_pool[m_len++] = s[i];
	}

	if (eSize == 2)
	{
		const unsigned short* s = (const unsigned short*)val;

		unsigned short tmp[] = {'(', 'n', 'u', 'l', 'l', ')', 0};
		if (!s) //check for NULL pointer
			s = tmp;

		int n = 0;
		while (s[n])
			n++;

		while (n < len)
		{
			m_pool[m_len++] = ' ';
			n++;
		}

		for (int i=0; s[i]; s++)
			m_pool[m_len++] = s[i];
	}

	if (eSize == 4)
	{
		const unsigned int* s = (const unsigned int*)val;

		unsigned int tmp[] = {'(', 'n', 'u', 'l', 'l', ')', 0};
		if (!s) //check for NULL pointer
			s = tmp;

		int n = 0;
		while (s[n])
			n++;

		while (n < len)
		{
			m_pool[m_len++] = ' ';
			n++;
		}

		for (int i=0; s[i]; s++)
			m_pool[m_len++] = s[i];
	}
}

void printSpecial(va_list& vl, int chr, int digCnt, int preCnt, bool fillZero)
{
	switch (chr)
	{
	case 'd':
		printD(va_arg(vl, int), digCnt, fillZero);
		break;

	case 'u':
		printD(va_arg(vl, unsigned int), digCnt, fillZero);
		break;

	case 'x':
		printX(va_arg(vl, unsigned int), digCnt, fillZero, false);
		break;

	case 'X':
		printX(va_arg(vl, unsigned int), digCnt, fillZero, true);
		break;

	case 'f':
		printF(va_arg(vl, double), digCnt, preCnt, fillZero);
		break;

	case 's':
		printS(va_arg(vl, char*), digCnt, sizeof(char));
		break;

	case 'w':
		printS(va_arg(vl, WCHR*), digCnt, sizeof(WCHR));
		break;

	case 'W':
		printS(va_arg(vl, wchar_t*), digCnt, sizeof(wchar_t));
		break;

	case '%':
		printS("%", digCnt, sizeof(char));
		break;

	case 'c':
		m_pool[m_len++] = va_arg(vl, unsigned int);
		ASSERTD(m_pool[m_len-1] != 0, "Chars need to be different than 0");
		break;
	}
}

int SPRINTF(WCHR* dst, const char* fmt, ...)
{
	int fp = 0;
	m_len = 0;
	m_pool = dst;

	va_list vl;
	va_start(vl, fmt);

	while (fmt[fp])
	{
		if (fmt[fp] != '%')
		{
			m_pool[m_len++] = fmt[fp++];
		}
		else
		{
			fp++;

			int digCnt = 0;
			int preCnt = -1;
			bool fillZero = false;

			if (fmt[fp] == '0')
			{
				fillZero = true;
				fp++;
			}

			while ((fmt[fp] >= '0') && (fmt[fp] <= '9'))
			{
				digCnt = digCnt*10 + fmt[fp++]-'0';
			}

			if (fmt[fp] == '.')
			{
				fp++;
				preCnt = 0;
				while ((fmt[fp] >= '0') && (fmt[fp] <= '9'))
				{
					preCnt = preCnt*10 + fmt[fp++]-'0';
				}
			}

			printSpecial(vl, fmt[fp++], digCnt, preCnt, fillZero);
		}
	}

	va_end(vl);

	m_pool[m_len] = 0;
	return m_len;
}

int SPRINTF(WCHR* dst, const WCHR* fmt, ...)
{
	int fp = 0;
	m_len = 0;
	m_pool = dst;

	va_list vl;
	va_start(vl, fmt);

	while (fmt[fp])
	{
		if (fmt[fp] != '%')
		{
			m_pool[m_len++] = fmt[fp++];
		}
		else
		{
			fp++;

			int digCnt = 0;
			int preCnt = -1;
			bool fillZero = false;

			if (fmt[fp] == '0')
			{
				fillZero = true;
				fp++;
			}

			while ((fmt[fp] >= '0') && (fmt[fp] <= '9'))
			{
				digCnt = digCnt*10 + fmt[fp++]-'0';
			}

			if (fmt[fp] == '.')
			{
				fp++;
				preCnt = 0;
				while ((fmt[fp] >= '0') && (fmt[fp] <= '9'))
				{
					preCnt = preCnt*10 + fmt[fp++]-'0';
				}
			}

			printSpecial(vl, fmt[fp++], digCnt, preCnt, fillZero);
		}
	}

	va_end(vl);

	m_pool[m_len] = 0;
	return m_len;
}

WCHR* STRDUP(const WCHR* str)
{
	int len = 0;

	while (str[len])
		len++;

	WCHR* dst = new WCHR[len+1];
	STRCPY(dst, str);

	return dst;
}

WCHR* STRDUPs(const char* str)
{
	int len = 0;

	while (str[len])
		len++;

	WCHR* dst = new WCHR[len+1];
	STRCPYs(dst, str);

	return dst;
}

WCHR* TMPSTR(const char* str)
{
	int len = 0;

	while (str[len])
		len++;

	if (tmp_pool_pos + len >= MAX_TMP_POOL-1)
		tmp_pool_pos = 0;

	if (len > MAX_TMP_POOL - 1)
		len = MAX_TMP_POOL - 1;

	WCHR* ret = &tmp_pool[tmp_pool_pos];

	for (int i=0; i<len; i++)
		ret[i] = str[i];

	ret[len] = 0;
	tmp_pool_pos += len+1;

	return ret;
}

char* TMPSTRs(const WCHR* str)
{
	int len = STRLEN(str);

	if (tmp_pool_pos_s + len >= MAX_TMP_POOL-1)
		tmp_pool_pos_s = 0;

	if (len > MAX_TMP_POOL - 1)
		len = MAX_TMP_POOL - 1;

	char* ret = &tmp_pool_s[tmp_pool_pos_s];
	for(int i=0; i<len; ++i)
	{
		if(str[i]<255)
			ret[i] = str[i];
		else
			ret[i] = ' '; //replace wierd chars with spaces
	}
	ret[len] = '\0';
	tmp_pool_pos_s += len+1;

	return ret;
}

const WCHR* SHORTENSTR(const WCHR* str, int len)
{
	if (STRLEN(str) <= len)
		return str;

	//add ...
	len += 3;

	if (tmp_pool_pos + len >= MAX_TMP_POOL-1)
		tmp_pool_pos = 0;

	if (len > MAX_TMP_POOL - 1)
		len = MAX_TMP_POOL - 1;

	WCHR* ret = &tmp_pool[tmp_pool_pos];

	for (int i=0; i<len - 3; i++)
		ret[i] = str[i];

	for (int i = len - 3; i < len; i++)
		ret[i] = '.';

	ret[len] = 0;
	tmp_pool_pos += len + 1;

	return ret;
}
