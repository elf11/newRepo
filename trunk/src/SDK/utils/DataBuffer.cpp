#include "DataBuffer.h"
#include "platform.h"
#include <stdlib.h>
#include <string.h>

void DataBuffer::WriteU8(unsigned char val)
{
	memcpy(m_buf + m_pos, &val, 1);
	m_pos++;
}
unsigned char DataBuffer::ReadU8()
{
	unsigned char val;
	memcpy(&val, m_buf + m_pos, 1);	
	m_pos++;	
	return val;
}

void DataBuffer::WriteS8(char val)
{
	memcpy(m_buf + m_pos, &val, 1);
	m_pos++;
}

char DataBuffer::ReadS8	()
{
	char val;	
	memcpy(&val, m_buf + m_pos, 1);	
	m_pos++;	
	return val;
}

void DataBuffer::WriteU16(unsigned short val)
{
	memcpy(m_buf + m_pos, &val, 2);
	m_pos+=2;
}

unsigned short DataBuffer::ReadU16()
{
	unsigned short val;	
	memcpy(&val, m_buf + m_pos, 2);	
	m_pos+=2;	
	return val;
}

void DataBuffer::WriteS16(short val)
{
	memcpy(m_buf + m_pos, &val, 2);
	m_pos+=2;
}

short DataBuffer::ReadS16()
{
	short val;	
	memcpy(&val, m_buf + m_pos, 2);	
	m_pos+=2;	
	return val;
}

void DataBuffer::WriteU32 (unsigned int val)
{
	memcpy(m_buf + m_pos, &val, 4);
	m_pos+=4;
}
unsigned int DataBuffer::ReadU32()
{
	unsigned int val;	
	memcpy(&val, m_buf + m_pos, 4);	
	m_pos+=4;	
	return val;
}

void DataBuffer::WriteS32(int val)
{
	memcpy(m_buf + m_pos, &val, 4);
	m_pos+=4;
}

int DataBuffer::ReadS32()
{
	int val;	
	memcpy(&val, m_buf + m_pos, 4);	
	m_pos+=4;	
	return val;
}

void DataBuffer::WriteF32 (float val)
{
	memcpy(m_buf + m_pos, &val, 4);
	m_pos+=4;
}

float DataBuffer::ReadF32()
{
	float val;	
	memcpy(&val, m_buf + m_pos, 4);	
	m_pos+=4;	
	return val;
}

void DataBuffer::WriteBytes(const unsigned char* bytes, int size)
{
	memcpy(m_buf + m_pos, bytes, size);	
	m_pos+=size;	
}

void DataBuffer::ReadBytes (unsigned char* bytes, int size)
{
	memcpy(bytes, m_buf + m_pos, size);
	m_pos+=size;
}
