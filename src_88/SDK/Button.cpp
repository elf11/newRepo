
#include "TankIncludes.h"


Button::Button(HudManager *Parent) : HudBaseObject(Parent)
{
	type = htButton;

	text = "Test";
	textLength = 4;

	enav1 = 17.0/257;
	enau1 = 20.0/513;
	enav2 = 90.0/257;
	enau2 = 174.0/513;

	v1 = 17.0/257;
	u1 = 189.0/513;
	v2 = 90.0/257;
	u2 = 345.0/513;

	posx = 200;
	posy = 350;

	width = 100;
	height = 100;

	enabled = 1;
	visible = 1;
	down = 0;
	action = NULL;

	Texture = GAME->TexMan->GetTexture("buttons.png");
}

Button::~Button(void)
{

}

int Button::IsInside(int x, int y)
{
	if(!(this->visible))
	{
		return 0;
	}
	if ((this->posx <= x) && (x < (this->posx + this->width)))
	{
		if((this->posy <= y) && (y < (this->posy + this->height)))
		{
			return 1;
		}
	}

	if (down)
	{
		return 1;
	}

	return 0;
}

int Button::OnMouseDown(int x, int y)
{
	if(IsInside(x,y))
	{
		this->down = 1;
		return 1;
	}

	return 0;
}

int Button::OnMouseUp(int x, int y)
{
	this->down = 0;
	if(IsInside(x,y))
	{
		if(action != NULL)
		{
			action;
		}
		return 1;
	}

	return 0;
}

int Button::OnMouseMove(int x, int y)
{
	if(IsInside(x,y))
	{
		if (down == 0)
		{
			if (Owner->MouseDown > 0)
			{
				return 0;
			}
		}
		return 1;
	}

	return 0;
}

int Button::OnKeyDown(int key)
{
	return 0;
}

int Button::OnKeyUp(int key)
{
	return 0;
}

void Button::Render(void)
{
	GAME->GameRenderer->SetTexture1(Texture);
	if(down == 1)
	{
		GAME->TxtRen->DrawImage(posx,posy,width,height,enau1,enav1,enau2,enav2);
	}
	else
	{
		GAME->TxtRen->DrawImage(posx,posy,width,height,u1,v1,u2,v2);
	}

	int pxlen = GAME->TxtRen->TextPixelLength(text,textLength);
	int pylen = GAME->TxtRen->TextPixelHeight();

	GAME->TxtRen->DrawText(posx + ((width - pxlen) / 2),posy + ((height - pylen) / 2),text,textLength);
}