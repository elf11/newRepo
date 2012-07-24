#include "Color.h"

Color Color::Lerp(const Color& color1, const Color& color2, const float ammount)
{
	return Color
	(
		color1.r + (color2.r - color1.r) * ammount,
		color1.g + (color2.g - color1.g) * ammount,
		color1.b + (color2.b - color1.b) * ammount,
		color1.a + (color2.a - color1.a) * ammount
	);	
}

void Color::Lerp(const Color& color1, const Color& color2, const float ammount, Color *const result)
{
	result->r = color1.r + (color2.r - color1.r) * ammount;
	result->g = color1.g + (color2.g - color1.g) * ammount;
	result->b = color1.b + (color2.b - color1.b) * ammount;
	result->a = color1.a + (color2.a - color1.a) * ammount;
}

const Color Color::AliceBlue = Color(240 ,248 ,255 ,255);
const Color Color::AntiqueWhite = Color(250 ,235 ,215 ,255);
const Color Color::Aqua = Color(0 ,255 ,255 ,255);
const Color Color::Aquamarine = Color(127 ,255 ,212 ,255);
const Color Color::Azure = Color(240 ,255 ,255 ,255);
const Color Color::Beige = Color(245 ,245 ,220 ,255);
const Color Color::Bisque = Color(255 ,228 ,196 ,255);
const Color Color::Black = Color(0 ,0 ,0 ,255);
const Color Color::BlanchedAlmond = Color(255 ,235 ,205 ,255);
const Color Color::Blue = Color(0 ,0 ,255 ,255);
const Color Color::SoftBlue = Color(0x7b ,0x7b ,255 ,255);
const Color Color::BlueViolet = Color(138 ,43 ,226 ,255);
const Color Color::Brown = Color(165 ,42 ,42 ,255);
const Color Color::BurlyWood = Color(222 ,184 ,135 ,255);
const Color Color::CadetBlue = Color(95 ,158 ,160 ,255);
const Color Color::Chartreuse = Color(127 ,255 ,0 ,255);
const Color Color::Chocolate = Color(210 ,105 ,30 ,255);
const Color Color::Coral = Color(255 ,127 ,80 ,255);
const Color Color::CornflowerBlue = Color(100 ,149 ,237 ,255);
const Color Color::Cornsilk = Color(255 ,248 ,220 ,255);
const Color Color::Crimson = Color(220 ,20 ,60 ,255);
const Color Color::Cyan = Color(0 ,255 ,255 ,255);
const Color Color::DarkBlue = Color(0 ,0 ,139 ,255);
const Color Color::DarkCyan = Color(0 ,139 ,139 ,255);
const Color Color::DarkGoldenrod = Color(184 ,134 ,11 ,255);
const Color Color::DarkGray = Color(169 ,169 ,169 ,255);
const Color Color::DarkGreen = Color(0 ,100 ,0 ,255);
const Color Color::DarkKhaki = Color(189 ,183 ,107 ,255);
const Color Color::DarkMagenta = Color(139 ,0 ,139 ,255);
const Color Color::DarkOliveGreen = Color(85 ,107 ,47 ,255);
const Color Color::DarkOrange = Color(255 ,140 ,0 ,255);
const Color Color::DarkOrchid = Color(153 ,50 ,204 ,255);
const Color Color::DarkRed = Color(139 ,0 ,0 ,255);
const Color Color::DarkSalmon = Color(233 ,150 ,122 ,255);
const Color Color::DarkSeaGreen = Color(143 ,188 ,139 ,255);
const Color Color::DarkSlateBlue = Color(72 ,61 ,139 ,255);
const Color Color::DarkSlateGray = Color(47 ,79 ,79 ,255);
const Color Color::DarkTurquoise = Color(0 ,206 ,209 ,255);
const Color Color::DarkViolet = Color(148 ,0 ,211 ,255);
const Color Color::DeepPink = Color(255 ,20 ,147 ,255);
const Color Color::DeepSkyBlue = Color(0 ,191 ,255 ,255);
const Color Color::DimGray = Color(105 ,105 ,105 ,255);
const Color Color::DodgerBlue = Color(30 ,144 ,255 ,255);
const Color Color::Firebrick = Color(178 ,34 ,34 ,255);
const Color Color::FloralWhite = Color(255 ,250 ,240 ,255);
const Color Color::ForestGreen = Color(34 ,139 ,34 ,255);
const Color Color::Fuchsia = Color(255 ,0 ,255 ,255);
const Color Color::Gainsboro = Color(220 ,220 ,220 ,255);
const Color Color::GhostWhite = Color(248 ,248 ,255 ,255);
const Color Color::Gold = Color(255 ,215 ,0 ,255);
const Color Color::Goldenrod = Color(218 ,165 ,32 ,255);
const Color Color::Gray = Color(128 ,128 ,128 ,255);
const Color Color::Green = Color(0 ,128 ,0 ,255);
const Color Color::SoftGreen = Color(0xb1,0xf5, 0xb5 ,255);
const Color Color::GreenYellow = Color(173 ,255 ,47 ,255);
const Color Color::Honeydew = Color(240 ,255 ,240 ,255);
const Color Color::HotPink = Color(255 ,105 ,180 ,255);
const Color Color::IndianRed = Color(205 ,92 ,92 ,255);
const Color Color::Indigo = Color(75 ,0 ,130 ,255);
const Color Color::Ivory = Color(255 ,255 ,240 ,255);
const Color Color::Khaki = Color(240 ,230 ,140 ,255);
const Color Color::Lavender = Color(230 ,230 ,250 ,255);
const Color Color::LavenderBlush = Color(255 ,240 ,245 ,255);
const Color Color::LawnGreen = Color(124 ,252 ,0 ,255);
const Color Color::LemonChiffon = Color(255 ,250 ,205 ,255);
const Color Color::LightBlue = Color(173 ,216 ,230 ,255);
const Color Color::LightCoral = Color(240 ,128 ,128 ,255);
const Color Color::LightCyan = Color(224 ,255 ,255 ,255);
const Color Color::LightGoldenrodYellow = Color(250 ,250 ,210 ,255);
const Color Color::LightGray = Color(211 ,211 ,211 ,255);
const Color Color::LightGreen = Color(144 ,238 ,144 ,255);
const Color Color::LightPink = Color(255 ,182 ,193 ,255);
const Color Color::LightSalmon = Color(255 ,160 ,122 ,255);
const Color Color::LightSeaGreen = Color(32 ,178 ,170 ,255);
const Color Color::LightSkyBlue = Color(135 ,206 ,250 ,255);
const Color Color::LightSlateGray = Color(119 ,136 ,153 ,255);
const Color Color::LightSteelBlue = Color(176 ,196 ,222 ,255);
const Color Color::LightYellow = Color(255 ,255 ,224 ,255);
const Color Color::Lime = Color(0 ,255 ,0 ,255);
const Color Color::LimeGreen = Color(50 ,205 ,50 ,255);
const Color Color::Linen = Color(250 ,240 ,230 ,255);
const Color Color::Magenta = Color(255 ,0 ,255 ,255);
const Color Color::Maroon = Color(128 ,0 ,0 ,255);
const Color Color::MediumAquamarine = Color(102 ,205 ,170 ,255);
const Color Color::MediumBlue = Color(0 ,0 ,205 ,255);
const Color Color::MediumOrchid = Color(186 ,85 ,211 ,255);
const Color Color::MediumPurple = Color(147 ,112 ,219 ,255);
const Color Color::MediumSeaGreen = Color(60 ,179 ,113 ,255);
const Color Color::MediumSlateBlue = Color(123 ,104 ,238 ,255);
const Color Color::MediumSpringGreen = Color(0 ,250 ,154 ,255);
const Color Color::MediumTurquoise = Color(72 ,209 ,204 ,255);
const Color Color::MediumVioletRed = Color(199 ,21 ,133 ,255);
const Color Color::MidnightBlue = Color(25 ,25 ,112 ,255);
const Color Color::MintCream = Color(245 ,255 ,250 ,255);
const Color Color::MistyRose = Color(255 ,228 ,225 ,255);
const Color Color::Moccasin = Color(255 ,228 ,181 ,255);
const Color Color::NavajoWhite = Color(255 ,222 ,173 ,255);
const Color Color::Navy = Color(0 ,0 ,128 ,255);
const Color Color::OldLace = Color(253 ,245 ,230 ,255);
const Color Color::Olive = Color(128 ,128 ,0 ,255);
const Color Color::OliveDrab = Color(107 ,142 ,35 ,255);
const Color Color::Orange = Color(255 ,165 ,0 ,255);
const Color Color::OrangeRed = Color(255 ,69 ,0 ,255);
const Color Color::Orchid = Color(218 ,112 ,214 ,255);
const Color Color::PaleGoldenrod = Color(238 ,232 ,170 ,255);
const Color Color::PaleGreen = Color(152 ,251 ,152 ,255);
const Color Color::PaleTurquoise = Color(175 ,238 ,238 ,255);
const Color Color::PaleVioletRed = Color(219 ,112 ,147 ,255);
const Color Color::PapayaWhip = Color(255 ,239 ,213 ,255);
const Color Color::PeachPuff = Color(255 ,218 ,185 ,255);
const Color Color::Peru = Color(205 ,133 ,63 ,255);
const Color Color::Pink = Color(255 ,192 ,203 ,255);
const Color Color::Plum = Color(221 ,160 ,221 ,255);
const Color Color::PowderBlue = Color(176 ,224 ,230 ,255);
const Color Color::Purple = Color(128 ,0 ,128 ,255);
const Color Color::Red = Color(255 ,0 ,0 ,255);
const Color Color::SoftRed = Color(255 ,0x7b ,0x7b ,255);
const Color Color::RosyBrown = Color(188 ,143 ,143 ,255);
const Color Color::RoyalBlue = Color(65 ,105 ,225 ,255);
const Color Color::SaddleBrown = Color(139 ,69 ,19 ,255);
const Color Color::Salmon = Color(250 ,128 ,114 ,255);
const Color Color::SandyBrown = Color(244 ,164 ,96 ,255);
const Color Color::SeaGreen = Color(46 ,139 ,87 ,255);
const Color Color::SeaShell = Color(255 ,245 ,238 ,255);
const Color Color::Sienna = Color(160 ,82 ,45 ,255);
const Color Color::Silver = Color(192 ,192 ,192 ,255);
const Color Color::SkyBlue = Color(135 ,206 ,235 ,255);
const Color Color::SlateBlue = Color(106 ,90 ,205 ,255);
const Color Color::SlateGray = Color(112 ,128 ,144 ,255);
const Color Color::Snow = Color(255 ,250 ,250 ,255);
const Color Color::SpringGreen = Color(0 ,255 ,127 ,255);
const Color Color::SteelBlue = Color(70 ,130 ,180 ,255);
const Color Color::Tan = Color(210 ,180 ,140 ,255);
const Color Color::Teal = Color(0 ,128 ,128 ,255);
const Color Color::Thistle = Color(216 ,191 ,216 ,255);
const Color Color::Tomato = Color(255 ,99 ,71 ,255);
const Color Color::TransparentBlack = Color(0 ,0 ,0 ,0);
const Color Color::TransparentWhite = Color(255 ,255 ,255 ,0);
const Color Color::Turquoise = Color(64 ,224 ,208 ,255);
const Color Color::Violet = Color(238 ,130 ,238 ,255);
const Color Color::Wheat = Color(245 ,222 ,179 ,255);
const Color Color::White = Color(255 ,255 ,255 ,255);
const Color Color::WhiteSmoke = Color(245 ,245 ,245 ,255);
const Color Color::Yellow = Color(255 ,255 ,0 ,255);
const Color Color::YellowBreitling = Color(252, 217, 5, 255);
const Color Color::YellowBreitlingHightlight = Color(252 * 0.75f, 217 * 0.75f, 5 * 0.75f, 255 * 0.75f);
const Color Color::YellowGreen = Color(154 ,205 ,50 ,255);
