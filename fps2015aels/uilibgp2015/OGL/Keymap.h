#ifndef __ID_KEYMAP_H__
#define __ID_KEYMAP_H__

namespace	ID
{
	typedef enum
	{
		/** @name ASCII mapped keysyms
		 *  The keyboard syms have been cleverly chosen to map to ASCII
		 */
		/*@{*/
		KEY_UNKNOWN		= 0,
		KEY_FIRST		= 0,
		KEY_BACKSPACE		= 8,
		KEY_TAB			= 9,
		KEY_CLEAR		= 12,
		KEY_RETURN		= 13,
		KEY_PAUSE		= 19,
		KEY_ESCAPE		= 27,
		KEY_SPACE		= 32,
		KEY_EXCLAIM		= 33,
		KEY_QUOTEDBL		= 34,
		KEY_HASH		= 35,
		KEY_DOLLAR		= 36,
		KEY_AMPERSAND		= 38,
		KEY_QUOTE		= 39,
		KEY_LEFTPAREN		= 40,
		KEY_RIGHTPAREN		= 41,
		KEY_ASTERISK		= 42,
		KEY_PLUS		= 43,
		KEY_COMMA		= 44,
		KEY_MINUS		= 45,
		KEY_PERIOD		= 46,
		KEY_SLASH		= 47,
		KEY_0			= 48,
		KEY_1			= 49,
		KEY_2			= 50,
		KEY_3			= 51,
		KEY_4			= 52,
		KEY_5			= 53,
		KEY_6			= 54,
		KEY_7			= 55,
		KEY_8			= 56,
		KEY_9			= 57,
		KEY_COLON		= 58,
		KEY_SEMICOLON		= 59,
		KEY_LESS		= 60,
		KEY_EQUALS		= 61,
		KEY_GREATER		= 62,
		KEY_QUESTION		= 63,
		KEY_AT			= 64,
		KEY_LEFTBRACKET		= 91,
		KEY_BACKSLASH		= 92,
		KEY_RIGHTBRACKET	= 93,
		KEY_CARET		= 94,
		KEY_UNDERSCORE		= 95,
		KEY_BACKQUOTE		= 96,
		KEY_a			= 97,
		KEY_b			= 98,
		KEY_c			= 99,
		KEY_d			= 100,
		KEY_e			= 101,
		KEY_f			= 102,
		KEY_g			= 103,
		KEY_h			= 104,
		KEY_i			= 105,
		KEY_j			= 106,
		KEY_k			= 107,
		KEY_l			= 108,
		KEY_m			= 109,
		KEY_n			= 110,
		KEY_o			= 111,
		KEY_p			= 112,
		KEY_q			= 113,
		KEY_r			= 114,
		KEY_s			= 115,
		KEY_t			= 116,
		KEY_u			= 117,
		KEY_v			= 118,
		KEY_w			= 119,
		KEY_x			= 120,
		KEY_y			= 121,
		KEY_z			= 122,
		KEY_DELETE		= 127,
		/* End of ASCII mapped keysyms */
		/*@}*/

		/** @name International keyboard syms */
		/*@{*/
		KEY_WORLD_0		= 160,		/* 0xA0 */
		KEY_WORLD_1		= 161,
		KEY_WORLD_2		= 162,
		KEY_WORLD_3		= 163,
		KEY_WORLD_4		= 164,
		KEY_WORLD_5		= 165,
		KEY_WORLD_6		= 166,
		KEY_WORLD_7		= 167,
		KEY_WORLD_8		= 168,
		KEY_WORLD_9		= 169,
		KEY_WORLD_10		= 170,
		KEY_WORLD_11		= 171,
		KEY_WORLD_12		= 172,
		KEY_WORLD_13		= 173,
		KEY_WORLD_14		= 174,
		KEY_WORLD_15		= 175,
		KEY_WORLD_16		= 176,
		KEY_WORLD_17		= 177,
		KEY_WORLD_18		= 178,
		KEY_WORLD_19		= 179,
		KEY_WORLD_20		= 180,
		KEY_WORLD_21		= 181,
		KEY_WORLD_22		= 182,
		KEY_WORLD_23		= 183,
		KEY_WORLD_24		= 184,
		KEY_WORLD_25		= 185,
		KEY_WORLD_26		= 186,
		KEY_WORLD_27		= 187,
		KEY_WORLD_28		= 188,
		KEY_WORLD_29		= 189,
		KEY_WORLD_30		= 190,
		KEY_WORLD_31		= 191,
		KEY_WORLD_32		= 192,
		KEY_WORLD_33		= 193,
		KEY_WORLD_34		= 194,
		KEY_WORLD_35		= 195,
		KEY_WORLD_36		= 196,
		KEY_WORLD_37		= 197,
		KEY_WORLD_38		= 198,
		KEY_WORLD_39		= 199,
		KEY_WORLD_40		= 200,
		KEY_WORLD_41		= 201,
		KEY_WORLD_42		= 202,
		KEY_WORLD_43		= 203,
		KEY_WORLD_44		= 204,
		KEY_WORLD_45		= 205,
		KEY_WORLD_46		= 206,
		KEY_WORLD_47		= 207,
		KEY_WORLD_48		= 208,
		KEY_WORLD_49		= 209,
		KEY_WORLD_50		= 210,
		KEY_WORLD_51		= 211,
		KEY_WORLD_52		= 212,
		KEY_WORLD_53		= 213,
		KEY_WORLD_54		= 214,
		KEY_WORLD_55		= 215,
		KEY_WORLD_56		= 216,
		KEY_WORLD_57		= 217,
		KEY_WORLD_58		= 218,
		KEY_WORLD_59		= 219,
		KEY_WORLD_60		= 220,
		KEY_WORLD_61		= 221,
		KEY_WORLD_62		= 222,
		KEY_WORLD_63		= 223,
		KEY_WORLD_64		= 224,
		KEY_WORLD_65		= 225,
		KEY_WORLD_66		= 226,
		KEY_WORLD_67		= 227,
		KEY_WORLD_68		= 228,
		KEY_WORLD_69		= 229,
		KEY_WORLD_70		= 230,
		KEY_WORLD_71		= 231,
		KEY_WORLD_72		= 232,
		KEY_WORLD_73		= 233,
		KEY_WORLD_74		= 234,
		KEY_WORLD_75		= 235,
		KEY_WORLD_76		= 236,
		KEY_WORLD_77		= 237,
		KEY_WORLD_78		= 238,
		KEY_WORLD_79		= 239,
		KEY_WORLD_80		= 240,
		KEY_WORLD_81		= 241,
		KEY_WORLD_82		= 242,
		KEY_WORLD_83		= 243,
		KEY_WORLD_84		= 244,
		KEY_WORLD_85		= 245,
		KEY_WORLD_86		= 246,
		KEY_WORLD_87		= 247,
		KEY_WORLD_88		= 248,
		KEY_WORLD_89		= 249,
		KEY_WORLD_90		= 250,
		KEY_WORLD_91		= 251,
		KEY_WORLD_92		= 252,
		KEY_WORLD_93		= 253,
		KEY_WORLD_94		= 254,
		KEY_WORLD_95		= 255,		/* 0xFF */
		/*@}*/

		/** @name Numeric keypad */
		/*@{*/
		KEY_KP0			= 256,
		KEY_KP1			= 257,
		KEY_KP2			= 258,
		KEY_KP3			= 259,
		KEY_KP4			= 260,
		KEY_KP5			= 261,
		KEY_KP6			= 262,
		KEY_KP7			= 263,
		KEY_KP8			= 264,
		KEY_KP9			= 265,
		KEY_KP_PERIOD		= 266,
		KEY_KP_DIVIDE		= 267,
		KEY_KP_MULTIPLY		= 268,
		KEY_KP_MINUS		= 269,
		KEY_KP_PLUS		= 270,
		KEY_KP_ENTER		= 271,
		KEY_KP_EQUALS		= 272,
		/*@}*/

		/** @name Arrows + Home/End pad */
		/*@{*/
		KEY_UP			= 273,
		KEY_DOWN		= 274,
		KEY_RIGHT		= 275,
		KEY_LEFT		= 276,
		KEY_INSERT		= 277,
		KEY_HOME		= 278,
		KEY_END			= 279,
		KEY_PAGEUP		= 280,
		KEY_PAGEDOWN		= 281,
		/*@}*/

		/** @name Function keys */
		/*@{*/
		KEY_F1			= 282,
		KEY_F2			= 283,
		KEY_F3			= 284,
		KEY_F4			= 285,
		KEY_F5			= 286,
		KEY_F6			= 287,
		KEY_F7			= 288,
		KEY_F8			= 289,
		KEY_F9			= 290,
		KEY_F10			= 291,
		KEY_F11			= 292,
		KEY_F12			= 293,
		KEY_F13			= 294,
		KEY_F14			= 295,
		KEY_F15			= 296,
		/*@}*/

		/** @name Key state modifier keys */
		/*@{*/
		KEY_NUMLOCK		= 300,
		KEY_CAPSLOCK		= 301,
		KEY_SCROLLOCK		= 302,
		KEY_RSHIFT		= 303,
		KEY_LSHIFT		= 304,
		KEY_RCTRL		= 305,
		KEY_LCTRL		= 306,
		KEY_RALT		= 307,
		KEY_LALT		= 308,
		KEY_RMETA		= 309,
		KEY_LMETA		= 310,
		KEY_LSUPER		= 311,		/**< Left "Windows" key */
		KEY_RSUPER		= 312,		/**< Right "Windows" key */
		KEY_MODE		= 313,		/**< "Alt Gr" key */
		KEY_COMPOSE		= 314,		/**< Multi-key compose key */
		/*@}*/

		/** @name Miscellaneous function keys */
		/*@{*/
		KEY_HELP		= 315,
		KEY_PRINT		= 316,
		KEY_SYSREQ		= 317,
		KEY_BREAK		= 318,
		KEY_MENU		= 319,
		KEY_POWER		= 320,		/**< Power Macintosh power key */
		KEY_EURO		= 321,		/**< Some european keyboards */
		KEY_UNDO		= 322,		/**< Atari keyboard has Undo */
		/*@}*/
	}	Key;

