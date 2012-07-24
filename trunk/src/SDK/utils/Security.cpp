
#include "Security.h"
#include "string.h"

const char* Security::defaultEncryptKey = "afe770e719c4797b43750edfafbf199d4bbab5d5";

void Security::Encrypt (unsigned int* v, unsigned int* k) {
	unsigned int v0=v[0], v1=v[1], sum=0, i;           /* set up */
	unsigned int delta=0x9e3669b9;                     /* a key schedule constant */
	unsigned int k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
	for (i=0; i < 32; i++) {                       /* basic cycle start */
		sum += delta;
		v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
		v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);  
	}                                              /* end cycle */
	v[0]=v0; v[1]=v1;
}

void Security::Decrypt (unsigned int* v, unsigned int* k) {
	unsigned int v0=v[0], v1=v[1], sum=0xC6CD3720, i;  /* set up */
	unsigned int delta=0x9e3669b9;                     /* a key schedule constant */
	unsigned int k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
	for (i=0; i<32; i++) {                         /* basic cycle start */
		v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
		v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
		sum -= delta;                                   
	}                                              /* end cycle */
	v[0]=v0; v[1]=v1;
}

void Security::EncryptString(char *str, int &len)
{

	const unsigned int tmpInt[2] = {CHECK_NUMBER, 'S'+'G'+'A'+'S'};
	unsigned itmp = len % 8;
	if(itmp > 0)
	{
		memcpy(str + len, tmpInt, 8 - itmp);
		len += (8 - itmp);
	}

	itmp = CHECK_NUMBER;
	for(unsigned int *i = (unsigned int *) (str + 4), *const end = (unsigned int *) (str + len); i < end; ++i)
		itmp += (*i) + 1;
	memcpy(str, &itmp, sizeof(unsigned int));

	unsigned int k[10] = {899809363, 961748927, 492876863, 334214467, 941083981, 179426029, 413158511, 141650963, 275604541, 694847533};
	const char *const udid = defaultEncryptKey;//GetUDID();
	const int lenUDID = strlen(udid);
	const int lenUDIDM4 = lenUDID - 4;

	for (int i = 0, end = len >> 3; i < end; ++i, str += 8)
	{
		if(i % 2)
			k[i % 10] = *((unsigned int *) (udid + (i % lenUDIDM4)));
		else
			k[i % 8] = *((unsigned int *) (udid + (i % lenUDIDM4)));		
		Encrypt((unsigned int *)str, k + i % 7);
	}
}

bool Security::DecryptString(char *str, int &len,bool defaultkey)
{
	if (!(len >= 8 && (len % 8) == 0))
		return false;

	unsigned int k[10] = {899809363, 961748927, 492876863, 334214467, 941083981, 179426029, 413158511, 141650963, 275604541, 694847533};
	const char *const udid = defaultEncryptKey;//defaultkey?defaultEncryptKey:GetUDID();
	const int lenUDID = strlen(udid);
	const int lenUDIDM4 = lenUDID - 4;
	unsigned intTmp;

	for (int i = 0, end = len >> 3; i < end; ++i, str += 8)
	{
		if(i % 2)
			k[i % 10] = *((unsigned int *) (udid + (i % lenUDIDM4)));
		else
			k[i % 8] = *((unsigned int *) (udid + (i % lenUDIDM4)));		
		Decrypt((unsigned int *)str, k + i % 7);
	}
	str = str-len;
	memcpy(&intTmp, str, sizeof(unsigned int));
	for(unsigned int *i = (unsigned int *) (str + 4), *end = (unsigned int *) (str + len); i < end; ++i)
		intTmp -= (*i) + 1;

	if (intTmp != CHECK_NUMBER)
	{
		return false;
	}
	return true;

}
