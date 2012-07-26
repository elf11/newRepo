#include "Texture2D.h"
#include "OpenGLES20.h"
#include <string.h>
#include "..\..\..\platforms\win32\include\fs\FileMgr.h"
//#include "PVRTC.h"
//#include "S3TC.h"
//#include "ATC.h"
#include "debug.h"


const Texture2D * const Texture2D::Empty = new Texture2D(true);


unsigned char * Texture2D::DataBuffer       = NULL;
unsigned int    Texture2D::DataBufferSize   = 0;

unsigned char * Texture2D::GetDataBuffer(const unsigned int size)
{
    if(size > DataBufferSize)
    {
        if(DataBuffer)
            delete [] DataBuffer;
        DataBufferSize = size;
        DataBuffer = new unsigned char[DataBufferSize];
    }
    return DataBuffer;
}

void Texture2D::UpdateDataBuffer()
{
    static unsigned int texDatBufferSample = 0;
    static unsigned int texDatBufferNumTex = 0;
    
    if(DataBuffer)
    {
        if(texDatBufferNumTex != numElements)
        {
            texDatBufferNumTex = numElements;
            texDatBufferSample = 0;
        }
        else
        {
            ++texDatBufferSample;
            if (texDatBufferSample > 100)
            {
                delete [] DataBuffer;
                DataBuffer = NULL;
                DataBufferSize = 0;
                texDatBufferNumTex = 0;
                texDatBufferSample = 0;
            }
        }
    }
}

Texture2D::Buffer::Buffer()
{
	width = height = format = nMipMaps = 0;
	ptr = NULL;
}

Texture2D::Texture2D(bool empty)
{
	if(empty)	Id = 0;
	else		Id = GenerateId();
	this->format	= 0;
	this->width		= 0;
	this->height	= 0;
	//this->filter	= NULL;
	//this->wrap		= NULL;
	this->path		= NULL;
	this->searchCtrl= 0;
	this->mipBias	= 0;
	this->refCount	= 0;
}

Texture2D::Texture2D(unsigned int format, unsigned int width, unsigned int height) : Id(GenerateId())
{
	//this->filter	= NULL;
	//this->wrap		= NULL;
	this->path		= NULL;
	this->searchCtrl= 0;
	this->mipBias	= 0;
	this->refCount	= 0;
	
	Buffer buf;
	buf.format = format;
	buf.width = width;
	buf.height = height;
	UploadFromBuffer(&buf, 0);
}

Texture2D::~Texture2D()
{
	Unload();
	if(path != NULL)
		delete [] path;
}

unsigned int Texture2D::GenerateId()
{
	unsigned int id;
	glGenTextures(1, &id);
	return id;
}

unsigned Texture2D::MemorySize() const
{
    unsigned size = 0;
    if (IsLoaded())
    {
        size = width * height;
        switch (format)
        {
                //case GL_ALPHA:
                //case GL_LUMINANCE:
                //    break;
            case GL_LUMINANCE_ALPHA:
            case GL_RGBA4:
            case GL_RGB565:
            case GL_RGB5_A1:
                size = size << 1; break;
            case GL_RGB:
            case GL_RGBA:
                size = size << 2; break;
            case 0x8C00://GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
            case 0x8C02://GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
            case 0x83F0://GL_COMPRESSED_RGB_S3TC_DXT1;
            case 0x83F1://GL_COMPRESSED_RGBA_S3TC_DXT1;
            case 0x83F2://GL_COMPRESSED_RGBA_S3TC_DXT3;
            case 0x83F3://GL_COMPRESSED_RGBA_S3TC_DXT5;
            case 0x8C92://GL_ATC_RGB_AMD;
            case 0x8C93://GL_ATC_RGBA_EXPLICIT_ALPHA_AMD;
            case 0x87EE://GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD;
            case 0x8D64://GL_ETC1_RGB8;
                size = size >> 1; break;
            case 0x8C01://GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
            case 0x8C03://GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
                size = size >> 2; break;
        }
        
		/*
        if(filter && filter->FilterModeMin >= GL_NEAREST_MIPMAP_NEAREST)
            size = (size << 2) / 3;
		*/
	}
    
    return size;
}

