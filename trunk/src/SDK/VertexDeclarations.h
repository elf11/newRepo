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
