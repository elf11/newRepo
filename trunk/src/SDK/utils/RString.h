#ifndef SDK_STRING_H_INCLUDED
#define SDK_STRING_H_INCLUDED


class String
{
	char* buf;
	void copy(const char* str);
	void wcopy(const wchar_t* str);
public:
	String();
	String(const char* s);
	String(const char* s, const int len);
	String(const String& s);
	String(const int& i);
	String(const float& f);
	String(const double& f);
	~String();

	int Length();
	operator char* ();
	String operator+(String a);
	String operator+(int a);
	bool operator != (String s);
	bool operator == (char* s) const;
	const String& operator = (char* str);
	String& operator = (String str);
	String& operator += (String str);
	String Trim();
	String Substring(int i);
	String Substring(int start, int end);
	char CharAt(int i);
	String& ToUpperCase();
	String& ToLowerCase();
	void Printf(const char* s,...);
	void Printf(const wchar_t* s,...);
	bool Equals(const char* s);
	bool Equals(const String& s);
	int Find(char c);
	int Find(const char* str) const;
	int RemoveCharacter(char c);
	int ReplaceCharacter(char c,char newc);
	int ToInt() const;
	float ToFloat() const;
	void Delete(const int& count);

	char First();
	char Last();

	//void Parse(const char* separators, Array<String>& out);
};



#endif