unsigned Texture2D::TotalMemorySize()
{
    static unsigned lastSize = 0;
    unsigned size = 0;
    const Texture2D *t = NULL;
    for(const Texture2D *const* ptr = array, *const*const end = ptr + numElements; ptr < end; ++ptr)
    {
        t = *ptr;
        size += (*ptr)->MemorySize();
    }
    
    if(size != lastSize)
    {
        lastSize = size;
        DEBUG_OUT(">>>>>> Begin Texture Memory <<<<<<");
        for(const Texture2D *const* ptr = array, *const*const end = ptr + numElements; ptr < end; ++ptr)
        {
            t = *ptr;
			if (t->IsLoaded())
			{
				const char *const name = t->path ? t->path : "CUSTOM";
				//const char *const mipmap = t->filter && t->filter->FilterModeMin >= GL_NEAREST_MIPMAP_NEAREST ? "(MipMaps)" : "";
				//DEBUG_OUT("%s\t\t%ux%u\t\t%u\t\t%s", name, t->width, t->height, t->MemorySize(), mipmap);
			}
        }
        
        DEBUG_OUT(">>>>>> Texture Memory: %u <<<<<<", size);
    }
    return size;
}

void Texture2D::GenerateSearchCtrl()
{
	searchCtrl = 0;
	if(path != NULL)
		for(const char *c = path; *c != '\0'; searchCtrl += *(c++));
}

Texture2D * Texture2D::Find(const char *file)
{
	if(file == NULL) return NULL;
	
	unsigned int searchCtrl = 0;
	for(const char *c = file; *c != '\0' ; searchCtrl += *(c++));
	
	for(Texture2D *const* t = array, *const*const end = array + numElements; t < end; ++t)
		if((*t)->path && (*t)->searchCtrl == searchCtrl && strcmp((*t)->path, file) == 0)
			return (*t);
	
	return NULL;
}

void Texture2D::InvalidateAll()
{
	for(Texture2D *const* t = array, *const*const end = array + numElements; t < end; ++t)
		(*t)->Id = 0;
}

void Texture2D::GenerateMipMaps(unsigned char *data)
{
#ifndef SOFTWARE_GENERATE_MIPMAP
	glGenerateMipmap(GL_TEXTURE_2D);
#else
	if(data == NULL)
		return;
	
	unsigned bpp = 0;
	
	switch (format)
	{
		//only these are supported for the moment
		case GL_RGBA:				bpp = 4; break;
		case GL_RGB:				bpp = 3; break;
		case GL_LUMINANCE_ALPHA:	bpp = 2; break;
		case GL_LUMINANCE:		
		case GL_ALPHA:				bpp = 1; break;
	}
	
	if(bpp == 0)
		return;
	
	unsigned srcW = width;
	unsigned srcH = height;
	unsigned dstW = width >> 1;
	unsigned dstH = height >> 1;
	unsigned srcLW = srcW * bpp;
	unsigned char *buf = new unsigned char[dstW * dstH * bpp];
	unsigned char *buf4 = NULL;
	unsigned level = 1;
	unsigned med = 0, i,j,dstWbpp;
	unsigned char *bSrc = data, *pSrc, *pEnd, *pEndLine,
				  *bDst = buf, *pDst, *src, *dst;
	
	bool _1D_mip_map = false;
	
	for(;;)
	{
		srcLW		= srcW * bpp;
		
		pSrc		= bSrc;
		pEndLine	= bSrc + srcLW;
		pEnd		= bSrc + (srcH * srcLW);
		
		pDst		= bDst;
		
		if(_1D_mip_map)
		{
			while(pSrc < pEnd)
			{
				for(unsigned i = 0; i < bpp; ++i, ++pDst, ++pSrc)
				{
					med = *pSrc + *(pSrc + bpp);
					med = med >> 1;
					*pDst = (unsigned char) med;
				}
				pSrc += bpp;
			}
		}
		else
		{
			while(pSrc < pEnd)
			{
				for(unsigned i = 0; i < bpp; ++i, ++pDst, ++pSrc)
				{
					med = *pSrc + *(pSrc + bpp) + *(pSrc + srcLW) + *(pSrc + srcLW + bpp);
					med = med >> 2;
					*pDst = (unsigned char) med;
				}
				pSrc += bpp;
				
				if (pSrc == pEndLine)
				{
					pSrc += srcLW;
					pEndLine += 2 * srcLW;
				}
			}
		}
		
		dstWbpp = dstW * bpp;
		med = dstWbpp % 4;
		if(med > 0 && dstH > 1)		//4-byte align each line of pixels
		{
			med = 4 - med;
			if(buf4 == NULL)
				buf4 = new unsigned char [(dstWbpp + med) * dstH];
			
			src = bDst;
			dst = buf4;
	
			for(i = 0; i < dstH; ++i, dst += med)
				for(j = 0; j < dstWbpp; ++j)
					*(dst++) = *(src++);
			glTexImage2D(GL_TEXTURE_2D, level, format, dstW, dstH, 0, format, GL_UNSIGNED_BYTE, buf4);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, level, format, dstW, dstH, 0, format, GL_UNSIGNED_BYTE, bDst);
		}
		
		pEnd = bSrc;
		bSrc = bDst;
		bDst = pEnd;
		
		srcW = dstW;
		srcH = dstH;
		dstW = dstW >> 1;
		dstH = dstH >> 1;
		
		if (dstW == 0)
		{
			dstW = 1;
			_1D_mip_map = true;	//height only
			if (dstH == 0) break;
		}
		if (dstH == 0)
		{
			dstH = 1;
			_1D_mip_map = true;	//width only
		}
		++level;
	}
	
	delete [] buf;
	if(buf4) delete [] buf4;
	
