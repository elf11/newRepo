
#include "TankIncludes.h"

Label::Label(HudManager *Parent) : HudBaseObject(Parent)
{
	type = htLabel;

	text = NULL;
	textLength = 0;

	posx = GAME->WindowWidth - 250;
	posy = 100;

	width = 100;
	height = 100;

	visible = 1;
}

Label::~Label(void)
{

}

void Label::Render(void)
{
	int pxlen = GAME->TxtRen->TextPixelLength(text,textLength);
	int pylen = GAME->TxtRen->TextPixelHeight();

	GAME->TxtRen->DrawText(posx + ((width - pxlen) / 2),posy + ((height - pylen) / 2),text,textLength);
}