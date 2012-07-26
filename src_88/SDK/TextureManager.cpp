
#include "TankIncludes.h"

TextureManager::TextureManager(void)
{

}

TextureManager::~TextureManager(void)
{
	for (int i = 0;i < Textures.Length();i += 1)
	{
		delete Textures[i];
	}
}

Texture2D::Texture2D(void)
{
	PixelData = NULL;
}

Texture2D::~Texture2D(void)
{
	if (FileName != NULL)
	{
		free(FileName);
	}
	if (PixelData != NULL)
	{
		free(PixelData);
	}
}

int Texture2D :: LoadFromFile(char * FileName){

	int loadedSize;
	unsigned char *LoaddedData = LoadFileBuffer(FileName,loadedSize);
	
	int x;
	x = LoadBuffer(LoaddedData, loadedSize);
	delete[] LoaddedData;

	return x;
}


#include <png.h>

void userReadData(png_structp pngPtr, png_bytep data, png_size_t length)
{
	unsigned char **BufferData;
	BufferData = (unsigned char **)(png_get_io_ptr(pngPtr));
	memmove(data,(*BufferData),length);
	(*BufferData) += length;
}

int Texture2D :: LoadBuffer(unsigned char * Buffer, int length)
{
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;

	/* Create and initialize the png_struct
     * with the desired error handler
     * functions.  If you want to use the
     * default stderr and longjump method,
     * you can supply NULL for the last
     * three parameters.  We also supply the
     * the compiler header file version, so
     * that we know if the application
     * was compiled with a compatible version
     * of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);

    if (png_ptr == NULL) {
        return 0;
    }

    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        png_destroy_read_struct(&png_ptr, *((png_infopp *)(NULL)),*((png_infopp *)(NULL)));
        return 0;
    }

    /* Set error handling if you are
     * using the setjmp/longjmp method
     * (this is the normal method of
     * doing things with libpng).
     * REQUIRED unless you  set up
     * your own error handlers in
     * the png_create_read_struct()
     * earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, *((png_infopp *)(NULL)));
        /* If we get here, we had a
         * problem reading the file */
        return 0;
    }

    /* Set up the output control if
     * you are using standard C streams */
	png_set_read_fn(png_ptr,(png_voidp)&Buffer, userReadData);

    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);

    /*
     * If you have enough memory to read
     * in the entire image at once, and
     * you need to specify only
     * transforms that can be controlled
     * with one of the PNG_TRANSFORM_*
     * bits (this presently excludes
     * dithering, filling, setting
     * background, and doing gamma
     * adjustment), then you can read the
     * entire image (including pixels)
     * into the info structure with this
     * call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to
     *  expand a palette into RGB
     */
	png_read_info(png_ptr, info_ptr);
//    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, *((png_voidp *)(NULL)));

    width = info_ptr->width;
    height = info_ptr->height;

	PixelData = new unsigned char [width * height * 4];
	png_bytepp row_pointers = new png_bytep[height];
	for (int i = 0; i < height; i++) {
		row_pointers[i] = PixelData + (width * 4 * i);
	}
	png_read_image(png_ptr, row_pointers);

	delete[] row_pointers;
	
	switch (info_ptr->color_type) {
		case PNG_COLOR_TYPE_RGB:
			for (int i = 0;i < height;i += 1)
			{
				for (int j = width - 1;j >= 0;j -= 1)
				{
					PixelData[i * width * 4 + j * 4 + 3] = 255;
					PixelData[i * width * 4 + j * 4 + 2] = PixelData[i * width * 4 + j * 3 + 2];
					PixelData[i * width * 4 + j * 4 + 1] = PixelData[i * width * 4 + j * 3 + 1];
					PixelData[i * width * 4 + j * 4 + 0] = PixelData[i * width * 4 + j * 3 + 0];
				}
			}
			break;
        case PNG_COLOR_TYPE_RGBA:
            break;
        default:
			png_destroy_read_struct(&png_ptr, &info_ptr, ((png_infopp)(0)));
	        return false;
    }

	png_destroy_read_struct(&png_ptr, &info_ptr, ((png_infopp)(0)));


    /* Clean up after the read,
     * and free any memory allocated */



/*	int i,j,z;
	z = width * height * 4;
	for (i = 0,j = 0;i < z;i += 4,j += 3)
	{
		PixelData[i] = Buffer[j];
		PixelData[i + 1] = Buffer[j + 1];
		PixelData[i + 2] = Buffer[j + 2];
		PixelData[i + 3] = 255;
	}*/

	glGenTextures(1,&ptr);	  
	glBindTexture(GL_TEXTURE_2D,ptr);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,PixelData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	return 1;
}

GLuint Texture2D :: getPtr(void){

	 return ptr;

}


Texture2D * TextureManager :: GetTexture(char * FileName){
		
	for(unsigned int i = 0; i < Textures.Length(); i++)
	{
		if(strcmp(FileName,Textures[i]->FileName) == 0)
		{
			return Textures[i];
		}
	}

	Texture2D *newTexture = new Texture2D();
	if (newTexture->LoadFromFile(FileName) != 0)
	{
		Textures.Push(newTexture);
		newTexture->FileName = strdup(FileName);
		newTexture->Manager = this;
		return newTexture;
	}
	else
	{
		delete newTexture;
		return NULL;
	}

}