#endif
}

Texture2D::Buffer Texture2D::LoadBuffer(const char *file, unsigned char *const rawPtr)
{
	Buffer buf;
	
	const unsigned int pathLen = strlen(file);
	const char* end = file + pathLen;
	
	while(*end != '.' && end != file)
		--end;
	
	if(end == file)
		return buf;
	
	unsigned int sz = 0;
	unsigned int loader = 0;
	unsigned int loaderSafe = 0;
#ifdef __OS_LINUX
	sz = strlen(file) + 1;
	char *_file = new char[sz];
	memcpy(_file, file, sz);
			_file[sz - 4] = 'p';
			_file[sz - 3] = 'n';
			_file[sz - 2] = 'g';
			end = &_file[sz-5];
			file = _file;
			//DEBUG_OUT("NEW FILE %s [end=%s]\n", file, end);

#endif
	
	if(strcmp(end,".png") == 0 || 
	   strcmp(end,".jpg") == 0 ||
	   strcmp(end,".jpeg") == 0 ||
	   strcmp(end,".tga") == 0)
		loader = loaderSafe = 1;
	else if(strcmp(end, ".pvr") == 0)
	{

		loader = 2;
		if(Graphics::Instance->Properties.HasRGBPVR4)			loaderSafe = 2;
		else if(Graphics::Instance->Properties.HasRGBS3TCDXT1)	loaderSafe = 3;
		else if(Graphics::Instance->Properties.HasRGBATC)		loaderSafe = 4;
		else if(Graphics::Instance->Properties.HasRGBETC)		loaderSafe = 5;
		else													loaderSafe = 0;
	}
	else if(strcmp(end, ".dds") == 0)
		loader = loaderSafe = 3;
	else if(strcmp(end, ".atc") == 0)
		loader = loaderSafe = 4;
	else if(strcmp(end, ".etc") == 0)
		loader = loaderSafe = 5;
	else
		loader = loaderSafe = 0;
	
	if(loaderSafe == 1)
	{
		//DEBUG_OUT("DECOMPRESSING FILE WITH SAFE=1\n");
		buf = DecompressImage(file, rawPtr);
		if(buf.ptr)
		{
#if !defined(OS_IOS) && !defined(OS_MACOS)
			if(buf.format == TextureFormat::RGBA8)
			{
				float scale;
				for(unsigned char *p = buf.ptr, *end = p + (buf.width * buf.height * 4); p < end; p += 4)
				{
					scale = float(p[3]) / 255.f;
					p[0] *= scale;
					p[1] *= scale;
					p[2] *= scale;
				}
			}
#endif
		}
	}
	else if(loaderSafe == 2 || loaderSafe == 5) //pvr || etc
	{
		DEBUG_OUT("loading PVR texture\n"); 
		File *s;
		if(loader != loaderSafe)
		{
			sz = strlen(file) + 1;
			char *_file = new char[sz];
			memcpy(_file, file, sz);
			_file[sz - 4] = 'e';
			_file[sz - 3] = 't';
			_file[sz - 2] = 'c';
			s = FILEMGR->Open(_file);
			delete [] _file;
		}
		else s = FILEMGR->Open(file);
		
		if(s)
		{
			PvrHeader header;
			s->Read(&header, sizeof(PvrHeader));
			
			switch (header.dwpfFlags & 0xff)
			{
				case OGL_RGBA_4444:
					buf.format = TextureFormat::RGBA4;
					break;
				case OGL_RGBA_5551:
					buf.format = TextureFormat::RGBA5551;
					break;
				case OGL_RGBA_8888:
					buf.format = TextureFormat::RGBA8;
					break;
				case OGL_RGB_565:
					buf.format = TextureFormat::RGB565;
					break;
				case OGL_RGB_888:
					buf.format = TextureFormat::RGB8;
					break;
				case OGL_I_8:
					buf.format = TextureFormat::Grey;
					break;
				case OGL_AI_88:
					buf.format = TextureFormat::GreyAlpha;
					break;
				case OGL_PVRTC2:
					buf.format = header.dwAlphaBitMask == 0 ? TextureFormat::RGBPVR2 : TextureFormat::RGBAPVR2;
					break;
				case OGL_PVRTC4:
					buf.format = header.dwAlphaBitMask == 0 ? TextureFormat::RGBPVR4 : TextureFormat::RGBAPVR4;
					break;
				case OGL_ETC:
					buf.format = TextureFormat::RGBETC;
					break;
				default:
					delete s;
					return buf;
			}
			
			buf.width  = header.dwWidth;
			buf.height = header.dwHeight;
			buf.nMipMaps = (header.dwpfFlags & PVRTEX_MIPMAP) ? header.dwMipMapCount : 0;
			buf.ptr = rawPtr ? rawPtr : GetDataBuffer(header.dwDataSize);
			s->Read(buf.ptr, header.dwDataSize);
			delete s;
		}
	}
	else if(loaderSafe == 3) //dds
	{
		//DEBUG_OUT("LOADING DDS FILE\n");
		File *s;
		if(loader != loaderSafe)
		{
			sz = strlen(file) + 1;
			char *_file = new char[sz];
			memcpy(_file, file, sz);
			_file[sz - 4] = 'd';
			_file[sz - 3] = 'd';
			_file[sz - 2] = 's';
			s = FILEMGR->Open(_file);
			delete [] _file;
		}
		else s = FILEMGR->Open(file);

		if(s)
		{
			DDSHeader hdds;
			s->Read(&hdds, sizeof(DDSHeader));
			switch (hdds.fourCC)
			{
			case FOURCC_DXT1:
				buf.format = TextureFormat::RGBS3TCDXT1;
				break;
			case FOURCC_DXT3:
				buf.format = TextureFormat::RGBAS3TCDXT3;
				break;
			case FOURCC_DXT5:
				buf.format = TextureFormat::RGBAS3TCDXT5;
				break;
			}

			buf.width  = hdds.width;
			buf.height = hdds.height;
			buf.nMipMaps = hdds.nMipMaps;
			buf.ptr = rawPtr ? rawPtr : GetDataBuffer(s->Size() - sizeof(DDSHeader));
			s->Read(buf.ptr, s->Size() - sizeof(DDSHeader));
			delete s;
		}
	}
	else if(loaderSafe == 4) //atc
	{
		//DEBUG_OUT("loading atc texture\n");
		File *s;
		if(loader != loaderSafe)
		{
			sz = strlen(file) + 1;
			char *_file = new char[sz];
			memcpy(_file, file, sz);
			_file[sz - 4] = 'a';
			_file[sz - 3] = 't';
			_file[sz - 2] = 'c';
			s = FILEMGR->Open(_file);
			delete [] _file;
		}
		else s = FILEMGR->Open(file);
		
		if(s)
		{
			ATCHeader hatc;
			s->Read(&hatc, sizeof(ATCHeader));
			buf.format = hatc.format;
			buf.width  = hatc.width;
			buf.height = hatc.height;
			buf.nMipMaps = hatc.nMipMaps;			
			buf.ptr = rawPtr ? rawPtr : GetDataBuffer(s->Size() - sizeof(ATCHeader));
			s->Read(buf.ptr, s->Size() - sizeof(ATCHeader));
			delete s;
		}
	}
	if(!buf.ptr){
		DEBUG_OUT("Failed to load textures %s\n", file);

	}
	
	if(buf.nMipMaps == 1 && (buf.width > 16 || buf.height > 16))
		buf.nMipMaps = 0;
	return buf;
}

