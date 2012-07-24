#pragma once

#include "Vector3.h"

class Color
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	
	inline Color() {}
	inline Color(const unsigned char R, const unsigned char G, const unsigned char B, const unsigned char A) : r(R), g(G), b(B), a(A) {}
	inline Color(const unsigned char R, const unsigned char G, const unsigned char B) : r(R), g(G), b(B), a(255) {}
	inline Color(const unsigned char GreyChannel, const unsigned char A) : r(GreyChannel), g(GreyChannel), b(GreyChannel), a(A) {}
	inline Color(const unsigned char GreyChannel) : r(GreyChannel), g(GreyChannel), b(GreyChannel), a(255) {}
	
	inline void Set(const unsigned char R, const unsigned char G, const unsigned char B, const unsigned char A)
	{
		r = R; g = G; b = B; a = A;
	}
	
	inline void SetFloat(const float R, const float G, const float B, const float A)
	{
		r = R * 255; g = G * 255; b = B * 255; a = A * 255;
	}
	
	inline void SetFloat(const float channel)
	{
		r = g = b = a = channel * 255;
	}
	
	inline void SetFloat(const float channel, const float alpha)
	{
		r = g = b = channel * 255;
		a = alpha * 255;
	}
	
	inline void SetVector(const Vector3 *const color)
	{
		r = color->x * 255;
		g = color->y * 255;
		b = color->z * 255;
		a = 255;
	}
	
	static inline Color FromFloat(const float R, const float G, const float B, const float A)
	{
		return Color(R * 255, G * 255, B * 255, A * 255);
	}
	
	static inline void CreateFromVector(const Vector3 *const color, Color *result)
	{
		result->r = color->x * 255;
		result->g = color->y * 255;
		result->b = color->z * 255;
		result->a = 255;
	}
	
	inline void FromFloat(const float R, const float G, const float B, const float A, Color *const result)
	{
		result->r = R * 255;
		result->g = G * 255;
		result->b = B * 255;
		result->a = A * 255;
	}
	
	inline unsigned int PacketValue() const { return *((unsigned int *) &r); }
	inline unsigned int PacketValueARGB() const
	{ 
		return ((a << 24) | (r << 16) | (g << 8) | b);
	}

	inline unsigned int PacketValueABGR() const
	{ 
		return ((a << 24) | (b << 16) | (g << 8) | r);
	}
	
	inline void PremultiplyAlpha()
	{
		const float alpha = a / 255.f;
		r *= alpha;
		g *= alpha;
		b *= alpha;
	}
	
	inline Vector3 ToVector3() const { return Vector3(r * 0.003921568627451f, g * 0.003921568627451f, b * 0.003921568627451f); }
	
	inline Color & operator *= (const float val)
	{
		r *= val;
		g *= val;
		b *= val;
		a *= val;
		return (*this);
	}
    
    inline Color & operator *= (const Vector3 &val)
	{
		r *= val.x;
		g *= val.y;
		b *= val.z;
		return (*this);
	}
	
	static Color Lerp(const Color& color1, const Color& color2, const float ammount);
	static void Lerp(const Color& color1, const Color& color2, const float ammount, Color *const result);
	
	const static Color AliceBlue;
	const static Color AntiqueWhite;
	const static Color Aqua;
	const static Color Aquamarine;
	const static Color Azure;
	const static Color Beige;
	const static Color Bisque;
	const static Color Black;
	const static Color BlanchedAlmond;
	const static Color Blue;
	const static Color SoftBlue;
	const static Color BlueViolet;
	const static Color Brown;
	const static Color BurlyWood;
	const static Color CadetBlue;
	const static Color Chartreuse;
	const static Color Chocolate;
	const static Color Coral;
	const static Color CornflowerBlue;
	const static Color Cornsilk;
	const static Color Crimson;
	const static Color Cyan;
	const static Color DarkBlue;
	const static Color DarkCyan;
	const static Color DarkGoldenrod;
	const static Color DarkGray;
	const static Color DarkGreen;
	const static Color DarkKhaki;
	const static Color DarkMagenta;
	const static Color DarkOliveGreen;
	const static Color DarkOrange;
	const static Color DarkOrchid;
	const static Color DarkRed;
	const static Color DarkSalmon;
	const static Color DarkSeaGreen;
	const static Color DarkSlateBlue;
	const static Color DarkSlateGray;
	const static Color DarkTurquoise;
	const static Color DarkViolet;
	const static Color DeepPink;
	const static Color DeepSkyBlue;
	const static Color DimGray;
	const static Color DodgerBlue;
	const static Color Firebrick;
	const static Color FloralWhite;
	const static Color ForestGreen;
	const static Color Fuchsia;
	const static Color Gainsboro;
	const static Color GhostWhite;
	const static Color Gold;
	const static Color Goldenrod;
	const static Color Gray;
	const static Color Green;
	const static Color SoftGreen;
	const static Color GreenYellow;
	const static Color Honeydew;
	const static Color HotPink;
	const static Color IndianRed;
	const static Color Indigo;
	const static Color Ivory;
	const static Color Khaki;
	const static Color Lavender;
	const static Color LavenderBlush;
	const static Color LawnGreen;
	const static Color LemonChiffon;
	const static Color LightBlue;
	const static Color LightCoral;
	const static Color LightCyan;
	const static Color LightGoldenrodYellow;
	const static Color LightGray;
	const static Color LightGreen;
	const static Color LightPink;
	const static Color LightSalmon;
	const static Color LightSeaGreen;
	const static Color LightSkyBlue;
	const static Color LightSlateGray;
	const static Color LightSteelBlue;
	const static Color LightYellow;
	const static Color Lime;
	const static Color LimeGreen;
	const static Color Linen;
	const static Color Magenta;
	const static Color Maroon;
	const static Color MediumAquamarine;
	const static Color MediumBlue;
	const static Color MediumOrchid;
	const static Color MediumPurple;
	const static Color MediumSeaGreen;
	const static Color MediumSlateBlue;
	const static Color MediumSpringGreen;
	const static Color MediumTurquoise;
	const static Color MediumVioletRed;
	const static Color MidnightBlue;
	const static Color MintCream;
	const static Color MistyRose;
	const static Color Moccasin;
	const static Color NavajoWhite;
	const static Color Navy;
	const static Color OldLace;
	const static Color Olive;
	const static Color OliveDrab;
	const static Color Orange;
	const static Color OrangeRed;
	const static Color Orchid;
	const static Color PaleGoldenrod;
	const static Color PaleGreen;
	const static Color PaleTurquoise;
	const static Color PaleVioletRed;
	const static Color PapayaWhip;
	const static Color PeachPuff;
	const static Color Peru;
	const static Color Pink;
	const static Color Plum;
	const static Color PowderBlue;
	const static Color Purple;
	const static Color Red;
	const static Color SoftRed;
	const static Color RosyBrown;
	const static Color RoyalBlue;
	const static Color SaddleBrown;
	const static Color Salmon;
	const static Color SandyBrown;
	const static Color SeaGreen;
	const static Color SeaShell;
	const static Color Sienna;
	const static Color Silver;
	const static Color SkyBlue;
	const static Color SlateBlue;
	const static Color SlateGray;
	const static Color Snow;
	const static Color SpringGreen;
	const static Color SteelBlue;
	const static Color Tan;
	const static Color Teal;
	const static Color Thistle;
	const static Color Tomato;
	const static Color TransparentBlack;
	const static Color TransparentWhite;
	const static Color Turquoise;
	const static Color Violet;
	const static Color Wheat;
	const static Color White;
	const static Color WhiteSmoke;
	const static Color Yellow;
	const static Color YellowBreitling;
	const static Color YellowBreitlingHightlight;
	const static Color YellowGreen;
};

inline bool operator == (const Color &c1, const Color &c2) { return ((const unsigned int &)c1) == ((const unsigned int &)c2); }
inline bool operator != (const Color &c1, const Color &c2) { return ((const unsigned int &)c1) != ((const unsigned int &)c2); }
inline Color operator * (const Color& c, float v) {return Color(c.r*v, c.g*v, c.b*v, c.a*v);}

