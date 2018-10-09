#pragma once
#include "DrawManager.h"
#include "../sdk/sdk.hpp"

class Style
{
public:
	DWORD cursor_color = PURPLE(255);
	DWORD cursor_outline_color = BLACK(150);

	DWORD menu_color_border = WHITE(255);
	DWORD menu_color_1_border = BLACK(100);
	DWORD menu_outline_color_border = EVENDARKERGRAY(125);

	DWORD menu_color = WHITE(255);
	DWORD menu_color_1 = D3DCOLOR_ARGB(255, 180, 180, 180);
	DWORD menu_outline_color = EVENDARKERGRAY(255);

	int menux = 100;
	int menuy = 100;
	int menuw = 485 + 150;
	int menuh = 375;
	int menu_outline_thickness = 1;

	DWORD checkbox_color = WHITE(255);
	DWORD checkbox_color1 = GRAY(255);
	DWORD checkbox_outline_color = BLACK(100);
	DWORD checkbox_check_color = PURPLE(255);
	DWORD checkbox_check_outline_color = BLACK(150);
	DWORD checkbox_font_color = BLACK(200);

	DWORD checkbox_color_hovered = GRAY(200);
	DWORD checkbox_color_hovered1 = DARKGRAY(200);
	DWORD checkbox_outline_color_hovered = BLACK(100);
	DWORD checkbox_check_color_hovered = PURPLE(255);
	DWORD checkbox_check_outline_color_hovered = BLACK(150);
	DWORD checkbox_font_color_hovered = BLACK(230);

	DWORD checkbox_color_pressed = GRAY(255);
	DWORD checkbox_color_pressed1 = DARKGRAY(255);
	DWORD checkbox_outline_color_pressed = BLACK(100);
	DWORD checkbox_check_color_pressed = PURPLE(255);
	DWORD checkbox_check_outline_color_pressed = BLACK(150);
	DWORD checkbox_font_color_pressed = BLACK(255);

	int checkbox_clicked_width = 10;
	int checkbox_clicked_height = 10;
	int checkbox_width = 12;
	int checkbox_height = 12;
	int checkbox_outline_thickness = 1;

	DWORD slider_color = WHITE(255);
	DWORD slider_outline_color = BLACK(100);
	DWORD slider_slide_color = PURPLE(255);
	DWORD slider_font_color = BLACK(200);

	DWORD slider_color_hovered = GRAY(200);
	DWORD slider_outline_color_hovered = BLACK(100);
	DWORD slider_slide_color_hovered = PURPLE(255);
	DWORD slider_font_color_hovered = BLACK(230);

	DWORD slider_color_pressed = GRAY(255);
	DWORD slider_outline_color_pressed = BLACK(100);
	DWORD slider_slide_color_pressed = PURPLE(255);
	DWORD slider_font_color_pressed = BLACK(255);

	int slider_width = 100;
	int slider_height = 12;
	int slider_outline_thickness = 1;

	int button_outline_thickness = 1;

	int column_width = 200;

	int item_spacing_y = 12;

	int colorpicker_size = 120;
	int colorpicker_huebar_size = 8;
};

namespace s1lentgui
{
	enum class ObjectState
	{
		OBJECTSTATE_IDLE,
		OBJECTSTATE_HOVERED,
		OBJECTSTATE_PRESSED
	};

	namespace utils
	{
		int GetTextWidth(const char *szText, LPD3DXFONT pFont);
		int GetTextHeight(const char *szText, LPD3DXFONT pFont);
		bool Hovered(int x, int y, int w, int h);
		bool Pressed(int x, int y, int w, int h);
		int GetSliderPixelOffset(int x, int y, int w, int h);
		int GetSliderValueInt(int x, int y, int w, int h, int min, int max);
		float GetSliderValueFloat(int x, int y, int w, int h, float min, float max);
		bool Clicked(int x, int y, int w, int h, int buttonid);
		ObjectState State(int x, int y, int w, int h);
	}
}

namespace s1lentgui
{
	namespace utils
	{
		bool InvalidateControlInput = false;

		char* Keys[] =
		{
			"",
			"mouse1",
			"mouse2",
			"cancel",
			"mouse3",
			"mouse4",
			"mouse5",
			"",
			"bckspc",
			"tab",
			"",
			"",
			"clear",
			"return",
			"",
			"",
			"shift",
			"control",
			"alt",
			"pause",
			"caps",
			"",
			"",
			"",
			"",
			"",
			"",
			"esc",
			"",
			"",
			"",
			"",
			"space",
			"pgup",
			"pgdown",
			"end",
			"home",
			"left",
			"up",
			"right",
			"down",
			"",
			"",
			"",
			"prnt",
			"ins",
			"del",
			"",
			"0",
			"1",
			"2",
			"3",
			"4",
			"5",
			"6",
			"7",
			"8",
			"9",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"a",
			"b",
			"c",
			"d",
			"e",
			"f",
			"g",
			"h",
			"i",
			"j",
			"k",
			"l",
			"m",
			"n",
			"o",
			"p",
			"q",
			"r",
			"s",
			"t",
			"u",
			"v",
			"w",
			"x",
			"y",
			"z",
			"",
			"",
			"",
			"",
			"",
			"num0",
			"num1",
			"num2",
			"num3",
			"num4",
			"num5",
			"num6",
			"num7",
			"num8",
			"num9",
			"mul",
			"add",
			"",
			"sub",
			"dec",
			"div",
			"f1",
			"f2",
			"f3",
			"f4",
			"f5",
			"f6",
			"f7",
			"f8",
			"f9",
			"f10",
			"f11",
			"f12"
		};

		int GetTextWidth(const char *szText, LPD3DXFONT pFont)
		{
			RECT rcRect = { 0, 0, 0, 0 };

			if (pFont)
				pFont->DrawTextA(0, szText, strlen(szText), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));

			return rcRect.right - rcRect.left;
		}

		int GetTextHeight(const char *szText, LPD3DXFONT pFont)
		{
			RECT rcRect = { 0, 0, 0, 0 };

			if (pFont)
				pFont->DrawTextA(0, szText, strlen(szText), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));