Texture2D * Texture2D::CreateFromBuffer(const Buffer *const buf, const int mipBias)
{
	Texture2D *tex = new Texture2D();
	tex->UploadFromBuffer(buf, mipBias);
	return tex;
}

Texture2D * Texture2D::Load(const char *file, const int mipBias)
{
	Texture2D *tfind = Find(file);
	if(tfind) return tfind;
	//DEBUG_OUT("LOADING TEXTURE %s\n", file);	
	Buffer buf = LoadBuffer(file);
	if(buf.ptr == NULL)
	{
		DEBUG_OUT("CANNOT LOAD TEXTURE %s", file);
		return NULL;
	}
	
	Texture2D *tex = CreateFromBuffer(&buf, mipBias);
	tex->path = new char[strlen(file) + 1];
	strcpy(tex->path, file);
	tex->GenerateSearchCtrl();
	return tex;
}

void Texture2D::UploadFromBuffer(const Buffer *const buf, const int mipBias)
{
	UploadFromBuffer(buf, mipBias);
}

void Texture2D::UploadFromBuffer(const Buffer *const buf, const int mipBias)
{	
	unsigned short	texType = GL_RGBA;
	unsigned short	texFormat = GL_UNSIGNED_BYTE;
	unsigned int texCompressed = 0;
	unsigned int BPP = 32;
	
	switch (buf->format)
	{
		case GL_RGBA4:								texFormat = GL_UNSIGNED_SHORT_4_4_4_4;				BPP = 16; break;
		case GL_RGB5_A1:							texFormat = GL_UNSIGNED_SHORT_5_5_5_1;				BPP = 16; break;
		case GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:	texFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;	texCompressed = 2; BPP = 2; break;
		case GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:	texFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;	texCompressed = 4; BPP = 4; break;
		case GL_RGB565:								texType = GL_RGB; texFormat = GL_UNSIGNED_SHORT_5_6_5;				BPP = 16; break;
		case GL_RGB:								texType = GL_RGB;													BPP = 24; break;
		case GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG:	texFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;	texCompressed = 2; BPP = 2; break;
		case GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG:	texFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;	texCompressed = 4; BPP = 4; break;
		case GL_LUMINANCE:							texType = GL_LUMINANCE;			BPP = 8; break;
		case GL_ALPHA:								texType = GL_ALPHA;				BPP = 8; break;
		case GL_LUMINANCE_ALPHA:					texType = GL_LUMINANCE_ALPHA;	BPP = 16; break;
		case 0x83F0:/*GL_COMPRESSED_RGB_S3TC_DXT1*/ texType = GL_RGB; texFormat = 0x83F0; BPP = 4; texCompressed = 8; break;
		case 0x83F1:/*GL_COMPRESSED_RGBA_S3TC_DXT1*/texFormat = 0x83F1; BPP = 4; texCompressed = 8; break;
		case 0x83F2:/*GL_COMPRESSED_RGBA_S3TC_DXT3*/texFormat = 0x83F2; BPP = 8; texCompressed = 16; break;
		case 0x83F3:/*GL_COMPRESSED_RGBA_S3TC_DXT5*/texFormat = 0x83F3; BPP = 8; texCompressed = 16; break;
		//case ATC_RGB:								texType = GL_RGB; texFormat = ATC_RGB; BPP = 4; texCompressed = 8; break;
		//case ATC_RGBAE:								texFormat = ATC_RGBAE; BPP = 8; texCompressed = 16; break;
		//case ATC_RGBAI:								texFormat = ATC_RGBAI; BPP = 8; texCompressed = 16; break;
		case 0x8D64:/*GL_ETC1_RGB8*/				texType = GL_RGB; texFormat = 0x8D64; BPP = 4; texCompressed = 8; break;
	}

	format	= buf->format;
	width	= buf->width >> mipBias;
	height	= buf->height >> mipBias;
	this->mipBias = mipBias;

	unsigned int sz = 0;
	unsigned int w = buf->width;
	unsigned int h = buf->height;
	unsigned char * texPtr = buf->ptr;
	
	if(this->Id == 0)
	{
		//this->filter= NULL;
		//this->wrap	= NULL;
		this->Id	= GenerateId();
	}
	
	glBindTexture(GL_TEXTURE_2D, Id);
	Graphics::Instance->States.Texture[0] = Graphics::Instance->Texture = this;
	
	switch(buf->format)
	{
		case 0x8C00://GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG
		case 0x8C01://GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
		case 0x8C02://GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG
		case 0x8C03://GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG
		{
			for (unsigned int i = 0; i <= buf->nMipMaps; i++)
			{
				if (texCompressed == 2)
					sz = (Math::Max(w, PVRTC2_MIN_TEXWIDTH) * Math::Max(h, PVRTC2_MIN_TEXHEIGHT) * BPP) >> 3;
				else if (texCompressed == 4)
					sz = (Math::Max(w, PVRTC4_MIN_TEXWIDTH) * Math::Max(h, PVRTC4_MIN_TEXHEIGHT) * BPP) >> 3;
				
				if(i >= mipBias)
					glCompressedTexImage2D(GL_TEXTURE_2D, i - mipBias, texFormat, w, h, 0, sz, texPtr);
				
				texPtr += sz;
				
				w = w >> 1;	if(w == 0) w = 1;
				h = h >> 1;	if(h == 0) h = 1;
			}
			break;
		}
		case 0x83F0://GL_COMPRESSED_RGB_S3TC_DXT1
		case 0x83F1://GL_COMPRESSED_RGBA_S3TC_DXT1
		case 0x83F2://GL_COMPRESSED_RGBA_S3TC_DXT3
		case 0x83F3://GL_COMPRESSED_RGBA_S3TC_DXT5
		case ATC_RGB:	//GL_ATC_RGB_AMD
		case ATC_RGBAE:	//GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
		case ATC_RGBAI:	//GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD
		case 0x8D64://GL_ETC1_RGB8
		{
			for (unsigned int i = 0; i <= buf->nMipMaps; i++)
			{
				sz = ((w + 3) / 4) * ((h + 3) / 4) * texCompressed;
				if(i >= mipBias)
					glCompressedTexImage2D(GL_TEXTURE_2D, i - mipBias, texFormat, w, h, 0, sz, texPtr);
				
				texPtr += sz;
				
				w = w >> 1;	if(w == 0) w = 1;
				h = h >> 1;	if(h == 0) h = 1;
			}
			break;
		}
		default:
		{
			for (unsigned i = 0; i <= buf->nMipMaps; i++)
			{
				sz = (w * h * BPP + 7) / 8;
				if(i >= mipBias)
					glTexImage2D(GL_TEXTURE_2D, i - mipBias, texType, w, h, 0, texType, texFormat, texPtr);				
				texPtr += sz;
				w = w >> 1;	if(w == 0) w = 1;
				h = h >> 1;	if(h == 0) h = 1;
			}
			break;
		}
	}
	
	/*
	if(this->wrap != wrap)
	{
		this->wrap		= wrap;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap->WrapModeU);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap->WrapModeV);
	}
	
	if(this->filter != filter)
	{
		this->filter = filter;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter->FilterModeMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter->FilterModeMag);
        if(filter->Anisotropy > 1.f)
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, filter->Anisotropy);
	}
	
	if(buf->nMipMaps == 0 && filter->FilterModeMin >= GL_NEAREST_MIPMAP_NEAREST)
		GenerateMipMaps(buf->ptr);
	*/
}

