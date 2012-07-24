
#ifndef RENDERER__H
#define RENDERER__H

#include "OpenGLES10.h"
#include "OpenGLES20.h"
#include "VertexDeclarations.h"

class Shader
{
private :
	GLuint sh;
public :
	Shader(GLuint ShaderType,char *FileName);
	~Shader(void);

	GLuint ReturnShader(void);
};

class Program
{
private :
	GLuint pr;
public :
	Program(Shader &Vertex,Shader &Fragment);
	~Program(void);

	GLuint ReturnProgram(void);
};

class Renderer
{
private :
	Matrix const * PerspectiveMat;
	Matrix *CameraMat;
	Matrix *ModelMat;
	
	Matrix TransformMat;

	Program *VertexPosProgram;
	Program *VertexPosColorProgram;
	Program *VertexPosTexProgram;
	Program *VertexPosNormalTexProgram;
	Program *VertexPosColorTexProgram;
	Program *VertexPosNormalColorTexProgram;
	Program *VertexPosNormalColorDualTexProgram;
	Program *VertexPosDualTexProgram;
	Program *VertexPos2DProgram;
	Program *VertexPos2DColorProgram;
	Program *VertexPos2DTexProgram;
	Program *VertexPos2DColorTexProgram;
	Program *VertexPos4DProgram;

	Program *LoadProgram(char *VertexFileName,char *FragmentFileName);

	void MakeTransform(void);
public :
	Renderer(void);
	~Renderer(void);

	void SetPerspective(Matrix const * mat);
	void SetCamera(Matrix *mat);
	void SetModel(Matrix *mat);

	void DrawBuffer(GLuint Mode,VertexPos *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
	void DrawBuffer(GLuint Mode,VertexPosColor *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
	void DrawBuffer(GLuint Mode,VertexPosTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
	void DrawBuffer(GLuint Mode,VertexPosNormalTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
	void DrawBuffer(GLuint Mode,VertexPosColorTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
	void DrawBuffer(GLuint Mode,VertexPosNormalColorTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
	void DrawBuffer(GLuint Mode,VertexPosNormalColorDualTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
	void DrawBuffer(GLuint Mode,VertexPosDualTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
	void DrawBuffer(GLuint Mode,VertexPos2D *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
	void DrawBuffer(GLuint Mode,VertexPos2DColor *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
	void DrawBuffer(GLuint Mode,VertexPos2DTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
	void DrawBuffer(GLuint Mode,VertexPos2DColorTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
	void DrawBuffer(GLuint Mode,VertexPos4D *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize);
};

#endif
