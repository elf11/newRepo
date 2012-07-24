#ifndef _MISC_H_
#define _MISC_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "RMath.h"
#include "misc.h"
#include "platform.h"
#include "debug.h"
#include <stdarg.h>
#include "stdinc.h"

//extern char* strdup2(const char*);

class TiXmlDocument;
class TiXmlElement;
class CFile;

bool wildcardMatch(const char* name, const char* pattern);
bool parseXML(TiXmlDocument* doc, const char* path);
bool parseXML(TiXmlDocument* doc, CFile* f);
int countXMLSiblings(TiXmlElement* e);

char* strdup2(const char* s);


void populateRandVector(int min, int max, int count, int* vec); //random list between [min, max) 
void scrambleVector(int count, int* vec); //random order of elements from [0, count)


#endif //_MISC_H_