/*
void Texture2D::SetFilter(const FilterState *const filter)
{
    if(this->filter != filter)
	{
        if(Graphics::Instance->States.Texture[0] != this)
        {
            glBindTexture(GL_TEXTURE_2D, Id);
            Graphics::Instance->States.Texture[0] = Graphics::Instance->Texture = this;
        }
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter->FilterModeMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter->FilterModeMag);
        if(int(filter->Anisotropy) !=  int(this->filter->Anisotropy))
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, filter->Anisotropy);
        this->filter = filter;
	}
}

void Texture2D::SetWrap(const WrapState *constwrap)
{
    if(this->wrap != wrap)
	{
        if(Graphics::Instance->States.Texture[0] != this)
        {
            glBindTexture(GL_TEXTURE_2D, Id);
            Graphics::Instance->States.Texture[0] = Graphics::Instance->Texture = this;
        }
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap->WrapModeU);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap->WrapModeV);
        this->wrap = wrap;
	}
}

*/

Texture2D * Texture2D::LoadRAW(const unsigned int format, const char *file, const unsigned int width, const unsigned int height)
{
	Texture2D *tfind = Find(file);
	if(tfind && tfind->format == format) return tfind;
	
	File *s = FILEMGR->Open(file);
	if(s == NULL)
	{
		DEBUG_OUT("CANNOT LOAD TEXTURE %s", file);
		return NULL;
	}
	
	Buffer buf;
	buf.format = format;
	buf.width = width;
	buf.height = height;
	buf.ptr = GetDataBuffer(s->Size());
	s->Read(buf.ptr, s->Size());
	delete s;
	
	Texture2D *tex = CreateFromBuffer(&buf);
	tex->path = new char[strlen(file) + 1];
	strcpy(tex->path, file);
	tex->GenerateSearchCtrl();
	return tex;
}

