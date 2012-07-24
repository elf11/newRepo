
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Renderer.h"

char *LoadShaderSourceFromFile(char *FileName)
{
	//Deschide fisierul
	FILE *F = fopen(FileName,"rt");
	Assert(F != 0,"Unable to load shader source file.");

	//Afla lungimea fisierului
	fseek(F,0,SEEK_END);
	long size = ftell(F);
	fseek(F,0,SEEK_SET);

	//Initializeaza bufferul
	char *temp = new char[size + 1];
	memset(temp,0,size + 1);

	//Citeste sursa
	fread(temp,1,size,F);

	//Inchide fisierul
	fclose(F);

	//Intoarce bufferul unde se afla sursa
	return temp;
}

GLuint CreateShader(GLuint ShaderType,char *Source)
{
	GLuint shader = glCreateShader(ShaderType);

	glShaderSource(shader,1,(const GLchar **)(&Source),NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader,GL_COMPILE_STATUS,&status);

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		Assert(!(ShaderType == GL_VERTEX_SHADER),"Unable to compile vertex shader.");
//		Assert(!(ShaderType == GL_GEOMETRY_SHADER),"Unable to compile geometry shader.");
		Assert(!(ShaderType == GL_FRAGMENT_SHADER),"Unable to compile fragment shader.");

		Assert(1,strInfoLog);

		delete[] strInfoLog;
	}

	return shader;
}

void DeleteShader(GLuint Shader)
{
	glDeleteShader(Shader);
}

GLuint CreateProgram(GLuint *Shaders,int Number,int ComponentMask)
{
	GLuint program = glCreateProgram();

	for (int i = 0;i < Number;i += 1)
	{
		glAttachShader(program,Shaders[i]);
	}

	if (ComponentMask & elmPosition3Mask)
	{
		glBindAttribLocation(program,elmPosition3,"position3");
	}
	if (ComponentMask & elmNormalMask)
	{
		glBindAttribLocation(program,elmNormal,"normal");
	}
	if (ComponentMask & elmColorMask)
	{
		glBindAttribLocation(program,elmColor,"color");
	}
	if (ComponentMask & elmTex1Mask)
	{
		glBindAttribLocation(program,elmTex1,"tex1");
	}
	if (ComponentMask & elmTex2Mask)
	{
		glBindAttribLocation(program,elmTex2,"tex2");
	}
	if (ComponentMask & elmPosition2Mask)
	{
		glBindAttribLocation(program,elmPosition2,"position2");
	}
	if (ComponentMask & elmPosition3Mask)
	{
		glBindAttribLocation(program,elmPosition3,"w");
	}

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		Assert(1,"Unable to link program.");

		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);

		Assert(1,strInfoLog);
		delete[] strInfoLog;
	}

	for (int i = 0;i < Number;i += 1)
	{
		glDetachShader(program,Shaders[i]);
	}

	return program;
}

void DestroyProgram(GLuint Program)
{
	glDeleteProgram(Program);
}

Shader::Shader(GLuint ShaderType,char *FileName)
{
	char *Source = LoadShaderSourceFromFile(FileName);
	sh = CreateShader(ShaderType,Source);
	delete[] Source;
}

Shader::~Shader(void)
{
	DeleteShader(sh);
}

GLuint Shader::ReturnShader(void)
{
	return sh;
}

Program::Program(Shader &Vertex,Shader &Fragment,int ComponentMask)
{
	GLuint Shaders[2];
	Shaders[0] = Vertex.ReturnShader();
	Shaders[1] = Fragment.ReturnShader();
	pr = CreateProgram(Shaders,2,ComponentMask);
}

Program::~Program(void)
{
	DestroyProgram(pr);
}

GLuint Program::ReturnProgram(void)
{
	return pr;
}

Program *Renderer::LoadProgram(char *VertexFileName,char *FragmentFileName,int ComponentMask)
{
	Shader *s1 = new Shader(GL_VERTEX_SHADER,VertexFileName);
	Shader *s2 = new Shader(GL_FRAGMENT_SHADER,FragmentFileName);
	Program *pr = new Program(*s1,*s2,ComponentMask);
	delete s1;
	delete s2;
	return pr;
}

