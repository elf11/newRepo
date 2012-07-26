
#include "TankIncludes.h"

EditBox::EditBox(HudManager *Parent) : HudBaseObject(Parent)
{
	type = htEditBox;

	strcpy(text,"");
	textLength = 0;

	v1 = 118.0/257;
	u1 = 15.0/513;
	v2 = 243.0/257;
	u2 = 488.0/513;

	posx = 200;
	posy = GAME->WindowHeight - 150;

	width = 200;
	height = 100;

	enabled = 1;
	visible = 1;
	focus = 0;

	Texture = GAME->TexMan->GetTexture("Buttons.png");
}

EditBox::~EditBox(void)
{

}

int EditBox::IsInside(int x, int y)
{
	if(!(this->visible))
	{
		return 0;
	}
	if((this->posx <= x) && (x < (this->posx + this->width)))
	{
		if((this->posy <= y) && (y < (this->posy + this->height)))
		{
			return 1;
		}
	}

	return 0;
}

int EditBox::OnMouseDown(int x, int y)
{
	if(IsInside(x,y))
	{
		this->focus = 1;
		Owner->FocusedElement = this;
		return 1;
	}

	this->focus = 0;
	if (Owner->FocusedElement == this)
	{
		Owner->FocusedElement = NULL;
	}
	return 0;
}

int EditBox::OnMouseUp(int x, int y)
{
	if(IsInside(x,y))
	{
		return 1;
	}

	return 0;
}

int EditBox::OnMouseMove(int x, int y)
{
	if(IsInside(x,y))
	{
		if (Owner->MouseDown > 0)
		{
			return 0;
		}
		return 1;
	}

	return 0;
}

int EditBox::OnKeyDown(int key)
{
	char S[2];
	S[0] = key;
	S[1] = 0;
	if(focus == 1)
	{
		if(32 <= key && key <= 126)
		{
			if(textLength < MaxTextLength)
			{
				strcat(text,S);
				textLength += 1;
			}
		}
		else
		{
			if ((key == 8) && (textLength > 0))
			{
				text[textLength - 1] = 0;
				textLength -= 1;
			}
		}
		return 1;
	}

	return 0;
}

int EditBox::OnKeyUp(int key)
{
	return 0;
}

void EditBox::Render(void)
{
	GAME->GameRenderer->SetTexture1(Texture);
	GAME->TxtRen->DrawImage(posx,posy,width,height,u1,v1,u2,v2);


	int pxlen = GAME->TxtRen->TextPixelLength(text,textLength);
	int pylen = GAME->TxtRen->TextPixelHeight();

	GAME->TxtRen->DrawText(posx + ((width - pxlen) / 2),posy + ((height - pylen) / 2),text,textLength);
}