#pragma once

#include "ManagedArray.h"
#include "Renderer.h"

//#define SOFTWARE_GENERATE_MIPMAP

class Graphics;
class TextureFormat;


class Texture2D : public ManagedArray<Texture2D, 1024>
{
public:
	class Buffer
	{
	public:
		unsigned int	width;
		unsigned int	height;
		unsigned int	format;
		unsigned int	nMipMaps;
		unsigned char*	ptr;
		Buffer();
		
		static bool ReplaceColor(const Buffer *const src, const Vector3* hsvDst, Buffer *const dst, unsigned char* mask);
	};
		
private:
	Texture2D(bool empty = false);
	static unsigned int GenerateId();
	static Buffer DecompressImage(const char *file, unsigned char *const rawPtr = NULL);
	
protected:
	unsigned int			format;
	unsigned int			width;
	unsigned int			height;
	
	//const WrapState		*	wrap;
	//const FilterState	*	filter;
	
	unsigned int			searchCtrl;
			 int			mipBias;
			 int			refCount;
	
	void GenerateMipMaps(unsigned char *data);
	void GenerateSearchCtrl();
public:
	char *path;
	unsigned int Id;
	
	Texture2D(unsigned int format, unsigned int width, unsigned int height);
	virtual ~Texture2D();
	
	inline unsigned int				Format()	const	{ return format; }
	inline unsigned int				Width()		const	{ return width; }
	inline unsigned int				Height()	const	{ return height; }
	
	
	inline bool						IsValid()	const	{ return Id > 0; }
    
    unsigned                        MemorySize() const;
	void UploadFromBuffer(const Buffer *const buf, const int mipBias = 0);
	void Reload();
    void Unload();
    bool IsLoaded() const { return Id > 0; }
	
	void IncRefCount();
	void DecRefCount();

	static const Texture2D * const Empty;
    static unsigned char *  DataBuffer;
    static unsigned int     DataBufferSize;
    
    static unsigned char * GetDataBuffer(const unsigned int size);
    static void            UpdateDataBuffer();
    
	static Buffer LoadBuffer(const char *file, unsigned char *const rawPtr = NULL);
	
	static Texture2D * Load(const char *file, const int mipBias = 0);
	static Texture2D * CreateFromBuffer(const Buffer *const buf, const int mipBias = 0);
	
	static Texture2D * LoadRAW(const unsigned int format, const char *file, const unsigned int width, const unsigned int height);
	static Texture2D * LoadGreyAlphaFromGrey(const char *file, const unsigned int width, const unsigned int height);
    static Texture2D * LoadGreyAlphaZeroFromGrey(const char *file, const unsigned int width, const unsigned int height);
	static Texture2D * Find(const char *file);
	static unsigned    TotalMemorySize();
	static void InvalidateAll();
	
	friend class RenderBuffer;
	friend class Graphics;
};

void ConvertHSVtoRGB(const Vector3 *const hsv, Vector3 *const rgb);