Renderer::Renderer(void)
{
//	VertexPosProgram = LoadProgram("VertexPos.vsh","VertexPos.fsh",elmPosition3Mask);
	VertexPosColorProgram = LoadProgram("VertexPosColor.vsh","VertexPosColor.fsh",elmPosition3Mask | elmColorMask);
//	VertexPosTexProgram = LoadProgram("VertexPosTex.vsh","VertexPosTex.fsh",elmPosition3Mask | elmTex1Mask);
//	VertexPosNormalTexProgram = LoadProgram("VertexPosNormalTex.vsh","VertexPosNormalTex.fsh",elmPosition3Mask | elmNormalMask | elmTex1Mask);
//	VertexPosColorTexProgram = LoadProgram("VertexPosColorTex.vsh","VertexPosColorTex.fsh",elmPosition3Mask | elmColorMask | elmTex1Mask);
//	VertexPosNormalColorTexProgram = LoadProgram("VertexPosNormalColorTex.vsh","VertexPosNormalColorTex.fsh",elmPosition3Mask | elmNormalMask | elmColorMask | elmTex1Mask);
//	VertexPosNormalColorDualTexProgram = LoadProgram("VertexPosNormalColorDualTex.vsh","VertexPosNormalColorDualTex.fsh",elmPosition3Mask | elmNormalMask | elmColorMask | elmTex1Mask | elmTex2Mask);
//	VertexPosDualTexProgram = LoadProgram("VertexPosDualTex.vsh","VertexPosDualTex.fsh",elmPosition3Mask | elmTex1Mask | elmTex2Mask);
//	VertexPos2DProgram = LoadProgram("VertexPos2D.vsh","VertexPos2D.fsh",elmPosition2Mask);
//	VertexPos2DColorProgram = LoadProgram("VertexPos2DColor.vsh","VertexPos2DColor.fsh",elmColorMask | elmPosition2Mask);
//	VertexPos2DTexProgram = LoadProgram("VertexPos2DTex.vsh","VertexPos2DTex.fsh",elmTex1Mask | elmPosition2Mask);
//	VertexPos2DColorTexProgram = LoadProgram("VertexPos2DColorTex.vsh","VertexPos2DColorTex.fsh",elmColorMask | elmTex1Mask | elmPosition2Mask);
//	VertexPos4DProgram = LoadProgram("VertexPos4D.vsh","VertexPos4D.fsh",elmPosition3Mask | elmWMask);
}

Renderer::~Renderer(void)
{
/*	delete VertexPosProgram;*/
	delete VertexPosColorProgram;
/*	delete VertexPosTexProgram;
	delete VertexPosNormalTexProgram;
	delete VertexPosColorTexProgram;
	delete VertexPosNormalColorTexProgram;
	delete VertexPosNormalColorDualTexProgram;
	delete VertexPosDualTexProgram;
	delete VertexPos2DProgram;
	delete VertexPos2DColorProgram;
	delete VertexPos2DTexProgram;
	delete VertexPos2DColorTexProgram;
	delete VertexPos4DProgram;*/
}

void Renderer::MakeTransform(void)
{
	TransformMat = (*PerspectiveMat) * (*CameraMat) * (*ModelMat);
}

void Renderer::SetPerspective(Matrix const * mat)
{
	PerspectiveMat = mat;
}

void Renderer::SetCamera(Matrix *mat)
{
	CameraMat = mat;
}

void Renderer::SetModel(Matrix *mat)
{
	ModelMat = mat;
}

void Renderer::DrawBuffer(GLuint Mode,VertexPos *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPosProgram->ReturnProgram();
	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition3);
					   
	glVertexAttribPointer(elmPosition3,3,GL_FLOAT,GL_FALSE,sizeof(VertexPos),&VertexBuffer->pos);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition3);
}

void Renderer::DrawBuffer(GLuint Mode,VertexPosColor *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPosColorProgram->ReturnProgram();

	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition3);
	glEnableVertexAttribArray(elmColor);

	glVertexAttribPointer(elmPosition3,3,GL_FLOAT,GL_FALSE,sizeof(VertexPosColor),&VertexBuffer->pos);
	glVertexAttribPointer(elmColor,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(VertexPosColor),&VertexBuffer->color);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition3);
	glDisableVertexAttribArray(elmColor);
}

void Renderer::DrawBuffer(GLuint Mode,VertexPosTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPosTexProgram->ReturnProgram();
	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition3);
	glEnableVertexAttribArray(elmTex1);

	glVertexAttribPointer(elmPosition3,3,GL_FLOAT,GL_FALSE,sizeof(VertexPosTex),&VertexBuffer->pos);
	glVertexAttribPointer(elmTex1,2,GL_FLOAT,GL_FALSE,sizeof(VertexPosTex),&VertexBuffer->tex);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition3);
	glDisableVertexAttribArray(elmTex1);
}