Texture2D * Texture2D::LoadGreyAlphaFromGrey(const char *file, const unsigned int width, const unsigned int height)
{
	Texture2D *tfind = Find(file);
	if(tfind && tfind->format == TextureFormat::GreyAlpha) return tfind;
	
	File *s = FILEMGR->Open(file);
	if(s == NULL)
	{
		DEBUG_OUT("CANNOT LOAD TEXTURE %s", file);
		return NULL;
	}
	
	Buffer buf;
	buf.format = TextureFormat::GreyAlpha;
	buf.width = width;
	buf.height = height;
	buf.ptr = GetDataBuffer(s->Size() * 2);
	s->Read(buf.ptr, s->Size());
	
	for(unsigned char *v = buf.ptr + s->Size() - 1, *vend = buf.ptr - 1, *px = buf.ptr + (s->Size()*2) - 2; v > vend; px -= 2, --v)
		*px = *(px + 1) = *v;
	delete s;

	Texture2D *tex = CreateFromBuffer(&buf, 0);
	tex->path	= new char[strlen(file) + 1];
	strcpy(tex->path, file);
	tex->GenerateSearchCtrl();
	return tex;
}

Texture2D * Texture2D::LoadGreyAlphaZeroFromGrey(const char *file, const unsigned int width, const unsigned int height)
{
	Texture2D *tfind = Find(file);
	if(tfind && tfind->format == TextureFormat::GreyAlpha) return tfind;
	
	File *s = FILEMGR->Open(file);
	if(s == NULL)
	{
		DEBUG_OUT("CANNOT LOAD TEXTURE %s", file);
		return NULL;
	}
	
	Buffer buf;
	buf.format = TextureFormat::GreyAlpha;
	buf.width = width;
	buf.height = height;
	buf.ptr = GetDataBuffer(s->Size() * 2);
	s->Read(buf.ptr, s->Size());
	
	for(unsigned char *v = buf.ptr + s->Size() - 1, *vend = buf.ptr - 1, *px = buf.ptr + (s->Size()*2) - 2; v > vend; px -= 2, --v)
    {
		*px = *v;
        *(px + 1) = 0;
    }
	delete s;
    
	Texture2D *tex = CreateFromBuffer(&buf, 0);
	tex->path	= new char[strlen(file) + 1];
	strcpy(tex->path, file);
	tex->GenerateSearchCtrl();
	return tex;
}