	typedef enum
	{
		KEYMOD_NONE  = 0x0000,
		KEYMOD_LSHIFT= 0x0001,
		KEYMOD_RSHIFT= 0x0002,
		KEYMOD_LCTRL = 0x0040,
		KEYMOD_RCTRL = 0x0080,
		KEYMOD_LALT  = 0x0100,
		KEYMOD_RALT  = 0x0200,
		KEYMOD_LMETA = 0x0400,
		KEYMOD_RMETA = 0x0800,
		KEYMOD_NUM   = 0x1000,
		KEYMOD_CAPS  = 0x2000,
		KEYMOD_MODE  = 0x4000,
		KEYMOD_RESERVED = 0x8000
	}	Mod;

	typedef enum
	{
		BUTTON_NONE = 0,
		BUTTON_LEFT,
		BUTTON_MID,
		BUTTON_RIGHT
	}	Mouse_Button;

	#define KEYMOD_CTRL	(KEYMOD_LCTRL | KEYMOD_RCTRL)
	#define KEYMOD_SHIFT	(KEYMOD_LSHIFT | KEYMOD_RSHIFT)
	#define KEYMOD_ALT	(KEYMOD_LALT | KEYMOD_RALT)
	#define KEYMOD_META	(KEYMOD_LMETA | KEYMOD_RMETA)

};

#endif