void Renderer::DrawBuffer(GLuint Mode,VertexPosNormalTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPosNormalTexProgram->ReturnProgram();
	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition3);
	glEnableVertexAttribArray(elmNormal);
	glEnableVertexAttribArray(elmTex1);

	glVertexAttribPointer(elmPosition3,3,GL_FLOAT,GL_FALSE,sizeof(VertexPosNormalTex),&VertexBuffer->pos);
	glVertexAttribPointer(elmNormal,3,GL_FLOAT,GL_FALSE,sizeof(VertexPosNormalTex),&VertexBuffer->normal);
	glVertexAttribPointer(elmTex1,2,GL_FLOAT,GL_FALSE,sizeof(VertexPosNormalTex),&VertexBuffer->tex);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition3);
	glDisableVertexAttribArray(elmNormal);
	glDisableVertexAttribArray(elmTex1);
}

void Renderer::DrawBuffer(GLuint Mode,VertexPosColorTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPosColorTexProgram->ReturnProgram();
	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition3);
	glEnableVertexAttribArray(elmColor);
	glEnableVertexAttribArray(elmTex1);

	glVertexAttribPointer(elmPosition3,3,GL_FLOAT,GL_FALSE,sizeof(VertexPosColorTex),&VertexBuffer->pos);
	glVertexAttribPointer(elmColor,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(VertexPosColorTex),&VertexBuffer->color);
	glVertexAttribPointer(elmTex1,2,GL_FLOAT,GL_FALSE,sizeof(VertexPosColorTex),&VertexBuffer->tex);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition3);
	glDisableVertexAttribArray(elmColor);
	glDisableVertexAttribArray(elmTex1);
}

void Renderer::DrawBuffer(GLuint Mode,VertexPosNormalColorTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPosNormalColorTexProgram->ReturnProgram();
	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition3);
	glEnableVertexAttribArray(elmNormal);
	glEnableVertexAttribArray(elmColor);
	glEnableVertexAttribArray(elmTex1);

	glVertexAttribPointer(elmPosition3,3,GL_FLOAT,GL_FALSE,sizeof(VertexPosNormalColorTex),&VertexBuffer->pos);
	glVertexAttribPointer(elmNormal,3,GL_FLOAT,GL_FALSE,sizeof(VertexPosNormalColorTex),&VertexBuffer->normal);
	glVertexAttribPointer(elmColor,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(VertexPosNormalColorTex),&VertexBuffer->color);
	glVertexAttribPointer(elmTex1,2,GL_FLOAT,GL_FALSE,sizeof(VertexPosNormalColorTex),&VertexBuffer->tex);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition3);
	glDisableVertexAttribArray(elmNormal);
	glDisableVertexAttribArray(elmColor);
	glDisableVertexAttribArray(elmTex1);
}

void Renderer::DrawBuffer(GLuint Mode,VertexPosNormalColorDualTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPosNormalColorDualTexProgram->ReturnProgram();
	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition3);
	glEnableVertexAttribArray(elmNormal);
	glEnableVertexAttribArray(elmColor);
	glEnableVertexAttribArray(elmTex1);
	glEnableVertexAttribArray(elmTex2);

	glVertexAttribPointer(elmPosition3,3,GL_FLOAT,GL_FALSE,sizeof(VertexPosNormalColorDualTex),&VertexBuffer->pos);
	glVertexAttribPointer(elmNormal,3,GL_FLOAT,GL_FALSE,sizeof(VertexPosNormalColorDualTex),&VertexBuffer->normal);
	glVertexAttribPointer(elmColor,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(VertexPosNormalColorDualTex),&VertexBuffer->color);
	glVertexAttribPointer(elmTex1,2,GL_FLOAT,GL_FALSE,sizeof(VertexPosNormalColorDualTex),&VertexBuffer->tex);
	glVertexAttribPointer(elmTex2,2,GL_FLOAT,GL_FALSE,sizeof(VertexPosNormalColorDualTex),&VertexBuffer->tex2);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition3);
	glDisableVertexAttribArray(elmNormal);
	glDisableVertexAttribArray(elmColor);
	glDisableVertexAttribArray(elmTex1);
	glDisableVertexAttribArray(elmTex2);
}