void Texture2D::Unload()
{
    if(Id > 0)
    {
        if(Graphics::Instance->Texture == this || Graphics::Instance->States.Texture[0] == this)
        {
            Graphics::Instance->Texture = Graphics::Instance->States.Texture[0] = Texture2D::Empty;
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
        if(Graphics::Instance->Texture2 == this || Graphics::Instance->States.Texture[1] == this)
        {
            Graphics::Instance->Texture2 = Graphics::Instance->States.Texture[1] = Texture2D::Empty;
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE0);
        }
        
		glDeleteTextures(1, &Id);
        Id = 0;
    }
}

void Texture2D::Reload()
{
	if(Id == 0 && path != NULL)
	{
		Buffer buf;
		const unsigned int pathLen = strlen(path);
		const char* end = path + pathLen;
		
		while(*end != '.' && end != path)
			--end;
		
		if(strcmp(end, ".png") == 0 || 
		   strcmp(end, ".jpg") == 0 ||
		   strcmp(end, ".jpeg") == 0 ||
		   strcmp(end, ".tga") == 0 ||
		   strcmp(end, ".pvr") == 0 ||
		   strcmp(end, ".dds") == 0 ||
		   strcmp(end, ".atc") == 0 ||
		   strcmp(end, ".etc") == 0) //Load
		{
			buf = LoadBuffer(path);
			if(buf.ptr == NULL)
				return;
			UploadFromBuffer(&buf, mipBias);
		}
		else if(format == TextureFormat::GreyAlpha) //LoadGreyAlphaFromGrey
		{
			File *s = FILEMGR->Open(path);
			if(s == NULL)
				return;
			buf.format = TextureFormat::GreyAlpha;
			buf.width  = width;
			buf.height = height;
			buf.ptr = GetDataBuffer(s->Size() * 2);
			s->Read(buf.ptr, s->Size());
			delete s;
			
			for(unsigned char *v = buf.ptr + s->Size() - 1, *vend = buf.ptr - 1, *px = buf.ptr + (s->Size()*2) - 2; v > vend; px -= 2, --v)
				*px = *(px + 1) = *v;
			
			UploadFromBuffer(&buf, mipBias);
		}
		else //LoadRAW
		{
			File *s = FILEMGR->Open(path);
			if(s == NULL)
				return;
			buf.format = format;
			buf.width = width;
			buf.height = height;
			buf.ptr = GetDataBuffer(s->Size());
			s->Read(buf.ptr, s->Size());
			delete s;
			
			UploadFromBuffer(&buf, mipBias);
		}
	}
}

