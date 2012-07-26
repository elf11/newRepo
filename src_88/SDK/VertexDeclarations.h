#pragma once

#include "RMath.h"
#include "Color.h"

enum VertexElement
{
	elmPosition3,
	elmNormal,
	elmColor,
	elmTex1,
	elmTex2,
	elmPosition2,
	elmW
};

enum VertexElementMask
{
	elmPosition3Mask = 1,
	elmNormalMask = 2,
	elmColorMask = 4,
	elmTex1Mask = 8,
	elmTex2Mask = 16,
	elmPosition2Mask = 32,
	elmWMask = 64
};

const int vbtPos					= 0x00;
const int vbtPosColor				= 0x01;
const int vbtPosTex					= 0x02;
const int vbtPosNormalTex			= 0x03;
const int vbtPosColorTex			= 0x04;
const int vbtPosNormalColorTex		= 0x05;
const int vbtPosNormalColorDualTex	= 0x06;
const int vbtPosDualTex				= 0x07;
const int vbtPos2D					= 0x08;
const int vbtPos2DColor				= 0x09;
const int vbtPos2DTex				= 0x0A;
const int vbtPos2DColorTex			= 0x0B;
const int vbtPos4D					= 0x0C;

class VertexPos
{
public:
	Vector3 pos;
};

class VertexPosColor
{
public:
	Vector3 pos;
	Color	color;
};

class VertexPosTex
{
public:
	Vector3 pos;
	Vector2 tex;
};

class VertexPosNormalTex
{
public:
	Vector3 pos;
	Vector3 normal;
	Vector2 tex;
};

class VertexPosColorTex
{
public:
	Vector3 pos;
	Color	color;
	Vector2 tex;
};

class VertexPosNormalColorTex
{
public:
	Vector3 pos;
	Vector3 normal;
	Color	color;
	Vector2 tex;
};

class VertexPosNormalColorDualTex
{
public:
	Vector3 pos;
	Vector3 normal;
	Color	color;
	Vector2 tex;
	Vector2 tex2;
};

class VertexPosDualTex
{
public:
	Vector3 pos;
	Vector2 tex;
	Vector2 tex2;
};

class VertexPos2D
{
public:
	Vector2 pos;
};

class VertexPos2DColor
{
public:
	Vector2 pos;
	Color	color;
};

class VertexPos2DTex
{
public:
	Vector2 pos;
	Vector2 tex;
};

class VertexPos2DColorTex
{
public:
	Vector2 pos;
	Color	color;
	Vector2 tex;
};

class VertexPos4D
{
public:
	Vector3 pos;
    float   w;
};
