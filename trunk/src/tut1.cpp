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
#include "GameOptions.h"
#include "TerainMap.h"


//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	GAME->InitGameTime();
//	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

}

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	GAME->UpdateGameTime();

	glClearColor(0.0f, 0.3f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GAME->PlayerCamera->Update();
	for (int i = 0;i < 256;i += 1)
	{
		GAME->TestCube[i].Update();
	}
	GAME->TestTerainMap->Update();

	GAME->PlayerCamera->Render();
	for (int i = 0;i < 256;i += 1)
	{
		GAME->TestCube[i].Render();
	}
	GAME->TestTerainMap->Render();

}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	GAME->PlayerCamera->UpdateWindowData(w,h);
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

int KeyState[256];
int MouseInit = 0;
int MouseDown;
int LastMX,LastMY;
int MouseX,MouseY;
int DeltaMX,DeltaMY;

void MakeKeyDown(int k)
{
	KeyState[k] = 1;
}

void MakeKeyUp(int k)
{
	KeyState[k] = 0;
}

void MakeMouseDown(void)
{
	MouseDown = 1;
}

void MakeMouseUp(void)
{
	MouseDown = 0;
}

void MakeMousePos(int x,int y)
{
	if (MouseInit == 0)
	{
		MouseInit = 1;
		LastMX = MouseX = x;
		LastMY = MouseY = y;
	}
	else
	{
		LastMX = MouseX;
		LastMY = MouseY;
		MouseX = x;
		MouseY = y;
	}
	DeltaMX = MouseX - LastMX;
	DeltaMY = MouseY - LastMY;
}