void Renderer::DrawBuffer(GLuint Mode,VertexPosDualTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPosDualTexProgram->ReturnProgram();
	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition3);
	glEnableVertexAttribArray(elmTex1);
	glEnableVertexAttribArray(elmTex2);

	glVertexAttribPointer(elmPosition3,3,GL_FLOAT,GL_FALSE,sizeof(VertexPosDualTex),&VertexBuffer->pos);
	glVertexAttribPointer(elmTex1,2,GL_FLOAT,GL_FALSE,sizeof(VertexPosDualTex),&VertexBuffer->tex);
	glVertexAttribPointer(elmTex2,2,GL_FLOAT,GL_FALSE,sizeof(VertexPosDualTex),&VertexBuffer->tex2);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition3);
	glDisableVertexAttribArray(elmTex1);
	glDisableVertexAttribArray(elmTex2);
}

void Renderer::DrawBuffer(GLuint Mode,VertexPos2D *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPos2DProgram->ReturnProgram();
	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition2);

	glVertexAttribPointer(elmPosition2,2,GL_FLOAT,GL_FALSE,sizeof(VertexPos2D),&VertexBuffer->pos);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition2);
}

void Renderer::DrawBuffer(GLuint Mode,VertexPos2DColor *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPos2DColorProgram->ReturnProgram();
	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition2);
	glEnableVertexAttribArray(elmColor);

	glVertexAttribPointer(elmPosition2,2,GL_FLOAT,GL_FALSE,sizeof(VertexPos2DColor),&VertexBuffer->pos);
	glVertexAttribPointer(elmColor,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(VertexPos2DColor),&VertexBuffer->color);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition2);
	glDisableVertexAttribArray(elmColor);
}

void Renderer::DrawBuffer(GLuint Mode,VertexPos2DTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPos2DTexProgram->ReturnProgram();
	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition2);
	glEnableVertexAttribArray(elmTex1);

	glVertexAttribPointer(elmPosition2,2,GL_FLOAT,GL_FALSE,sizeof(VertexPos2DTex),&VertexBuffer->pos);
	glVertexAttribPointer(elmTex1,2,GL_FLOAT,GL_FALSE,sizeof(VertexPos2DTex),&VertexBuffer->tex);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition2);
	glDisableVertexAttribArray(elmTex1);
}

void Renderer::DrawBuffer(GLuint Mode,VertexPos2DColorTex *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPos2DColorTexProgram->ReturnProgram();
	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition2);
	glEnableVertexAttribArray(elmColor);
	glEnableVertexAttribArray(elmTex1);

	glVertexAttribPointer(elmPosition2,2,GL_FLOAT,GL_FALSE,sizeof(VertexPos2DColorTex),&VertexBuffer->pos);
	glVertexAttribPointer(elmColor,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(VertexPos2DColorTex),&VertexBuffer->color);
	glVertexAttribPointer(elmTex1,2,GL_FLOAT,GL_FALSE,sizeof(VertexPos2DColorTex),&VertexBuffer->tex);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition2);
	glDisableVertexAttribArray(elmColor);
	glDisableVertexAttribArray(elmTex1);
}

void Renderer::DrawBuffer(GLuint Mode,VertexPos4D *VertexBuffer,unsigned short *IndexBuffer,int IndexBufferSize)
{
	MakeTransform();

	GLuint prg = VertexPos4DProgram->ReturnProgram();
	glUseProgram(prg);

	glEnableVertexAttribArray(elmPosition3);
	glEnableVertexAttribArray(elmW);

	glVertexAttribPointer(elmPosition3,3,GL_FLOAT,GL_FALSE,sizeof(VertexPos4D),&VertexBuffer->pos);
	glVertexAttribPointer(elmW,1,GL_FLOAT,GL_FALSE,sizeof(VertexPos4D),&VertexBuffer->w);

	GLint TMindex = glGetUniformLocation(prg,"TransformMat");
	glUniformMatrix4fv(TMindex,1,GL_FALSE,(const GLfloat *)(&TransformMat));

	glDrawElements(Mode,IndexBufferSize,GL_UNSIGNED_SHORT,IndexBuffer);

	glDisableVertexAttribArray(elmPosition3);
	glDisableVertexAttribArray(elmW);
}