void Texture2D::IncRefCount()
{
	refCount++;
}

void Texture2D::DecRefCount()
{
	if (refCount > 0)
	{
		refCount--;
		if (refCount==0)
			Unload();
	}
/*	else
	{
		int vz = 0;
		int v1 = 1/vz;
	}*/
}


void ConvertHSVtoRGB(const Vector3 *const hsv, Vector3 *const rgb)
{
	int i;
	float f, p, q, t;
	
	if( hsv->y < 0.001f ) 
	{
		// achromatic (grey)
		rgb->x = rgb->y = rgb->z = hsv->z;
	}
	else
	{
		
		float h = hsv->x;
        if(h >= 360.0)
            h = 0.0;
		h /= 60.f;			// sector 0 to 5
		i = h;
		f = h - i;			// factorial part of h
		p = hsv->z * ( 1.f - hsv->y );
		q = hsv->z * ( 1.f - hsv->y * f );
		t = hsv->z * ( 1.f - hsv->y * ( 1.f - f ) );
		
		switch( i ) {
			case 0:
				rgb->x = hsv->z;
				rgb->y = t;
				rgb->z = p;
				break;
			case 1:
				rgb->x = q;
				rgb->y = hsv->z;
				rgb->z = p;
				break;
			case 2:
				rgb->x = p;
				rgb->y = hsv->z;
				rgb->z = t;
				break;
			case 3:
				rgb->x = p;
				rgb->y = q;
				rgb->z = hsv->z;
				break;
			case 4:
				rgb->x = t;
				rgb->y = p;
				rgb->z = hsv->z;
				break;
			default:		// case 5:
				rgb->x = hsv->z;
				rgb->y = p;
				rgb->z = q;
				break;
		}
	}
}

