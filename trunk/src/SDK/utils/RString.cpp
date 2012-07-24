#include "stdinc.h"
#include "misc.h"
#include "RString.h"

void String::copy(const char* str)
{
	SAFE_DEL(buf);

	if(str != NULL && strlen(str))
	{
		buf = new char[strlen(str) + 1];
		strcpy(buf, str);
	}
}

void String::wcopy(const wchar_t* str)
{
#ifdef _WIN32
	SAFE_DEL(buf);

    const int len = wcslen(str);
	if(str != NULL && len)
	{
        const int sz = (len + 1) << 1;
		buf = new char[sz];
		memcpy(buf, str, sz);
	}
#endif
}


String::String()
{
	buf = NULL;
}

String::String(const char* s)
{
	buf = NULL;
	copy(s);
}


String::String(const char* s, const int len)
{
	buf = NULL;

	char* tmp = new char[len + 1];
	memcpy(tmp, s, len); tmp[len] = 0;
	copy(tmp);
	SAFE_DEL(tmp);
}

String::String(const String& s)
{
	buf = NULL;
	copy(s.buf);
}

String::String(const int& i)
{
	buf = NULL;
    Printf("%d", i);
}

String::String(const float& f)
{
	buf = NULL;
    Printf("%.3f", f);
}

String::String(const double& d)
{
	buf = NULL;
    Printf("%.3f", d);
}


String::~String()
{
	SAFE_DEL_ARRAY(buf);
}

int String::Length()
{
	if(buf == NULL) return 0;
	return strlen(buf);
}

String::operator char* ()
{
	return buf;
}

String String::operator+ (String a)
{
	const int len = Length();
	const int len_a = a.Length();
	char *temp = new char[len + len_a + 1];
	if(len > 0)
	{
		strcpy(temp, buf);
		if(a.Length()) strcat(temp, a);
	}
	else
	{
		if(len_a > 0)
			strcpy(temp, a);
		else
			temp[0] = 0;
	}
	String s(temp);
    delete [] temp;
	return s;
}

String String::operator+(int a)
{
	return *this + String(a);
}

bool String::operator != (String s)
{
	return strcmp(buf, s.buf) != 0;
}


bool String::operator == (char* s) const
{
	return strcmp(buf, s) == 0;
}

bool String::Equals(const char* s)
{
    if(buf == NULL && s != NULL) return false;
    if(buf != NULL && s == NULL) return false;
    if(buf == NULL && s == NULL) return true;

	return strcmp(buf,s) == 0;
}

bool String::Equals(const String& s)
{
    return Equals(s.buf);
}

const String& String::operator = (char* str)
{
	SAFE_DEL(buf);
	copy(str);
	return *this;
}

String& String::operator = (String str)
{
	SAFE_DEL(buf);
	copy(str.buf);
	return *this;
}

String& String::operator += (String str)
{
	const int len = Length();
	if(len == 0)
	{
		copy(str.buf);
	}
	else
	{
		String temp(buf);
		SAFE_DEL(buf);
		buf = new char[len + str.Length() + 1];
		strcpy(buf, temp.buf);
		strcat(buf, str.buf);
	}

	return *this;
}

String String::Trim()
{
	return buf;
}

String String::Substring(int i)
{
	return buf + i;
}

String String::Substring(int start, int end)
{
    if(Length() == 0) return "";

	String ss = String(buf + start);
	ss.buf[end - start] = 0;
	return ss;
}

char String::CharAt(int i)
{
	return buf[i];
}

String& String::ToUpperCase()
{
	const int len = Length();
	for(int i = 0; i < len; i++)
	{
		char& c = buf[i];
		if(c < 'a' || c > 'z') continue;
		c += 'A' - 'a';
	}
	return *this;
}

String& String::ToLowerCase()
{
	const int len = Length();
	for(int i = 0; i < len; i++)
	{
		char& c = buf[i];
		if(c < 'A' || c > 'Z') continue;
		c -= 'A' - 'a';
	}
	return *this;
}

void String::Printf(const char* s, ...)
{
	char str[1024];
	va_list args;
	va_start (args, s);
	vsprintf(str, s, args);
	va_end (args); // end processing the argument list.
	copy(str);
}

void String::Printf(const wchar_t* s, ...)
{
#ifdef _WIN32
	wchar_t str[1024];
	va_list args;
	va_start (args, s);
    vswprintf(str, s, args);
	va_end (args); // end processing the argument list.
    wcopy(str);
#endif
}

int String::Find(char c)
{
	const int len = Length();
	for(int i = 0; i < len; i++)
	{
		char& ch = buf[i];
		if (ch == c) return i;
	}
	return -1;

}

int String::RemoveCharacter(char c)
{
	int ret = 0;
	const int len = Length();
	int index = 0;
	String newbuf;
	for(int i = 0; i < len; i++)
	{
		char& ch = buf[i];
		if (ch == c) 
		{
			newbuf += Substring(index,i);
			index = i+1;
			ret++;
		}
	}

	if (index<len)
		newbuf+=Substring(index,len);
	
	buf = NULL;
	copy(newbuf);

	return ret;

}

int String::ReplaceCharacter(char c,char newc)
{
	int ret = 0;
	const int len = Length();
	for(int i = 0; i < len; i++)
	{
		char& ch = buf[i];
		if (ch == c) 
		{
			buf[i] = newc;
			ret++;
		}
	}

	return ret;

}

int String::ToInt() const
{
    return atoi(buf);
}

float String::ToFloat() const
{
    if(buf == NULL || buf[0] == 0) return 0.0f;
    return atof(buf);
}

int String::Find(const char* str) const
{
    if(buf == NULL) return -1;
    if(str == NULL) return -1;
    const char* res = strstr(buf, str);
    if(res == NULL) return -1;
    return res - buf;
}

void String::Delete(const int& count)
{
    if(count >= Length())
    {
        SAFE_DEL(buf);
        return;
    }
    String ss(buf + count);
    copy(ss.buf);
}
/*
void String::Parse(const char* separators, Array<String>& out)
{
	
    out.SetLength(100);
    out.SetLength(0);

    String temp(buf);

    while(temp.Length())
    {
        int i = -1;
		
		for(int k = 0; k < strlen(separators); k++)
		{
			const int j = temp.Find(separators[k]);
			if(j >= 0) { i = j; break; }
		}
        if(i < 0) i = temp.Length();
        if(i >= 0)
        {
            out.Add(temp.Substring(0, i));
            temp.Delete(i + 1);
        }
    }
}
*/
char String::Last()
{
	if(Length() == 0) return 0;
	return buf[Length() - 1];
}

char String::First()
{
	if(Length() == 0) return 0;
	return buf[0];
}