			return rcRect.bottom - rcRect.top;
		}

		bool Hovered(int x, int y, int w, int h)
		{
			POINT p;
			GetCursorPos(&p);
			return p.x >= x && p.y >= y && p.x <= x + w && p.y <= y + h;
		}

		bool Pressed(int x, int y, int w, int h)
		{
			return Hovered(x, y, w, h) && GetKeyState(VK_LBUTTON) & 0x8000;
		}

		int GetSliderPixelOffset(int x, int y, int w, int h)
		{
			POINT p;
			GetCursorPos(&p);

			if (p.x <= x)
				return 0;
			else if (p.x >= x + w)
				return w;
			else
				return p.x - x;
		}

		int GetSliderValueInt(int x, int y, int w, int h, int min, int max)
		{
			return (int)(GetSliderPixelOffset(x, y, w, h) * ((float)max / (float)w));
		}

		float GetSliderValueFloat(int x, int y, int w, int h, float min, float max)
		{
			return (float)GetSliderPixelOffset(x, y, w, h) * (max / w);
		}

		bool toggledown[500] = { false };
		bool listeningforkeypress[500] = { false };

		bool Clicked(int x, int y, int w, int h, int buttonid)
		{
			if (Hovered(x, y, w, h) && GetKeyState(VK_LBUTTON) & 0x8000 && !toggledown[buttonid])
				toggledown[buttonid] = true;
			else if (Hovered(x, y, w, h) && !(GetKeyState(VK_LBUTTON) & 0x8000) && toggledown[buttonid])
			{
				toggledown[buttonid] = false;
				return true;
			}

			if (toggledown[buttonid])
				for (int i = 0; i < ARRAYSIZE(toggledown); ++i)
					if (i != buttonid)
					{
						toggledown[i] = false;
						listeningforkeypress[i] = false;
					}

			return false;
		}

		ObjectState State(int x, int y, int w, int h)
		{
			if (Pressed(x, y, w, h))
				return ObjectState::OBJECTSTATE_PRESSED;
			else if (Hovered(x, y, w, h))
				return ObjectState::OBJECTSTATE_HOVERED;
			else
				return ObjectState::OBJECTSTATE_IDLE;
		}

		std::vector<RECT> AllObjectBounds;
	}

	static int last_object_x = 0;
	static int last_object_y = 0;
	static int last_object_id = 0;
	static bool onceperdraw = false;
	static int selecteddropdown = 0;

	Style style;

	int menuobjectoffset_x = 106;
	int menuobjectoffset_y = 15;

	unsigned long long lastmenucoloranimtime = 0;
	int menucoloranim = 0;
	DWORD menuanimcolor = D3DCOLOR_RGBA(100, 0, 255, 255);

	char* _title = "";

	int selectedtextbox = -1;

	Style& GetStyle()
	{
		return style;
	}

	void CloseButton(bool* opened, int x, int y, bool popout = true)
	{
		utils::AllObjectBounds.push_back({ style.menux + x - 1, style.menuy + y, 20, 12 });

		if (utils::Clicked(style.menux + x - 1, style.menuy + y, 20, 12, 0))
			exit(0);

		auto state = utils::State(style.menux + x - 1, style.menuy + y, 20, 12);

		switch (state)
		{
		case ObjectState::OBJECTSTATE_IDLE:
			g_pDraw->FilledBoxOutlined(style.menux + x - 1, style.menuy + y, 20, 12, D3DCOLOR_RGBA(255, 0, 0, 255), GRAY(150), 1);
			break;
		case ObjectState::OBJECTSTATE_HOVERED:
			g_pDraw->FilledBoxOutlined(style.menux + x - (popout ? 1 : 0) - 1, style.menuy + y - (popout ? 1 : 0), 20 + (popout ? 1 : 0), 12 + (popout ? 1 : 0), D3DCOLOR_RGBA(255, 0, 0, 255), GRAY(150), 1);
			break;
		case ObjectState::OBJECTSTATE_PRESSED:
			g_pDraw->FilledBoxOutlined(style.menux + x - (popout ? 2 : 0) - 1, style.menuy + y - (popout ? 2 : 0), 20 + (popout ? 2 : 0), 12 + (popout ? 2 : 0), D3DCOLOR_RGBA(255, 0, 0, 255), GRAY(150), 1);
			break;
		}
	}

	bool Begin(const char* title, bool* visible, bool closebutton = true)
	{
		_title = _strdup(title);

		if (*visible)
		{
			if (GetTickCount64() > lastmenucoloranimtime + 100)
			{
				lastmenucoloranimtime = GetTickCount64();

				if (menucoloranim < 20)
					menucoloranim++;
				else
					menucoloranim = 0;

				switch (menucoloranim)
				{
				case 0:
					menuanimcolor = D3DCOLOR_RGBA(125, 0, 255, 255);
					break;
				case 1:
					menuanimcolor = D3DCOLOR_RGBA(135, 0, 255, 255);
					break;
				case 2:
					menuanimcolor = D3DCOLOR_RGBA(145, 0, 255, 255);
					break;
				case 3:
					menuanimcolor = D3DCOLOR_RGBA(155, 0, 255, 255);
					break;
				case 4:
					menuanimcolor = D3DCOLOR_RGBA(165, 0, 255, 255);
					break;
				case 5:
					menuanimcolor = D3DCOLOR_RGBA(175, 0, 255, 255);
					break;
				case 6:
					menuanimcolor = D3DCOLOR_RGBA(185, 0, 255, 255);
					break;
				case 7:
					menuanimcolor = D3DCOLOR_RGBA(195, 0, 255, 255);
					break;
				case 8:
					menuanimcolor = D3DCOLOR_RGBA(195, 0, 255, 255);
					break;
				case 9:
					menuanimcolor = D3DCOLOR_RGBA(195, 0, 255, 255);
					break;
				case 10:
					menuanimcolor = D3DCOLOR_RGBA(195, 0, 255, 255);
					break;
				case 11:
					menuanimcolor = D3DCOLOR_RGBA(195, 0, 255, 255);
					break;
				case 12:
					menuanimcolor = D3DCOLOR_RGBA(185, 0, 255, 255);
					break;
				case 13:
					menuanimcolor = D3DCOLOR_RGBA(175, 0, 255, 255);
					break;
				case 14:
					menuanimcolor = D3DCOLOR_RGBA(165, 0, 255, 255);
					break;
				case 15:
					menuanimcolor = D3DCOLOR_RGBA(155, 0, 255, 255);
					break;
				case 16:
					menuanimcolor = D3DCOLOR_RGBA(145, 0, 255, 255);
					break;
				case 17:
					menuanimcolor = D3DCOLOR_RGBA(135, 0, 255, 255);
					break;
				case 18:
					menuanimcolor = D3DCOLOR_RGBA(125, 0, 255, 255);
					break;
				case 19:
					menuanimcolor = D3DCOLOR_RGBA(125, 0, 255, 255);
					break;
				case 20:
					menuanimcolor = D3DCOLOR_RGBA(125, 0, 255, 255);
					break;
				}
			}

			POINT p;
			GetCursorPos(&p);

			static bool dragging = false;
			static int offsetx = 0, offsety = 0;
			static short oldkey = 0;
			static bool gpress = false;

			if (dragging && !(GetKeyState(VK_LBUTTON) & 0x8000))
				dragging = false;

			if (dragging && GetKeyState(VK_LBUTTON) & 0x8000 && !gpress)
			{
				style.menux = p.x - offsetx;
				style.menuy = p.y - offsety;
			}

			bool InMenuObject = false;
			for (auto& ObjectRegion : utils::AllObjectBounds)
			{
				if (utils::Pressed(ObjectRegion.left, ObjectRegion.top, ObjectRegion.right, ObjectRegion.bottom))
					InMenuObject = true;
			}

			if (!InMenuObject && utils::Pressed(style.menux, style.menuy - 25, style.menuw, style.menuh + 25) && gpress)
			{
				dragging = true;
				offsetx = p.x - style.menux;
				offsety = p.y - style.menuy;
			}

			utils::AllObjectBounds.clear();

			gpress = GetKeyState(VK_LBUTTON) & 0x8000 && !oldkey;
			oldkey = GetKeyState(VK_LBUTTON) & 0x8000;

			g_pDraw->FilledBoxOutlined(style.menux, style.menuy - 25, style.menuw, style.menuh + 25, menuanimcolor, style.menu_outline_color_border, style.menu_outline_thickness);
			g_pDraw->GradientBox(style.menux + 1, style.menuy - 24, style.menuw - 2, (style.menuh + 25) / 20, style.menu_color_1_border, D3DCOLOR_RGBA(1, 1, 1, 1), true);
			g_pDraw->FilledBoxOutlined(style.menux + 3, style.menuy + 3, style.menuw - 6, style.menuh - 6, style.menu_color, style.menu_outline_color, style.menu_outline_thickness);
			g_pDraw->GradientBox(style.menux + 4, style.menuy + 4, style.menuw - 8, (style.menuh - 6) / 8, style.menu_color_1, style.menu_color, true);
			g_pDraw->GradientBox(style.menux + 4, style.menuy + (style.menuh - (style.menuh - 6) / 8) - 4, style.menuw - 8, (style.menuh - 6) / 8, style.menu_color, style.menu_color_1, true);

			if (closebutton)
				CloseButton(visible, 426, -14);

			return true;
		}

		return false;
	}

	class CDropdownDrawing
	{
	public:
		CDropdownDrawing(const char* _name, std::vector<const char*> _contents, int* _option, bool _popout, int _x, int _y, int _w, int _h, ObjectState _state, int __x, int __y)
		{
			name = _name;
			contents = _contents;
			option = _option;
			popout = _popout;
			x = _x;
			y = _y;
			w = _w;
			h = _h;
			state = _state;
			_x_ = __x;
			_y_ = __y;
		}

		~CDropdownDrawing()
		{

		}

		const char* name;
		std::vector<const char*> contents;
		int* option;
		bool popout;
		int x, y, w, h, _x_, _y_;
		ObjectState state;
	};

	std::vector<CDropdownDrawing> DropdownDrawing;

	void End()
	{
		if (DropdownDrawing.size() > 0)
		{
			switch (DropdownDrawing.at(0).state)
			{
			case ObjectState::OBJECTSTATE_IDLE: // draw idle
			{
				g_pDraw->String(DropdownDrawing.at(0)._x_, DropdownDrawing.at(0)._y_, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, DropdownDrawing.at(0).name);
				g_pDraw->GradientBoxOutlined(DropdownDrawing.at(0).x - (DropdownDrawing.at(0).popout ? 2 : 0), DropdownDrawing.at(0).y - (DropdownDrawing.at(0).popout ? 2 : 0), DropdownDrawing.at(0).w + (DropdownDrawing.at(0).popout ? 2 : 0), (DropdownDrawing.at(0).h + (DropdownDrawing.at(0).popout ? 2 : 0)), style.checkbox_outline_thickness, style.checkbox_color, style.checkbox_color1, style.checkbox_outline_color, true);
				g_pDraw->String(DropdownDrawing.at(0).x + 6, DropdownDrawing.at(0).y + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, DropdownDrawing.at(0).contents.at(*DropdownDrawing.at(0).option));

				int LastY = DropdownDrawing.at(0)._y_ + 4;
				for (auto& option : DropdownDrawing.at(0).contents)
				{
					LastY += 12;
					g_pDraw->String(DropdownDrawing.at(0).x + 6, LastY, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, option);
					LastY += 4;
				}

			}
			break;
			case ObjectState::OBJECTSTATE_HOVERED: // draw when hovered
			{
				g_pDraw->String(DropdownDrawing.at(0)._x_, DropdownDrawing.at(0)._y_, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, DropdownDrawing.at(0).name);
				g_pDraw->GradientBoxOutlined(DropdownDrawing.at(0).x - (DropdownDrawing.at(0).popout ? 2 : 0), DropdownDrawing.at(0).y - (DropdownDrawing.at(0).popout ? 2 : 0), DropdownDrawing.at(0).w + (DropdownDrawing.at(0).popout ? 2 : 0), (DropdownDrawing.at(0).h + (DropdownDrawing.at(0).popout ? 2 : 0)), style.checkbox_outline_thickness, style.checkbox_color_hovered, style.checkbox_color_hovered1, style.checkbox_outline_color_hovered, true);
				g_pDraw->String(DropdownDrawing.at(0).x + 6, DropdownDrawing.at(0).y + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, DropdownDrawing.at(0).contents.at(*DropdownDrawing.at(0).option));

				int LastY = DropdownDrawing.at(0)._y_ + 4;
				for (auto& option : DropdownDrawing.at(0).contents)
				{
					LastY += 12;
					g_pDraw->String(DropdownDrawing.at(0).x + 6, LastY, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, option);
					LastY += 4;
				}
			}
			break;
			case ObjectState::OBJECTSTATE_PRESSED: // draw pressed down
			{
				g_pDraw->String(DropdownDrawing.at(0)._x_, DropdownDrawing.at(0)._y_, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, DropdownDrawing.at(0).name);
				g_pDraw->GradientBoxOutlined(DropdownDrawing.at(0).x - (DropdownDrawing.at(0).popout ? 2 : 0), DropdownDrawing.at(0).y - (DropdownDrawing.at(0).popout ? 2 : 0), DropdownDrawing.at(0).w + (DropdownDrawing.at(0).popout ? 2 : 0), (DropdownDrawing.at(0).h + (DropdownDrawing.at(0).popout ? 2 : 0)), style.checkbox_outline_thickness, style.checkbox_color_pressed, style.checkbox_color_pressed1, style.checkbox_outline_color_pressed, true);
				g_pDraw->String(DropdownDrawing.at(0).x + 6, DropdownDrawing.at(0).y + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, DropdownDrawing.at(0).contents.at(*DropdownDrawing.at(0).option));

				int LastY = DropdownDrawing.at(0)._y_ + 4;
				for (auto& option : DropdownDrawing.at(0).contents)
				{
					LastY += 12;
					g_pDraw->String(DropdownDrawing.at(0).x + 6, LastY, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, option);
					LastY += 4;
				}
			}
			break;
			}
		}

		g_pDraw->String(style.menux + style.menuw / 2, style.menuy - 19, FONT_CENTER, g_pDraw->fonts.fnormal, true, D3DCOLOR_RGBA(255, 255, 255, 255), _title);

		POINT Mouse;
		GetCursorPos(&Mouse);

		g_pDraw->FilledBox(Mouse.x + 1, Mouse.y, 1, 17, D3DCOLOR_RGBA(3, 6, 26, 255));

		for (int i = 0; i < 11; i++)
			g_pDraw->FilledBox(Mouse.x + 2 + i, Mouse.y + 1 + i, 1, 1, D3DCOLOR_RGBA(3, 6, 26, 255));

		g_pDraw->FilledBox(Mouse.x + 8, Mouse.y + 12, 5, 1, D3DCOLOR_RGBA(3, 6, 26, 255));
		g_pDraw->FilledBox(Mouse.x + 8, Mouse.y + 13, 1, 1, D3DCOLOR_RGBA(3, 6, 26, 255));
		g_pDraw->FilledBox(Mouse.x + 9, Mouse.y + 14, 1, 2, D3DCOLOR_RGBA(3, 6, 26, 255));
		g_pDraw->FilledBox(Mouse.x + 10, Mouse.y + 16, 1, 2, D3DCOLOR_RGBA(3, 6, 26, 255));
		g_pDraw->FilledBox(Mouse.x + 8, Mouse.y + 18, 2, 1, D3DCOLOR_RGBA(3, 6, 26, 255));
		g_pDraw->FilledBox(Mouse.x + 7, Mouse.y + 16, 1, 2, D3DCOLOR_RGBA(3, 6, 26, 255));
		g_pDraw->FilledBox(Mouse.x + 6, Mouse.y + 14, 1, 2, D3DCOLOR_RGBA(3, 6, 26, 255));
		g_pDraw->FilledBox(Mouse.x + 5, Mouse.y + 13, 1, 1, D3DCOLOR_RGBA(3, 6, 26, 255));
		g_pDraw->FilledBox(Mouse.x + 4, Mouse.y + 14, 1, 1, D3DCOLOR_RGBA(3, 6, 26, 255));
		g_pDraw->FilledBox(Mouse.x + 3, Mouse.y + 15, 1, 1, D3DCOLOR_RGBA(3, 6, 26, 255));
		g_pDraw->FilledBox(Mouse.x + 2, Mouse.y + 16, 1, 1, D3DCOLOR_RGBA(3, 6, 26, 255));

		for (int i = 0; i < 4; i++)
			g_pDraw->FilledBox(Mouse.x + 2 + i, Mouse.y + 2 + i, 1, 14 - (i * 2), D3DCOLOR_RGBA(255, 255, 255, 255));

		g_pDraw->FilledBox(Mouse.x + 6, Mouse.y + 6, 1, 8, D3DCOLOR_RGBA(255, 255, 255, 255));
		g_pDraw->FilledBox(Mouse.x + 7, Mouse.y + 7, 1, 9, D3DCOLOR_RGBA(255, 255, 255, 255));

		for (int i = 0; i < 4; i++)
			g_pDraw->FilledBox(Mouse.x + 8 + i, Mouse.y + 8 + i, 1, 4 - i, D3DCOLOR_RGBA(255, 255, 255, 255));

		g_pDraw->FilledBox(Mouse.x + 8, Mouse.y + 14, 1, 4, D3DCOLOR_RGBA(255, 255, 255, 255));
		g_pDraw->FilledBox(Mouse.x + 9, Mouse.y + 16, 1, 2, D3DCOLOR_RGBA(255, 255, 255, 255));

		last_object_x = 0;
		last_object_y = 0;
		last_object_id = 0;
		onceperdraw = false;
		DropdownDrawing.clear();
	}

	void NextColumn()
	{
		last_object_x += style.column_width;
		last_object_y = menuobjectoffset_y - 32;
	}

	void NewLine()
	{
		last_object_y += style.item_spacing_y + 17;
	}

	void Checkbox(const char* name, bool* option, bool popout = true, bool showname = true)
	{
		int TextW = utils::GetTextWidth(name, g_pDraw->fonts.fnormal);

		if (!onceperdraw)
		{
			last_object_x = menuobjectoffset_x;
			last_object_y = menuobjectoffset_y;
			onceperdraw = true;
		}
		else
		{
			last_object_y += style.item_spacing_y + style.checkbox_height;
			last_object_id++;
		}

		utils::AllObjectBounds.push_back({ style.menux + last_object_x, style.menuy + last_object_y, style.checkbox_width + TextW + style.checkbox_clicked_width, style.checkbox_height });

		if (utils::Clicked(style.menux + last_object_x, style.menuy + last_object_y, style.checkbox_width + TextW + style.checkbox_clicked_width, style.checkbox_height, last_object_id) && !utils::InvalidateControlInput)
			*option = !(*option);

		auto state = utils::State(style.menux + last_object_x, style.menuy + last_object_y, style.checkbox_width + TextW + style.checkbox_clicked_width, style.checkbox_height);

		if (utils::InvalidateControlInput)
			state = ObjectState::OBJECTSTATE_IDLE;

		switch (state)
		{
		case ObjectState::OBJECTSTATE_IDLE:
			if (!(*option))
				g_pDraw->FilledBoxOutlined(style.menux + last_object_x, style.menuy + last_object_y, style.checkbox_width, style.checkbox_height, style.checkbox_color, style.checkbox_outline_color, style.checkbox_outline_thickness);
			else
				g_pDraw->FilledBoxOutlined(style.menux + last_object_x, style.menuy + last_object_y, style.checkbox_width, style.checkbox_height, style.checkbox_check_color, style.checkbox_check_outline_color, style.checkbox_outline_thickness);

			if (showname)
				g_pDraw->String(style.menux + last_object_x + style.checkbox_width + style.checkbox_clicked_width, style.menuy + last_object_y + style.checkbox_height - style.checkbox_clicked_height, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, name);
			break;
		case ObjectState::OBJECTSTATE_HOVERED:
			if (!(*option))
				g_pDraw->FilledBoxOutlined(style.menux + last_object_x - (popout ? 1 : 0), style.menuy + last_object_y - (popout ? 1 : 0), style.checkbox_width + (popout ? 1 : 0), style.checkbox_height + (popout ? 1 : 0), style.checkbox_color_hovered, style.checkbox_outline_color_hovered, style.checkbox_outline_thickness);
			else
				g_pDraw->FilledBoxOutlined(style.menux + last_object_x - (popout ? 1 : 0), style.menuy + last_object_y - (popout ? 1 : 0), style.checkbox_width + (popout ? 1 : 0), style.checkbox_height + (popout ? 1 : 0), style.checkbox_check_color_hovered, style.checkbox_check_outline_color_hovered, style.checkbox_outline_thickness);

			if (showname)
				g_pDraw->String(style.menux + last_object_x + style.checkbox_width + style.checkbox_clicked_width, style.menuy + last_object_y + style.checkbox_height - style.checkbox_clicked_height, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, name);
			break;
		case ObjectState::OBJECTSTATE_PRESSED:
			if (!(*option))
				g_pDraw->FilledBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), style.checkbox_width + (popout ? 2 : 0), style.checkbox_height + (popout ? 2 : 0), style.checkbox_color_pressed, style.checkbox_outline_color_pressed, style.checkbox_outline_thickness);
			else
				g_pDraw->FilledBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), style.checkbox_width + (popout ? 2 : 0), style.checkbox_height + (popout ? 2 : 0), style.checkbox_check_color_pressed, style.checkbox_check_outline_color_pressed, style.checkbox_outline_thickness);

			if (showname)
				g_pDraw->String(style.menux + last_object_x + style.checkbox_width + style.checkbox_clicked_width, style.menuy + last_object_y + style.checkbox_height - style.checkbox_clicked_height, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
			break;
		}
	}

	bool Button(const char* name, bool popout = true)
	{
		int TextW = utils::GetTextWidth(name, g_pDraw->fonts.fnormal);
		int TextH = utils::GetTextHeight(name, g_pDraw->fonts.fnormal);

		if (!onceperdraw)
		{
			last_object_x = menuobjectoffset_x;
			last_object_y = menuobjectoffset_y;
			onceperdraw = true;
		}
		else
		{
			last_object_y += style.item_spacing_y + TextH + 4;
			last_object_id++;
		}

		utils::AllObjectBounds.push_back({ style.menux + last_object_x, style.menuy + last_object_y, TextW + 12, TextH + 4 });

		auto state = utils::State(style.menux + last_object_x, style.menuy + last_object_y, TextW + 12, TextH + 4);

		if (utils::InvalidateControlInput)
			state = ObjectState::OBJECTSTATE_IDLE;

		switch (state)
		{
		case ObjectState::OBJECTSTATE_IDLE:
			g_pDraw->GradientBoxOutlined(style.menux + last_object_x, style.menuy + last_object_y, TextW + 12, TextH + 4, style.checkbox_outline_thickness, style.checkbox_color, style.checkbox_color1, style.checkbox_outline_color, true);
			g_pDraw->String(style.menux + last_object_x + 6, style.menuy + last_object_y + TextH - 10, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, name);
			break;
		case ObjectState::OBJECTSTATE_HOVERED:
			g_pDraw->GradientBoxOutlined(style.menux + last_object_x - (popout ? 1 : 0), style.menuy + last_object_y - (popout ? 1 : 0), TextW + 12 + (popout ? 1 : 0), TextH + 4 + (popout ? 1 : 0), style.checkbox_outline_thickness, style.checkbox_color_hovered, style.checkbox_color_hovered1, style.checkbox_outline_color_hovered, true);
			g_pDraw->String(style.menux + last_object_x + 6, style.menuy + last_object_y + TextH - 10, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, name);
			break;
		case ObjectState::OBJECTSTATE_PRESSED:
			g_pDraw->GradientBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), TextW + 12 + (popout ? 2 : 0), TextH + 4 + (popout ? 2 : 0), style.checkbox_outline_thickness, style.checkbox_color_pressed, style.checkbox_color_pressed1, style.checkbox_outline_color_pressed, true);
			g_pDraw->String(style.menux + last_object_x + 6, style.menuy + last_object_y + TextH - 10, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
			break;
		}

		if (utils::Clicked(style.menux + last_object_x, style.menuy + last_object_y, TextW + 12, TextH + 4, last_object_id) && !utils::InvalidateControlInput)
			return true;

		return false;
	}

	void KeyButton(const char* name, int* option, bool popout = true)
	{
		static unsigned long long LastTickCount64 = 0;
		if (GetTickCount64() > LastTickCount64 + 700)
		{
			static int animstep = 0;
			static char* animation[] = { "-", "\\", "|", "/" };
			utils::Keys[0] = animation[animstep];
			if (animstep >= 3)
				animstep = 0;
			animstep++;
			LastTickCount64 = GetTickCount64();
		}

		int TextW = *option > 0 ? utils::GetTextWidth(utils::Keys[*option], g_pDraw->fonts.fnormal) : 6;
		int TextH = *option > 0 ? utils::GetTextHeight(utils::Keys[*option], g_pDraw->fonts.fnormal) : 13;

		if (!onceperdraw)
		{
			last_object_x = menuobjectoffset_x;
			last_object_y = menuobjectoffset_y;
			onceperdraw = true;
		}
		else
		{
			last_object_y += style.item_spacing_y + TextH + 4;
			last_object_id++;
		}

		utils::AllObjectBounds.push_back({ style.menux + last_object_x, style.menuy + last_object_y, TextW + 12, TextH + 4 });

		auto state = utils::State(style.menux + last_object_x, style.menuy + last_object_y, TextW + 12, TextH + 4);

		if (utils::InvalidateControlInput)
			state = ObjectState::OBJECTSTATE_IDLE;

		switch (state)
		{
		case ObjectState::OBJECTSTATE_IDLE:
			if (utils::listeningforkeypress[last_object_id])
			{
				g_pDraw->GradientBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), TextW + 12 + (popout ? 2 : 0), TextH + 4 + (popout ? 2 : 0), style.checkbox_outline_thickness, style.checkbox_color_pressed, style.checkbox_color_pressed1, style.checkbox_outline_color_pressed, true);
				g_pDraw->String(style.menux + last_object_x + 8, style.menuy + last_object_y + TextH - 10, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, utils::Keys[*option]);
				g_pDraw->String(style.menux + last_object_x + TextW + 18, style.menuy + last_object_y + TextH - 12, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
			}
			else
			{
				g_pDraw->GradientBoxOutlined(style.menux + last_object_x, style.menuy + last_object_y, TextW + 12, TextH + 4, style.checkbox_outline_thickness, style.checkbox_color, style.checkbox_color1, style.checkbox_outline_color, true);
				g_pDraw->String(style.menux + last_object_x + 8, style.menuy + last_object_y + TextH - 10, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, utils::Keys[*option]);
				g_pDraw->String(style.menux + last_object_x + TextW + 18, style.menuy + last_object_y + TextH - 12, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, name);
			}
			break;
		case ObjectState::OBJECTSTATE_HOVERED:
			if (utils::listeningforkeypress[last_object_id])
			{
				g_pDraw->GradientBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), TextW + 12 + (popout ? 2 : 0), TextH + 4 + (popout ? 2 : 0), style.checkbox_outline_thickness, style.checkbox_color_pressed, style.checkbox_color_pressed1, style.checkbox_outline_color_pressed, true);
				g_pDraw->String(style.menux + last_object_x + 6, style.menuy + last_object_y + TextH - 10, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, utils::Keys[*option]);
				g_pDraw->String(style.menux + last_object_x + TextW + 18, style.menuy + last_object_y + TextH - 12, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
			}
			else
			{
				g_pDraw->GradientBoxOutlined(style.menux + last_object_x - (popout ? 1 : 0), style.menuy + last_object_y - (popout ? 1 : 0), TextW + 12 + (popout ? 1 : 0), TextH + 4 + (popout ? 1 : 0), style.checkbox_outline_thickness, style.checkbox_color_hovered, style.checkbox_color_hovered1, style.checkbox_outline_color_hovered, true);
				g_pDraw->String(style.menux + last_object_x + 8, style.menuy + last_object_y + TextH - 10, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, utils::Keys[*option]);
				g_pDraw->String(style.menux + last_object_x + TextW + 18, style.menuy + last_object_y + TextH - 12, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, name);
			}
			break;
		case ObjectState::OBJECTSTATE_PRESSED:
			g_pDraw->GradientBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), TextW + 12 + (popout ? 2 : 0), TextH + 4 + (popout ? 2 : 0), style.checkbox_outline_thickness, style.checkbox_color_pressed, style.checkbox_color_pressed1, style.checkbox_outline_color_pressed, true);
			g_pDraw->String(style.menux + last_object_x + 8, style.menuy + last_object_y + TextH - 10, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, utils::Keys[*option]);
			g_pDraw->String(style.menux + last_object_x + TextW + 18, style.menuy + last_object_y + TextH - 12, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
			break;
		}

		if (utils::Clicked(style.menux + last_object_x, style.menuy + last_object_y, TextW + 12, TextH + 4, last_object_id) && !utils::InvalidateControlInput)
			utils::listeningforkeypress[last_object_id] = true;

		if (utils::listeningforkeypress[last_object_id] && !utils::InvalidateControlInput)
		{
			for (int i = 0; i <= 124; ++i)
			{
				if (GetKeyState(i) & 0x8000)
				{
					if (i == VK_ESCAPE)
						*option = 0;
					else
						*option = i;

					for (int i = 0; i < ARRAYSIZE(utils::listeningforkeypress); ++i)
						utils::listeningforkeypress[i] = false;
				}
			}
		}
	}

	bool Tab(const char* name, int x, int y, int w, int h, bool selected, bool popout = true)
	{
		int TextW = utils::GetTextWidth(name, g_pDraw->fonts.fnormal);
		int TextH = utils::GetTextHeight(name, g_pDraw->fonts.fnormal);

		utils::AllObjectBounds.push_back({ style.menux + x, style.menuy + y, w + 12, h + 4 });

		auto state = utils::State(style.menux + x, style.menuy + y, w + 12, h + 4);

		if (utils::InvalidateControlInput)
			state = ObjectState::OBJECTSTATE_IDLE;

		switch (state)
		{
		case ObjectState::OBJECTSTATE_IDLE:
			if (!selected)
			{
				g_pDraw->GradientBox(style.menux + x, style.menuy + y - 3, w + 12, 4, D3DCOLOR_RGBA(191, 134, 191,255), D3DCOLOR_RGBA(1, 1, 1, 1), false);
				g_pDraw->GradientBox(style.menux + x, style.menuy + y, w + 12, h + 4, style.checkbox_color1, style.checkbox_color, false);
				g_pDraw->GradientBox(style.menux + x, style.menuy + y + h + 3, w + 12, 4, D3DCOLOR_RGBA(191, 134, 191, 255), D3DCOLOR_RGBA(1, 1, 1, 1), false);
				g_pDraw->String(style.menux + x + (w / 2) - (TextW / 2), style.menuy + y + (h / 2) - (TextH / 2) + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, name);
			}
			else
			{
				g_pDraw->GradientBox(style.menux + x, style.menuy + y - 3, w + 12, 4, D3DCOLOR_RGBA(191, 134, 191, 255), D3DCOLOR_RGBA(1, 1, 1, 1), false);
				g_pDraw->GradientBox(style.menux + x - (popout ? 2 : 0), style.menuy + y - (popout ? 2 : 0) + 2, w + 12 + (popout ? 2 : 0), h + 4 + (popout ? 2 : 0), style.checkbox_color_pressed1, style.checkbox_color_pressed, false);
				g_pDraw->GradientBox(style.menux + x, style.menuy + y + h + 3, w + 12, 4, D3DCOLOR_RGBA(191, 134, 191, 255), D3DCOLOR_RGBA(1, 1, 1, 1), false);
				g_pDraw->String(style.menux + x + (w / 2) - (TextW / 2), style.menuy + y + (h / 2) - (TextH / 2) + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
			}
			break;
		case ObjectState::OBJECTSTATE_HOVERED:
			if (!selected)
			{
				g_pDraw->GradientBox(style.menux + x, style.menuy + y - 3, w + 12, 4, D3DCOLOR_RGBA(191, 134, 191, 255), D3DCOLOR_RGBA(1, 1, 1, 1), false);
				g_pDraw->GradientBox(style.menux + x - (popout ? 1 : 0), style.menuy + y - (popout ? 1 : 0) + 2, w + 12 + (popout ? 1 : 0), h + 4 + (popout ? 1 : 0), style.checkbox_color_hovered1, style.checkbox_color_hovered, false);
				g_pDraw->GradientBox(style.menux + x, style.menuy + y + h + 3, w + 12, 4, D3DCOLOR_RGBA(191, 134, 191, 255), D3DCOLOR_RGBA(1, 1, 1, 1), false);
				g_pDraw->String(style.menux + x + (w / 2) - (TextW / 2), style.menuy + y + (h / 2) - (TextH / 2) + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, name);
			}
			else
			{
				g_pDraw->GradientBox(style.menux + x, style.menuy + y - 3, w + 12, 4, D3DCOLOR_RGBA(191, 134, 191, 255), D3DCOLOR_RGBA(1, 1, 1, 1), false);
				g_pDraw->GradientBox(style.menux + x - (popout ? 2 : 0), style.menuy + y - (popout ? 2 : 0) + 2, w + 12 + (popout ? 2 : 0), h + 4 + (popout ? 2 : 0), style.checkbox_color_pressed1, style.checkbox_color_pressed, false);
				g_pDraw->GradientBox(style.menux + x, style.menuy + y + h + 3, w + 12, 4, D3DCOLOR_RGBA(191, 134, 191, 255), D3DCOLOR_RGBA(1, 1, 1, 1), false);
				g_pDraw->String(style.menux + x + (w / 2) - (TextW / 2), style.menuy + y + (h / 2) - (TextH / 2) + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
			}
			break;
		case ObjectState::OBJECTSTATE_PRESSED:
			g_pDraw->GradientBox(style.menux + x, style.menuy + y - 3, w + 12, 4, D3DCOLOR_RGBA(191, 134, 191, 255), D3DCOLOR_RGBA(1, 1, 1, 1), false);
			g_pDraw->GradientBox(style.menux + x - (popout ? 2 : 0), style.menuy + y - (popout ? 2 : 0) + 2, w + 12 + (popout ? 2 : 0), h + 4 + (popout ? 2 : 0), style.checkbox_color_pressed1, style.checkbox_color_pressed, false);
			g_pDraw->GradientBox(style.menux + x, style.menuy + y + h + 3, w + 12, 4, D3DCOLOR_RGBA(191, 134, 191, 255), D3DCOLOR_RGBA(1, 1, 1, 1), false);
			g_pDraw->String(style.menux + x + (w / 2) - (TextW / 2), style.menuy + y + (h / 2) - (TextH / 2) + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
			break;
		}

		if (utils::Clicked(style.menux + x, style.menuy + y, w + 12, h + 4, last_object_id) && !utils::InvalidateControlInput)
			return true;

		return false;
	}

	bool Tab1(const char* name, int x, int y, int w, int h, bool selected, bool popout = true)
	{
		int TextW = utils::GetTextWidth(name, g_pDraw->fonts.fnormal);
		int TextH = utils::GetTextHeight(name, g_pDraw->fonts.fnormal);

		utils::AllObjectBounds.push_back({ style.menux + x, style.menuy + y, w + 12, h + 4 });

		auto state = utils::State(style.menux + x, style.menuy + y, w + 12, h + 4);

		if (utils::InvalidateControlInput)
			state = ObjectState::OBJECTSTATE_IDLE;

		switch (state)
		{
		case ObjectState::OBJECTSTATE_IDLE:
			if (!selected)
			{
				g_pDraw->GradientBox(style.menux + x, style.menuy + y, w + 12, h + 4, style.checkbox_color1, style.checkbox_color, false);
				g_pDraw->BorderedBox(style.menux + x - (popout ? 2 : 0), style.menuy + y - (popout ? 2 : 0) + 2, w + 12 + (popout ? 2 : 0), h + 4 + (popout ? 2 : 0), BLACK(255), 2);
				g_pDraw->String(style.menux + x + (w / 2) - (TextW / 2), style.menuy + y + (h / 2) - (TextH / 2) + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, name);
			}
			else
			{
				g_pDraw->GradientBox(style.menux + x - (popout ? 2 : 0), style.menuy + y - (popout ? 2 : 0) + 2, w + 12 + (popout ? 2 : 0), h + 4 + (popout ? 2 : 0), style.checkbox_color_pressed1, style.checkbox_color_pressed, false);
				g_pDraw->BorderedBox(style.menux + x - (popout ? 2 : 0), style.menuy + y - (popout ? 2 : 0) + 2, w + 12 + (popout ? 2 : 0), h + 4 + (popout ? 2 : 0), BLACK(255), 2);
				g_pDraw->String(style.menux + x + (w / 2) - (TextW / 2), style.menuy + y + (h / 2) - (TextH / 2) + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
			}
			break;
		case ObjectState::OBJECTSTATE_HOVERED:
			if (!selected)
			{
				g_pDraw->GradientBox(style.menux + x - (popout ? 1 : 0), style.menuy + y - (popout ? 1 : 0) + 2, w + 12 + (popout ? 1 : 0), h + 4 + (popout ? 1 : 0), style.checkbox_color_hovered1, style.checkbox_color_hovered, false);
				g_pDraw->BorderedBox(style.menux + x - (popout ? 2 : 0), style.menuy + y - (popout ? 2 : 0) + 2, w + 12 + (popout ? 2 : 0), h + 4 + (popout ? 2 : 0), BLACK(255), 2);
				g_pDraw->String(style.menux + x + (w / 2) - (TextW / 2), style.menuy + y + (h / 2) - (TextH / 2) + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, name);
			}
			else
			{
				g_pDraw->GradientBox(style.menux + x - (popout ? 2 : 0), style.menuy + y - (popout ? 2 : 0) + 2, w + 12 + (popout ? 2 : 0), h + 4 + (popout ? 2 : 0), style.checkbox_color_pressed1, style.checkbox_color_pressed, false);
				g_pDraw->BorderedBox(style.menux + x - (popout ? 2 : 0), style.menuy + y - (popout ? 2 : 0) + 2, w + 12 + (popout ? 2 : 0), h + 4 + (popout ? 2 : 0), BLACK(255), 2);
				g_pDraw->String(style.menux + x + (w / 2) - (TextW / 2), style.menuy + y + (h / 2) - (TextH / 2) + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
			}
			break;
		case ObjectState::OBJECTSTATE_PRESSED:
			g_pDraw->GradientBox(style.menux + x - (popout ? 2 : 0), style.menuy + y - (popout ? 2 : 0) + 2, w + 12 + (popout ? 2 : 0), h + 4 + (popout ? 2 : 0), style.checkbox_color_pressed1, style.checkbox_color_pressed, false);
			g_pDraw->BorderedBox(style.menux + x - (popout ? 2 : 0), style.menuy + y - (popout ? 2 : 0) + 2, w + 12 + (popout ? 2 : 0), h + 4 + (popout ? 2 : 0), BLACK(255),2);
			g_pDraw->String(style.menux + x + (w / 2) - (TextW / 2), style.menuy + y + (h / 2) - (TextH / 2) + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
			break;
		}

		if (utils::Clicked(style.menux + x, style.menuy + y, w + 12, h + 4, last_object_id) && !utils::InvalidateControlInput)
			return true;

		return false;
	}

	bool insideslider[500] = { false };
	void SliderFloat(const char* name, float* option, float min, float max, bool popout = true, bool showname = true)
	{
		if (!onceperdraw)
		{
			last_object_x = menuobjectoffset_x;
			last_object_y = menuobjectoffset_y;
			onceperdraw = true;
		}
		else
		{
			last_object_y += style.item_spacing_y + style.checkbox_height;
			last_object_id++;
		}

		utils::AllObjectBounds.push_back({ style.menux + last_object_x, style.menuy + last_object_y, style.slider_width, style.slider_height });

		auto state = utils::State(style.menux + last_object_x, style.menuy + last_object_y, style.slider_width, style.slider_height);

		if (utils::InvalidateControlInput)
			state = ObjectState::OBJECTSTATE_IDLE;

		if (state == ObjectState::OBJECTSTATE_PRESSED)
		{
			insideslider[last_object_id] = true;

			for (int i = 0; i < ARRAYSIZE(insideslider); ++i)
				if (i != last_object_id)
					insideslider[i] = false;
		}

		if (!(GetKeyState(VK_LBUTTON) & 0x8000) && insideslider[last_object_id])
			insideslider[last_object_id] = false;

		float newval = utils::GetSliderValueFloat(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), style.slider_width, style.slider_height, min, max);
		int offset = utils::GetSliderPixelOffset(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), style.slider_width, style.slider_height);

		if (insideslider[last_object_id] && offset >= 0.0f)
			*option = newval;

		int newpixel = *option / (max / style.slider_width);

		// fix for value being out of slider if changed from another with different range
		if (*option > max)
			newpixel = style.slider_width;

		int TextW = utils::GetTextWidth(std::to_string(*option).c_str(), g_pDraw->fonts.fsmall);
		int TextH = utils::GetTextHeight(std::to_string(*option).c_str(), g_pDraw->fonts.fsmall);

		auto OptionValueStdString = std::to_string(*option);
		OptionValueStdString.pop_back();
		OptionValueStdString.pop_back();
		OptionValueStdString.pop_back();
		OptionValueStdString.pop_back();
		auto OptionValueString = OptionValueStdString.c_str();

		if (insideslider[last_object_id])
		{
			g_pDraw->FilledBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), style.slider_width + (popout ? 2 : 0), style.slider_height + (popout ? 2 : 0), style.slider_color_pressed, style.slider_outline_color_pressed, style.slider_outline_thickness);
			g_pDraw->FilledBox(style.menux + last_object_x - (popout ? 2 : 0) + 1, style.menuy + last_object_y - (popout ? 2 : 0) + 1, newpixel + (popout ? 2 : 0) - 2, style.slider_height + (popout ? 2 : 0) - 1, style.slider_slide_color_pressed);
			g_pDraw->String(style.menux + last_object_x - (popout ? 2 : 0) + 6, style.menuy + last_object_y - (popout ? 2 : 0) + (TextH / 2), FONT_LEFT, g_pDraw->fonts.fsmall, false, style.slider_font_color_pressed, OptionValueString);

			if (showname)
				g_pDraw->String(style.menux + last_object_x + style.slider_width + 12, style.menuy + last_object_y - (popout ? 2 : 0), FONT_LEFT, g_pDraw->fonts.fnormal, false, style.slider_font_color_pressed, name);
		}

		switch (state)
		{
		case ObjectState::OBJECTSTATE_IDLE:
			if (!insideslider[last_object_id])
			{
				g_pDraw->FilledBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), style.slider_width + (popout ? 2 : 0), style.slider_height + (popout ? 2 : 0), style.slider_color, style.slider_outline_color, style.slider_outline_thickness);
				g_pDraw->FilledBox(style.menux + last_object_x - (popout ? 2 : 0) + 1, style.menuy + last_object_y - (popout ? 2 : 0) + 1, newpixel + (popout ? 2 : 0) - 2, style.slider_height + (popout ? 2 : 0) - 1, style.slider_slide_color);
				g_pDraw->String(style.menux + last_object_x - (popout ? 2 : 0) + 6, style.menuy + last_object_y - (popout ? 2 : 0) + (TextH / 2), FONT_LEFT, g_pDraw->fonts.fsmall, false, style.slider_font_color, OptionValueString);

				if (showname)
					g_pDraw->String(style.menux + last_object_x + style.slider_width + 12, style.menuy + last_object_y - (popout ? 2 : 0), FONT_LEFT, g_pDraw->fonts.fnormal, false, style.slider_font_color, name);
			}
			break;
		case ObjectState::OBJECTSTATE_HOVERED:
			if (!insideslider[last_object_id])
			{
				g_pDraw->FilledBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), style.slider_width + (popout ? 2 : 0), style.slider_height + (popout ? 2 : 0), style.slider_color_hovered, style.slider_outline_color_hovered, style.slider_outline_thickness);
				g_pDraw->FilledBox(style.menux + last_object_x - (popout ? 2 : 0) + 1, style.menuy + last_object_y - (popout ? 2 : 0) + 1, newpixel + (popout ? 2 : 0) - 2, style.slider_height + (popout ? 2 : 0) - 1, style.slider_slide_color_hovered);
				g_pDraw->String(style.menux + last_object_x - (popout ? 2 : 0) + 6, style.menuy + last_object_y - (popout ? 2 : 0) + (TextH / 2), FONT_LEFT, g_pDraw->fonts.fsmall, false, style.slider_font_color_hovered, OptionValueString);

				if (showname)
					g_pDraw->String(style.menux + last_object_x + style.slider_width + 12, style.menuy + last_object_y - (popout ? 2 : 0), FONT_LEFT, g_pDraw->fonts.fnormal, false, style.slider_font_color_hovered, name);
			}
			break;
		}
	}

	void SliderInt(const char* name, int* option, float min, float max, bool popout = true, bool showname = true)
	{
		if (!onceperdraw)
		{
			last_object_x = menuobjectoffset_x;
			last_object_y = menuobjectoffset_y;
			onceperdraw = true;
		}
		else
		{
			last_object_y += style.item_spacing_y + style.checkbox_height;
			last_object_id++;
		}

		utils::AllObjectBounds.push_back({ style.menux + last_object_x, style.menuy + last_object_y, style.slider_width, style.slider_height });

		auto state = utils::State(style.menux + last_object_x, style.menuy + last_object_y, style.slider_width, style.slider_height);

		if (utils::InvalidateControlInput)
			state = ObjectState::OBJECTSTATE_IDLE;

		if (state == ObjectState::OBJECTSTATE_PRESSED)
		{
			insideslider[last_object_id] = true;

			for (int i = 0; i < ARRAYSIZE(insideslider); ++i)
				if (i != last_object_id)
					insideslider[i] = false;
		}

		if (!(GetKeyState(VK_LBUTTON) & 0x8000) && insideslider[last_object_id])
			insideslider[last_object_id] = false;

		int newval = utils::GetSliderValueInt(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), style.slider_width, style.slider_height, min, max);
		int offset = utils::GetSliderPixelOffset(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), style.slider_width, style.slider_height);

		if (insideslider[last_object_id] && offset >= 0.0f)
			*option = newval;

		int newpixel = *option / (max / style.slider_width);

		// fix for value being out of slider if changed from another with different range
		if (*option > max)
			newpixel = style.slider_width;

		int TextW = utils::GetTextWidth(std::to_string(*option).c_str(), g_pDraw->fonts.fsmall);
		int TextH = utils::GetTextHeight(std::to_string(*option).c_str(), g_pDraw->fonts.fsmall);

		if (insideslider[last_object_id])
		{
			g_pDraw->FilledBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), style.slider_width + (popout ? 2 : 0), style.slider_height + (popout ? 2 : 0), style.slider_color_pressed, style.slider_outline_color_pressed, style.slider_outline_thickness);
			g_pDraw->FilledBox(style.menux + last_object_x - (popout ? 2 : 0) + 1, style.menuy + last_object_y - (popout ? 2 : 0) + 1, newpixel + (popout ? 2 : 0) - 2, style.slider_height + (popout ? 2 : 0) - 1, style.slider_slide_color_pressed);
			g_pDraw->String(style.menux + last_object_x - (popout ? 2 : 0) + 6, style.menuy + last_object_y - (popout ? 2 : 0) + (TextH / 2) - 1, FONT_LEFT, g_pDraw->fonts.fsmall, false, style.slider_font_color_pressed, std::to_string(*option).c_str());

			if (showname)
				g_pDraw->String(style.menux + last_object_x + style.slider_width + 12, style.menuy + last_object_y - (popout ? 2 : 0), FONT_LEFT, g_pDraw->fonts.fnormal, false, style.slider_font_color_pressed, name);
		}

		switch (state)
		{
		case ObjectState::OBJECTSTATE_IDLE:
			if (!insideslider[last_object_id])
			{
				g_pDraw->FilledBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), style.slider_width + (popout ? 2 : 0), style.slider_height + (popout ? 2 : 0), style.slider_color, style.slider_outline_color, style.slider_outline_thickness);
				g_pDraw->FilledBox(style.menux + last_object_x - (popout ? 2 : 0) + 1, style.menuy + last_object_y - (popout ? 2 : 0) + 1, newpixel + (popout ? 2 : 0) - 2, style.slider_height + (popout ? 2 : 0) - 1, style.slider_slide_color);
				g_pDraw->String(style.menux + last_object_x - (popout ? 2 : 0) + 6, style.menuy + last_object_y - (popout ? 2 : 0) + (TextH / 2) - 1, FONT_LEFT, g_pDraw->fonts.fsmall, false, style.slider_font_color, std::to_string(*option).c_str());

				if (showname)
					g_pDraw->String(style.menux + last_object_x + style.slider_width + 12, style.menuy + last_object_y - (popout ? 2 : 0), FONT_LEFT, g_pDraw->fonts.fnormal, false, style.slider_font_color, name);
			}
			break;
		case ObjectState::OBJECTSTATE_HOVERED:
			if (!insideslider[last_object_id])
			{
				g_pDraw->FilledBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), style.slider_width + (popout ? 2 : 0), style.slider_height + (popout ? 2 : 0), style.slider_color_hovered, style.slider_outline_color_hovered, style.slider_outline_thickness);
				g_pDraw->FilledBox(style.menux + last_object_x - (popout ? 2 : 0) + 1, style.menuy + last_object_y - (popout ? 2 : 0) + 1, newpixel + (popout ? 2 : 0) - 2, style.slider_height + (popout ? 2 : 0) - 1, style.slider_slide_color_hovered);
				g_pDraw->String(style.menux + last_object_x - (popout ? 2 : 0) + 6, style.menuy + last_object_y - (popout ? 2 : 0) + (TextH / 2 - 1), FONT_LEFT, g_pDraw->fonts.fsmall, false, style.slider_font_color_hovered, std::to_string(*option).c_str());

				if (showname)
					g_pDraw->String(style.menux + last_object_x + style.slider_width + 12, style.menuy + last_object_y - (popout ? 2 : 0), FONT_LEFT, g_pDraw->fonts.fnormal, false, style.slider_font_color_hovered, name);
			}
			break;
		}
	}

	void Text(const char* name)
	{
		int TextW = utils::GetTextWidth(name, g_pDraw->fonts.fnormal);

		if (!onceperdraw)
		{
			last_object_x = menuobjectoffset_x;
			last_object_y = menuobjectoffset_y;
			onceperdraw = true;
		}
		else
		{
			last_object_y += style.item_spacing_y + style.checkbox_height;
			last_object_id++;
		}

		auto state = utils::State(style.menux + last_object_x, style.menuy + last_object_y, style.checkbox_width + TextW + 12, style.checkbox_height);

		if (utils::InvalidateControlInput)
			state = ObjectState::OBJECTSTATE_IDLE;

		switch (state)
		{
		case ObjectState::OBJECTSTATE_IDLE:
			g_pDraw->String(style.menux + last_object_x, style.menuy + last_object_y, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, name);
			break;
		case ObjectState::OBJECTSTATE_HOVERED:
			g_pDraw->String(style.menux + last_object_x, style.menuy + last_object_y, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, name);
			break;
		case ObjectState::OBJECTSTATE_PRESSED:
			g_pDraw->String(style.menux + last_object_x, style.menuy + last_object_y, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, name);
			break;
		}
	}

	void TextLink(const char* url)
	{
		int TextW = utils::GetTextWidth(url, g_pDraw->fonts.fnormal);
		int TextH = utils::GetTextHeight(url, g_pDraw->fonts.fnormal);

		if (!onceperdraw)
		{
			last_object_x = menuobjectoffset_x;
			last_object_y = menuobjectoffset_y;
			onceperdraw = true;
		}
		else
		{
			last_object_y += style.item_spacing_y + style.checkbox_height;
			last_object_id++;
		}

		if (utils::Clicked(style.menux + last_object_x, style.menuy + last_object_y, style.checkbox_width + TextW + 12, style.checkbox_height, last_object_id) && !utils::InvalidateControlInput)
		{
			if (!strstr(url, "http://") && !strstr(url, "https://"))
				ShellExecuteA(0, "open", (std::string("http://") + std::string(url)).c_str(), 0, 0, SW_SHOW);
			else
				ShellExecuteA(0, "open", url, 0, 0, SW_SHOW);
		}

		auto state = utils::State(style.menux + last_object_x, style.menuy + last_object_y, style.checkbox_width + TextW + 12, style.checkbox_height);

		if (utils::InvalidateControlInput)
			state = ObjectState::OBJECTSTATE_IDLE;

		switch (state)
		{
		case ObjectState::OBJECTSTATE_IDLE:
			g_pDraw->String(style.menux + last_object_x, style.menuy + last_object_y, FONT_LEFT, g_pDraw->fonts.fnormal, false, D3DCOLOR_RGBA(0, 100, 255, 255), url);
			g_pDraw->Line(style.menux + last_object_x, style.menuy + last_object_y + TextH, style.menux + last_object_x + TextW, style.menuy + last_object_y + TextH, D3DCOLOR_RGBA(0, 100, 255, 255));
			break;
		case ObjectState::OBJECTSTATE_HOVERED:
			g_pDraw->String(style.menux + last_object_x, style.menuy + last_object_y, FONT_LEFT, g_pDraw->fonts.fnormal, false, D3DCOLOR_RGBA(0, 100, 255, 255), url);
			g_pDraw->Line(style.menux + last_object_x, style.menuy + last_object_y + TextH, style.menux + last_object_x + TextW, style.menuy + last_object_y + TextH, D3DCOLOR_RGBA(0, 100, 255, 255));
			break;
		case ObjectState::OBJECTSTATE_PRESSED:
			g_pDraw->String(style.menux + last_object_x, style.menuy + last_object_y, FONT_LEFT, g_pDraw->fonts.fnormal, false, D3DCOLOR_RGBA(0, 100, 255, 255), url);
			g_pDraw->Line(style.menux + last_object_x, style.menuy + last_object_y + TextH, style.menux + last_object_x + TextW, style.menuy + last_object_y + TextH, D3DCOLOR_RGBA(0, 100, 255, 255));
			break;
		}
	}

	void TextBox(const char* name, char** option, bool popout = true)
	{
		int TextW = utils::GetTextWidth(name, g_pDraw->fonts.fnormal);
		int TextH = utils::GetTextHeight(name, g_pDraw->fonts.fnormal);

		if (!onceperdraw)
		{
			last_object_x = menuobjectoffset_x;
			last_object_y = menuobjectoffset_y;
			onceperdraw = true;
		}
		else
		{
			last_object_y += style.item_spacing_y + TextH + 4;
			last_object_id++;
		}

		utils::AllObjectBounds.push_back({ style.menux + last_object_x + TextW + 6, style.menuy + last_object_y, 175, TextH + 4 });

		if (utils::Clicked(style.menux + last_object_x + TextW + 6, style.menuy + last_object_y, 175, TextH + 4, last_object_id) && !utils::InvalidateControlInput)
			selectedtextbox = last_object_id;

		if (selectedtextbox >= 0 && selectedtextbox == last_object_id)
		{
			for (int i = 0; i <= 124; ++i)
			{
				static bool pressingakey = false;
				static int keypressed = 0;
				if (GetKeyState(i) & 0x8000 && !pressingakey && keypressed <= 0)
				{
					if (i >= 0x30 && i <= 0x5A)
					{
						std::string buf = *option;
						char character = (char)MapVirtualKeyA(i, 2);
						if (GetKeyState(VK_CAPITAL) & 0x8000 || GetKeyState(VK_LSHIFT) & 0x8000 || GetKeyState(VK_RSHIFT) & 0x8000)
							buf += toupper(character);
						else
							buf += tolower(character);
						*option = _strdup(buf.c_str());
						pressingakey = true;
						keypressed = i;
					}

					for (int i = 0; i < ARRAYSIZE(utils::listeningforkeypress); ++i)
						utils::listeningforkeypress[i] = false;
				}
				else if (!(GetKeyState(keypressed) & 0x8000) && pressingakey && keypressed > 0)
				{
					pressingakey = false;
					keypressed = 0;
				}

				if (GetAsyncKeyState(VK_ESCAPE) & 1)
					selectedtextbox = -1;

				if (GetAsyncKeyState(VK_TAB) & 1)
					selectedtextbox++;

				if (GetAsyncKeyState(VK_BACK) & 1)
				{
					std::string buf = *option;
					if (buf.size() > 0)
						buf.pop_back();
					*option = _strdup(buf.c_str());
				}

				if (GetAsyncKeyState(VK_SPACE) & 1)
				{
					std::string buf = *option;
					buf.append(" ");
				}
			}

			int TextW1 = utils::GetTextWidth(*option, g_pDraw->fonts.fnormal);
			int TextH1 = utils::GetTextHeight(*option, g_pDraw->fonts.fnormal);
			if (style.menux + last_object_x + TextW + 6 + TextW1 + 12 >= style.menux + last_object_x + TextW + 181)
			{
				std::string buf = *option;
				if (buf.size() > 0)
					buf.pop_back();
				*option = _strdup(buf.c_str());
			}
		}

		auto state = utils::State(style.menux + last_object_x + TextW + 6, style.menuy + last_object_y, 175, TextH + 4);

		if (utils::InvalidateControlInput)
			state = ObjectState::OBJECTSTATE_IDLE;

		if (selectedtextbox == last_object_id)
		{
			if (state == ObjectState::OBJECTSTATE_PRESSED)
			{
				g_pDraw->GradientBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0) + TextW + 6, style.menuy + last_object_y - (popout ? 2 : 0), 175 + (popout ? 2 : 0), TextH + 4 + (popout ? 2 : 0), style.checkbox_outline_thickness, style.checkbox_color_pressed, style.checkbox_color_pressed1, style.checkbox_outline_color_pressed, true);
				g_pDraw->String(style.menux + last_object_x, style.menuy + last_object_y, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
				g_pDraw->String(style.menux + last_object_x + TextW + 12, style.menuy + last_object_y + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, *option);
			}
			else
			{
				g_pDraw->GradientBoxOutlined(style.menux + last_object_x - (popout ? 1 : 0) + TextW + 6, style.menuy + last_object_y - (popout ? 1 : 0), 175 + (popout ? 1 : 0), TextH + 4 + (popout ? 1 : 0), style.checkbox_outline_thickness, style.checkbox_color_hovered, style.checkbox_color_hovered1, style.checkbox_outline_color_hovered, true);
				g_pDraw->String(style.menux + last_object_x, style.menuy + last_object_y, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, name);
				g_pDraw->String(style.menux + last_object_x + TextW + 12, style.menuy + last_object_y + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, *option);
			}

			if (GetKeyState(VK_LBUTTON) & 0x8000 && !utils::Pressed(style.menux + last_object_x + TextW + 6, style.menuy + last_object_y, 175, TextH + 4))
				selectedtextbox = -1;
		}

		switch (state)
		{
		case ObjectState::OBJECTSTATE_IDLE:
			if (selectedtextbox != last_object_id)
			{
				g_pDraw->GradientBoxOutlined(style.menux + last_object_x + TextW + 6, style.menuy + last_object_y, 175, TextH + 4, style.checkbox_outline_thickness, style.checkbox_color, style.checkbox_color1, style.checkbox_outline_color, true);
				g_pDraw->String(style.menux + last_object_x, style.menuy + last_object_y, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, name);
				g_pDraw->String(style.menux + last_object_x + TextW + 12, style.menuy + last_object_y + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, *option);
			}
			break;
		case ObjectState::OBJECTSTATE_HOVERED:
			if (selectedtextbox != last_object_id)
			{
				g_pDraw->GradientBoxOutlined(style.menux + last_object_x - (popout ? 1 : 0) + TextW + 6, style.menuy + last_object_y - (popout ? 1 : 0), 175 + (popout ? 1 : 0), TextH + 4 + (popout ? 1 : 0), style.checkbox_outline_thickness, style.checkbox_color_hovered, style.checkbox_color_hovered1, style.checkbox_outline_color_hovered, true);
				g_pDraw->String(style.menux + last_object_x, style.menuy + last_object_y, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, name);
				g_pDraw->String(style.menux + last_object_x + TextW + 12, style.menuy + last_object_y + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, *option);
			}
			break;
		case ObjectState::OBJECTSTATE_PRESSED:
			if (selectedtextbox != last_object_id)
			{
				g_pDraw->GradientBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0) + TextW + 6, style.menuy + last_object_y - (popout ? 2 : 0), 175 + (popout ? 2 : 0), TextH + 4 + (popout ? 2 : 0), style.checkbox_outline_thickness, style.checkbox_color_pressed, style.checkbox_color_pressed1, style.checkbox_outline_color_pressed, true);
				g_pDraw->String(style.menux + last_object_x, style.menuy + last_object_y, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, name);
				g_pDraw->String(style.menux + last_object_x + TextW + 12, style.menuy + last_object_y + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, *option);
			}
			break;
		}
	}

	void DropDown(const char* name, std::vector<const char*> contents, int* option, bool popout = true)
	{
		int TextW = utils::GetTextWidth(name, g_pDraw->fonts.fnormal);
		int TextH = utils::GetTextHeight(name, g_pDraw->fonts.fnormal);

		if (!onceperdraw)
		{
			last_object_x = menuobjectoffset_x;
			last_object_y = menuobjectoffset_y;
			onceperdraw = true;
		}
		else
		{
			last_object_y += style.item_spacing_y + style.checkbox_height;
			last_object_id++;
		}

		RECT vals1 = { style.menux + last_object_x, style.menuy + last_object_y, TextW + 12, TextH + 4 };
		utils::AllObjectBounds.push_back({ vals1.left, vals1.top, vals1.right, vals1.bottom }); // dropdown name

		int LargestObjectWidth = 0;
		int LargestObjectHeight = 0;
		static bool waspressed = false;
		if (waspressed && !(GetKeyState(VK_LBUTTON) & 0x8000))
			waspressed = false;

		if (last_object_id == selecteddropdown && utils::InvalidateControlInput) // if selected, create the box with room for every option
		{
			if (GetKeyState(VK_ESCAPE) & 0x8000)
			{
				last_object_id = 0;
				utils::InvalidateControlInput = false;
			}

			for (auto& optionname : contents)
			{
				auto w = utils::GetTextWidth(optionname, g_pDraw->fonts.fnormal);
				LargestObjectHeight += utils::GetTextHeight(optionname, g_pDraw->fonts.fnormal);

				if (w > LargestObjectWidth)
					LargestObjectWidth = w;
			}

			int ValuesInArray = 0;
			for (auto& optionname : contents)
				ValuesInArray++;

			RECT vals = { style.menux + last_object_x + TextW + 7, style.menuy + last_object_y, LargestObjectWidth + 12, 16 * ValuesInArray + 16 };
			utils::AllObjectBounds.push_back({ vals.left, vals.top, vals.right, vals.bottom }); // text box

			if (utils::Hovered(vals.left, vals.top, vals.right, vals.bottom) && GetKeyState(VK_LBUTTON) & 0x8000) // if clicked inside box, algorithimically get the clicked option by name on screen and exits list
			{
				int CurrentItem = 0;
				int last_height = vals.top;
				for (auto& optionname : contents) {
					int t_height = utils::GetTextHeight(optionname, g_pDraw->fonts.fnormal);

					last_height += 12;

					if (utils::Hovered(vals.left, last_height, vals.right, t_height)) { // inside this option on screen
						*option = CurrentItem;
						break;
					}

					CurrentItem++;
					last_height += 4;
				}

				last_object_id = 0;
				utils::InvalidateControlInput = false;
			}
			else // if clicked outside of box, cancels
			{
				bool ClickedAnObject = false;

				for (auto& ObjectRegion : utils::AllObjectBounds)
				{
					if (utils::Pressed(ObjectRegion.left, ObjectRegion.top, ObjectRegion.right, ObjectRegion.bottom))
						ClickedAnObject = true;
				}

				if (ClickedAnObject)
				{
					last_object_id = 0;
					utils::InvalidateControlInput = false;
					waspressed = true;
				}
			}

			// drawing will happen on s1lentgui::end to be drawingw on top of everything else!
			// which is why it isnt here after this line!

			auto state = utils::State(vals.left, vals.top, vals.right, vals.bottom);
			DropdownDrawing.push_back(CDropdownDrawing(name, contents, option, popout, vals.left, vals.top, vals.right, vals.bottom, state, style.menux + last_object_x, style.menuy + last_object_y));
		}
		else // if not selected, create box for current option
		{
			LargestObjectWidth = utils::GetTextWidth(contents.at(*option), g_pDraw->fonts.fnormal);
			LargestObjectHeight = utils::GetTextHeight(contents.at(*option), g_pDraw->fonts.fnormal);

			RECT vals = { style.menux + last_object_x + TextW + 7, style.menuy + last_object_y, LargestObjectWidth + 12, LargestObjectHeight + 4 };

			if (utils::Clicked(vals.left, vals.top, vals.right, vals.bottom, last_object_id))
			{
				selecteddropdown = last_object_id;
				utils::InvalidateControlInput = true;
			}

			utils::AllObjectBounds.push_back({ vals.left, vals.top, vals.right, vals.bottom }); // text box
																								// Drawing the dropdown on the selected item without the list
			auto state = utils::State(vals.left, vals.top, vals.right, vals.bottom);

			switch (state)
			{
			case ObjectState::OBJECTSTATE_IDLE: // draw idle
				g_pDraw->String(vals1.left, vals1.top, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, name);
				g_pDraw->GradientBoxOutlined(vals.left - (popout ? 2 : 0), vals.top - (popout ? 2 : 0), vals.right + (popout ? 2 : 0), vals.bottom + (popout ? 2 : 0), style.checkbox_outline_thickness, style.checkbox_color, style.checkbox_color1, style.checkbox_outline_color, true);
				g_pDraw->String(vals.left + 6, vals.top + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, contents.at(*option));
				break;
			case ObjectState::OBJECTSTATE_HOVERED: // draw when hovered
				g_pDraw->String(vals1.left, vals1.top, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, name);
				g_pDraw->GradientBoxOutlined(vals.left - (popout ? 2 : 0), vals.top - (popout ? 2 : 0), vals.right + (popout ? 2 : 0), vals.bottom + (popout ? 2 : 0), style.checkbox_outline_thickness, style.checkbox_color_hovered, style.checkbox_color_hovered1, style.checkbox_outline_color_hovered, true);
				g_pDraw->String(vals.left + 6, vals.top + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, contents.at(*option));
				break;
			case ObjectState::OBJECTSTATE_PRESSED: // draw pressed down
				g_pDraw->String(vals1.left, vals1.top, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color, name);
				g_pDraw->GradientBoxOutlined(vals.left - (popout ? 2 : 0), vals.top - (popout ? 2 : 0), vals.right + (popout ? 2 : 0), vals.bottom + (popout ? 2 : 0), style.checkbox_outline_thickness, style.checkbox_color_pressed, style.checkbox_color_pressed1, style.checkbox_outline_color_pressed, true);
				g_pDraw->String(vals.left + 6, vals.top + 2, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_pressed, contents.at(*option));
				break;
			}
		}
	}

	void ColorPicker(const char* name, Color* color, bool &expanded, bool popout = true, bool showname = true) {
		
		int TextW = utils::GetTextWidth("Exp", g_pDraw->fonts.fnormal);
		int TextH = TextW;

		if (!onceperdraw)
		{
			last_object_x = menuobjectoffset_x;
			last_object_y = menuobjectoffset_y;
			onceperdraw = true;
		}
		else
		{
			last_object_y += style.item_spacing_y + TextH + 4;
			last_object_id++;
		}

		utils::AllObjectBounds.push_back({ style.menux + last_object_x, style.menuy + last_object_y, TextW + 12, TextH + 4 });

		auto state = utils::State(style.menux + last_object_x, style.menuy + last_object_y, TextW + 12, TextH + 4);

		if (utils::InvalidateControlInput)
			state = ObjectState::OBJECTSTATE_IDLE;


		g_pDraw->FilledBoxOutlined(style.menux + last_object_x - (popout ? 2 : 0), style.menuy + last_object_y - (popout ? 2 : 0), TextW + 12 + (popout ? 2 : 0), TextH + 4 + (popout ? 2 : 0), D3DCOLOR_RGBA(color->r(),color->g(),color->b(),color->a()),style.checkbox_outline_color,2);
		g_pDraw->String(style.menux + last_object_x + (TextW*2) + 12 + (popout ? 2 : 0), style.menuy + last_object_y + TextH - 10, FONT_LEFT, g_pDraw->fonts.fnormal, false, style.checkbox_font_color_hovered, name);


		if (utils::Clicked(style.menux + last_object_x, style.menuy + last_object_y, TextW + 12, TextH + 4, last_object_id) && !utils::InvalidateControlInput)
			expanded = !expanded;

		if (expanded)
		{
			int tempr, tempg, tempb, tempa;
			color->GetColor(tempr,tempg,tempb,tempa);
			s1lentgui::SliderInt("Red", &tempr, 0, 255);
			s1lentgui::SliderInt("Green", &tempg, 0, 255);
			s1lentgui::SliderInt("Blue", &tempb, 0, 255);
			s1lentgui::SliderInt("Alpha", &tempa, 0, 255);
			color->SetColor(tempr, tempg, tempb, tempa);
		}
		
	}

}