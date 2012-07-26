//Copyright (C) 2010-2012 by Jason L. McKesson
//This file is licensed under the MIT License.

#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>
#include "OpenGLES10.h"
#include "OpenGLES20.h"

#include "Renderer.h"
#include "BaseObject.h"
#include "Camera.h"
#include "Cube.h"
#include "GameMode.h"
#include "TerrainMap.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "GamePlayer.h"
#include "FileMgr.h"
#include "FileUtils.h"


/*void LoadAllLevelInfo()
{
	//read tinyxml

	//init camera
	//init terrain
	//init all objects

	//objects.Push(new Tank())
	//objects.Push(new Cube())

}*/


void GetParam(char *From,int &len)
{
	len = 0;
	while ((From[len] != ' ') && (From[len] != 0))
	{
		if (From[len] == '"')
		{
			len += 1;
			while (From[len] != '"')
			{
				len += 1;
			}
		}
		len += 1;
	}
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	char *CommandLine = GetCommandLine();
	char *Pnt = CommandLine;
	int len;
	GetParam(Pnt,len);
	Pnt += len + 1;
	GetParam(Pnt,len);
	if (len != 0)
	{
		Renderer *GameRenderer = new Renderer();
		TextureManager *TexMan = new TextureManager();
		ModelManager *mgr = new ModelManager(TexMan,GameRenderer);

		char data[1024];
		memset(data,0,1024);
		strncpy(data,Pnt + 1,len - 2);

		Model * M = mgr->GetModel(data);
		FILE *F = fopen("data.txt","wt");
		fprintf(F,"Nume fisier : %s\n",data);
		fprintf(F,"Bounding Box center : %f %f %f\n",M->BoundBox.center.x,M->BoundBox.center.y,M->BoundBox.center.z);
		fprintf(F,"Bounding Box offset : %f %f %f\n",M->BoundBox.offset.x,M->BoundBox.offset.y,M->BoundBox.offset.z);
		fprintf(F,"Bounding Box length : %f %f %f\n",M->BoundBox.offset.x * 2,M->BoundBox.offset.y * 2,M->BoundBox.offset.z * 2);
		fprintf(F,"Bounding Box point 0 : %f %f %f\n",
			M->BoundBox.center.x - M->BoundBox.offset.x,
			M->BoundBox.center.y - M->BoundBox.offset.y,
			M->BoundBox.center.z - M->BoundBox.offset.z);
		fprintf(F,"Bounding Box point 1 : %f %f %f\n",
			M->BoundBox.center.x + M->BoundBox.offset.x,
			M->BoundBox.center.y - M->BoundBox.offset.y,
			M->BoundBox.center.z - M->BoundBox.offset.z);
		fprintf(F,"Bounding Box point 2 : %f %f %f\n",
			M->BoundBox.center.x - M->BoundBox.offset.x,
			M->BoundBox.center.y + M->BoundBox.offset.y,
			M->BoundBox.center.z - M->BoundBox.offset.z);
		fprintf(F,"Bounding Box point 3 : %f %f %f\n",
			M->BoundBox.center.x + M->BoundBox.offset.x,
			M->BoundBox.center.y + M->BoundBox.offset.y,
			M->BoundBox.center.z - M->BoundBox.offset.z);
		fprintf(F,"Bounding Box point 4 : %f %f %f\n",
			M->BoundBox.center.x - M->BoundBox.offset.x,
			M->BoundBox.center.y - M->BoundBox.offset.y,
			M->BoundBox.center.z + M->BoundBox.offset.z);
		fprintf(F,"Bounding Box point 5 : %f %f %f\n",
			M->BoundBox.center.x + M->BoundBox.offset.x,
			M->BoundBox.center.y - M->BoundBox.offset.y,
			M->BoundBox.center.z + M->BoundBox.offset.z);
		fprintf(F,"Bounding Box point 6 : %f %f %f\n",
			M->BoundBox.center.x - M->BoundBox.offset.x,
			M->BoundBox.center.y + M->BoundBox.offset.y,
			M->BoundBox.center.z + M->BoundBox.offset.z);
		fprintf(F,"Bounding Box point 7 : %f %f %f\n",
			M->BoundBox.center.x + M->BoundBox.offset.x,
			M->BoundBox.center.y + M->BoundBox.offset.y,
			M->BoundBox.center.z + M->BoundBox.offset.z);
		fprintf(F,"Bounding Sphere center : %f %f %f\n",M->BoundSphere.center.x,M->BoundSphere.center.y,M->BoundSphere.center.z);
		fprintf(F,"Bounding Sphere radius : %f\n",M->BoundSphere.radius);

		fclose(F);
		abort();
	}


	GAME->InitGameTime();
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
//	glFrontFace(GL_CCW);

	glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 


	GAME->Load();
}

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void update()
{

	if (!GAME->loaded)
	{
		GAME->Load();
		return;
	}

	GAME->Update();

}

void render()
{
	  GAME->Render();
}

void display()
{
	update();

	render();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	GAME->WindowWidth = w;
	GAME->WindowHeight = h;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void MakeKeyDown(int k)
{
	GAME->HudMan->KeyDownEvent(k);
}

void MakeKeyUp(int k)
{
	GAME->HudMan->KeyUpEvent(k);
}

void MakeMouseDown(int x,int y)
{
	GAME->HudMan->MouseDownEvent(x,y);
}

void MakeMouseUp(int x,int y)
{
	GAME->HudMan->MouseUpEvent(x,y);
}

void MakeMousePos(int x,int y)
{
	GAME->HudMan->MouseMoveEvent(x,y);
}
