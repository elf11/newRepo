#ifndef DATA_STREAM_H
#define DATA_STREAM_H


class DataBuffer
{
	protected:
		unsigned char* m_buf;
		int 	m_pos;
		
	public:
	
	DataBuffer(unsigned char* buf): m_buf(buf), m_pos(0){ };	
	
	void SetPosition(int pos) {m_pos = pos;}
	int  GetPosition() {return m_pos;}
	
	void 			WriteU8	(unsigned char val);
	unsigned char 	ReadU8	();
	
	void 			WriteS8	(char val);
	char			ReadS8	();
	
	void 			WriteU16 (unsigned short val);	
	unsigned short  ReadU16	 ();
	
	void 			WriteS16 (short val);
	short			ReadS16  ();
	
	void 			WriteU32 (unsigned int val);
	unsigned int	ReadU32	 ();
	
	void 			WriteS32 (int val);
	int				ReadS32	 ();
	
	void 			WriteF32 (float val);
	float			ReadF32	 ();	
	
	void 			SkipBytes(int size) {m_pos += size;}
	
	void 			WriteBytes(const unsigned char* bytes, int size);
	void			ReadBytes (unsigned char* bytes, int size);
};

#endif //DATA_STREAM_H