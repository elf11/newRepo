#include "misc.h"

bool wildcardMatch(const char* name, const char* pattern)
{
	//empty strings will fail the match
	if (!name[0])
		return false;

	if (!pattern[0])
		return false;


	//count the number of stars from the beginning
	int nw = 0;	//star count
	int ln = 0;	//char count
	for (int i=0; pattern[i] && (ln==nw); i++)
	{
		if (pattern[i] == '*')
			nw ++;

		ln ++;
	}

	if (nw == ln)
	{
		//we have only stars (including just one) so match anything
		return true;
	}

	int sp=0;
	int pp=0;

	if (pattern[0] != '*')
	{
		//if we have a pattern start, it must match the name start
		while (pattern[pp] && (pattern[pp] != '*'))
		{
			if (pattern[pp] == name[sp])
			{
				pp++;
				sp++;
			}
			else
			{
				//one of the chars doesn't match
				return false;
			}
		}
	}

	if ((pattern[pp] == 0) && (name[sp] == 0))
	{
		//we have a match (no wildcards)
		return true;
	}

	char str[256];
	int sLen = 0;

	char ptr[256];
	int pLen = 0;

	while ((str[sLen]=name[sp+sLen]) != 0)
	{
		sLen++;
	}

	while ((ptr[pLen]=pattern[pp+pLen]) != 0)
	{
		pLen++;
	}

	if (ptr[pLen-1] != '*')
	{
		pp = pLen-1;
		sp = sLen-1;

		//if we have a pattern end, it must match the name end
		while (pp && (ptr[pp] != '*'))
		{
			if (ptr[pp] == str[sp])
			{
				pp--;
				sp--;
			}
			else
			{
				//one of the chars doesn't match
				return false;
			}
		}

		str[sp+1] = 0;
		ptr[pp+1] = 0;
	}

	//now the pattern has stars at the start and end
	//also both have been stripped so we can match anywhere

	pp = 0;
	char min[256];
	int mLen;

	char* strptr = str;

	while (ptr[pp])
	{
		//jump over wildcards
		while (ptr[pp] == '*')
		{
			pp++;
		}

		//we're at the end of the pattern and we had only wildcards so match
		if (!ptr[pp])
		{
			return true;
		}

		//now search for a mini-pattern
		mLen = 0;
		while (ptr[pp] && (ptr[pp] != '*'))
		{
			min[mLen++] = ptr[pp++];
		}

		min[mLen] = 0;

		//search for the first occurrence of the mini-pattern in the name
		strptr = strstr(strptr, min);

		//if nothing found, no match
		if (!strptr)
			return false;
	}

	//should never get here (early exit in the while), but to keep the compiler happy
	return true;
}

char* strdup2(const char* s)
{
	char* tmp = new char[strlen(s)+1];
	strcpy(tmp, s);
	return tmp;
}


void populateRandVector(int min, int max, int count, int* vec)
{
	int* list = new int [max - min];

	int n = max - min;

	for (int i=0; i<n; i++)
	{
		list[i] = i+min;
	}

	for (int i=0; i<count; i++)
	{
		int p = rand() % n;

		vec[i] = list[p];
		list[p] = list[n-1];
		n--;
	}
	delete [] list;
}

void scrambleVector(int count, int* vec)
{
	for (int i=0; i<count; i++)
		vec[i] = i;

	if (count < 2)
		return;

	for (int i=0; i<count*2; i++)
	{
		int p1 = rand() % count;
		int p2 = p1;

		while (p2 == p1)
			p2 = rand() % count;

		int tmp = vec[p1];
		vec[p1] = vec[p2];
		vec[p2] = tmp;
	}
}