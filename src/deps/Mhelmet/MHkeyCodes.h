#pragma once

#include <cstdint>
#include <ostream>

namespace MHelmet
{	
	typedef enum class KeyCode : uint16_t
	{
		// FILE glfw3.h
		Space = 32,
		Apostrophe = 39,	/* ' */
		Comma = 44,			/* , */
		Minus = 45,			/* - */
		Period = 46,		/* . */
		Slash = 47,			/* / */

		D0 = 48,			/* 0 */
		D1 = 49,			/* 1 */
		D2 = 50,			/* 2 */
		D3 = 51,			/* 3 */
		D4 = 52,			/* 4 */
		D5 = 53,			/* 5 */
		D6 = 54,			/* 6 */
		D7 = 55,			/* 7 */
		D8 = 56,			/* 8 */
		D9 = 57,			/* 9 */

		Semicolon = 59,		/* ; */
		Equal = 61,			/* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,	/* [ */
		Backslash = 92,		/* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,	/* ` */

		World1 = 161,		/* non-US #1 */
		World2 = 162,		/* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

using MHKey = MHelmet::Key;
	
// FILE glfw3.h
#define MH_KEY_SPACE              MHKey::Space
#define MH_KEY_APOSTROPHE         MHKey::Backslash  /* ' */
#define MH_KEY_COMMA              MHKey::Comma      /* , */
#define MH_KEY_MINUS              MHKey::Minus      /* - */
#define MH_KEY_PERIOD             MHKey::Period     /* . */
#define MH_KEY_SLASH              MHKey::Slash      /* / */
#define MH_KEY_0                  MHKey::D0
#define MH_KEY_1                  MHKey::D1
#define MH_KEY_2                  MHKey::D2
#define MH_KEY_3                  MHKey::D3
#define MH_KEY_4                  MHKey::D4
#define MH_KEY_5                  MHKey::D5
#define MH_KEY_6                  MHKey::D6
#define MH_KEY_7                  MHKey::D7
#define MH_KEY_8                  MHKey::D8
#define MH_KEY_9                  MHKey::D9
#define MH_KEY_SEMICOLON          MHKey::Semicolon  /* ; */
#define MH_KEY_EQUAL              MHKey::Equal      /* = */
#define MH_KEY_A                  MHKey::A
#define MH_KEY_B                  MHKey::B
#define MH_KEY_C                  MHKey::C
#define MH_KEY_D                  MHKey::D
#define MH_KEY_E                  MHKey::E
#define MH_KEY_F                  MHKey::F
#define MH_KEY_G                  MHKey::G
#define MH_KEY_H                  MHKey::H
#define MH_KEY_I                  MHKey::I
#define MH_KEY_J                  MHKey::J
#define MH_KEY_K                  MHKey::K
#define MH_KEY_L                  MHKey::L
#define MH_KEY_M                  MHKey::M
#define MH_KEY_N                  MHKey::N
#define MH_KEY_O                  MHKey::O
#define MH_KEY_P                  MHKey::P
#define MH_KEY_Q                  MHKey::Q
#define MH_KEY_R                  MHKey::R
#define MH_KEY_S                  MHKey::S
#define MH_KEY_T                  MHKey::T
#define MH_KEY_U                  MHKey::U
#define MH_KEY_V                  MHKey::V
#define MH_KEY_W                  MHKey::W
#define MH_KEY_X                  MHKey::X
#define MH_KEY_Y                  MHKey::Y
#define MH_KEY_Z                  MHKey::Z
#define MH_KEY_LEFT_BRACKET       MHKey::LeftBracket   /* [ */
#define MH_KEY_BACKSLASH          MHKey::Backslash     /* \ */
#define MH_KEY_RIGHT_BRACKET      MHKey::RightBracket  /* ] */
#define MH_KEY_GRAVE_ACCENT       MHKey::GraveAccent   /* ` */
#define MH_KEY_WORLD_1            MHKey::World1  /* non-US #1 */
#define MH_KEY_WORLD_2            MHKey::World2 /* non-US #2 */

/* Function keys */
#define MH_KEY_ESCAPE             MHKey::Escape
#define MH_KEY_ENTER              MHKey::Enter
#define MH_KEY_TAB                MHKey::Tab
#define MH_KEY_BACKSPACE          MHKey::Backspace
#define MH_KEY_INSERT             MHKey::Insert
#define MH_KEY_DELETE             MHKey::Delete
#define MH_KEY_RIGHT              MHKey::Right
#define MH_KEY_LEFT               MHKey::Left
#define MH_KEY_DOWN               MHKey::Down
#define MH_KEY_UP                 MHKey::Up
#define MH_KEY_PAGE_UP            MHKey::PageUp
#define MH_KEY_PAGE_DOWN          MHKey::PageDown
#define MH_KEY_HOME               MHKey::Home
#define MH_KEY_END                MHKey::End
#define MH_KEY_CAPS_LOCK          MHKey::CapsLock
#define MH_KEY_SCROLL_LOCK        MHKey::ScrollLock
#define MH_KEY_NUM_LOCK           MHKey::NumLock
#define MH_KEY_PRINT_SCREEN       MHKey::PrintScreen
#define MH_KEY_PAUSE              MHKey::Pause
#define MH_KEY_F1                 MHKey::F1
#define MH_KEY_F2                 MHKey::F2
#define MH_KEY_F3                 MHKey::F3
#define MH_KEY_F4                 MHKey::F4
#define MH_KEY_F5                 MHKey::F5
#define MH_KEY_F6                 MHKey::F6
#define MH_KEY_F7                 MHKey::F7
#define MH_KEY_F8                 MHKey::F8
#define MH_KEY_F9                 MHKey::F9
#define MH_KEY_F10                MHKey::F10
#define MH_KEY_F11                MHKey::F11
#define MH_KEY_F12                MHKey::F12
#define MH_KEY_F13                MHKey::F13
#define MH_KEY_F14                MHKey::F14
#define MH_KEY_F15                MHKey::F15
#define MH_KEY_F16                MHKey::F16
#define MH_KEY_F17                MHKey::F17
#define MH_KEY_F18                MHKey::F18
#define MH_KEY_F19                MHKey::F19
#define MH_KEY_F20                MHKey::F20
#define MH_KEY_F21                MHKey::F21
#define MH_KEY_F22                MHKey::F22
#define MH_KEY_F23                MHKey::F23
#define MH_KEY_F24                MHKey::F24
#define MH_KEY_F25                MHKey::F25
#define MH_KEY_KP_0               MHKey::KP0
#define MH_KEY_KP_1               MHKey::KP1
#define MH_KEY_KP_2               MHKey::KP2
#define MH_KEY_KP_3               MHKey::KP3
#define MH_KEY_KP_4               MHKey::KP4
#define MH_KEY_KP_5               MHKey::KP5
#define MH_KEY_KP_6               MHKey::KP6
#define MH_KEY_KP_7               MHKey::KP7
#define MH_KEY_KP_8               MHKey::KP8
#define MH_KEY_KP_9               MHKey::KP9
#define MH_KEY_KP_DECIMAL         MHKey::KPDecimal
#define MH_KEY_KP_DIVIDE          MHKey::KPDivide
#define MH_KEY_KP_MULTIPLY        MHKey::KPMultiply
#define MH_KEY_KP_SUBTRACT        MHKey::KPSubtract
#define MH_KEY_KP_ADD             MHKey::KPAdd
#define MH_KEY_KP_ENTER           MHKey::KPEnter
#define MH_KEY_KP_EQUAL           MHKey::KPEqual
#define MH_KEY_LEFT_SHIFT         MHKey::LeftShift
#define MH_KEY_LEFT_CONTROL       MHKey::LeftControl
#define MH_KEY_LEFT_ALT           MHKey::LeftAlt
#define MH_KEY_LEFT_SUPER         MHKey::LeftSuper
#define MH_KEY_RIGHT_SHIFT        MHKey::RightShift
#define MH_KEY_RIGHT_CONTROL      MHKey::RightControl
#define MH_KEY_RIGHT_ALT          MHKey::RightAlt
#define MH_KEY_RIGHT_SUPER        MHKey::RightSuper
#define MH_KEY_MENU               MHKey::Menu
								  
#define MH_MOUSE_BUTTON_LEFT      0
#define MH_MOUSE_BUTTON_RIGHT     1
#define MH_MOUSE_BUTTON_MIDDLE    2