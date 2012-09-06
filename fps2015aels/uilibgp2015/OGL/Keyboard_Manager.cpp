#include "Keyboard_Manager.h"
#include "Keymap.h"
#include "Common.h"
#include <iostream>
#include <string.h>

#ifndef	__MAKE_H
#include <map>
#include <vector>
#endif

std::map<int, int>	test(void);
static std::map<int, int>	gl_keymap = test();

std::map<int, int>	test(void)
{
	std::map<int, int>	km;

	km[ID::KEY_UNKNOWN] = 0;
	km[ID::KEY_FIRST] = 0;
	km[ID::KEY_BACKSPACE] = 8;
	km[ID::KEY_TAB] = 9;
	km[ID::KEY_CLEAR] = 12;
	km[ID::KEY_RETURN] = 13;
	km[ID::KEY_PAUSE] = 19;
	km[ID::KEY_ESCAPE] = 27;
	km[ID::KEY_SPACE] = 32;
	km[ID::KEY_EXCLAIM] = 33;
	km[ID::KEY_QUOTEDBL] = 34;
	km[ID::KEY_HASH] = 35;
	km[ID::KEY_DOLLAR] = 36;
	km[ID::KEY_AMPERSAND] = 38;
	km[ID::KEY_QUOTE] = 39;
	km[ID::KEY_LEFTPAREN] = 40;
	km[ID::KEY_RIGHTPAREN] = 41;
	km[ID::KEY_ASTERISK] = 42;
	km[ID::KEY_PLUS] = 43;
	km[ID::KEY_COMMA] = 44;
	km[ID::KEY_MINUS] = 45;
	km[ID::KEY_PERIOD] = 46;
	km[ID::KEY_SLASH] = 47;
	km[ID::KEY_0] = 48;
	km[ID::KEY_1] = 49;
	km[ID::KEY_2] = 50;
	km[ID::KEY_3] = 51;
	km[ID::KEY_4] = 52;
	km[ID::KEY_5] = 53;
	km[ID::KEY_6] = 54;
	km[ID::KEY_7] = 55;
	km[ID::KEY_8] = 56;
	km[ID::KEY_9] = 57;
	km[ID::KEY_COLON] = 58;
	km[ID::KEY_SEMICOLON] = 59;
	km[ID::KEY_LESS] = 60;
	km[ID::KEY_EQUALS] = 61;
	km[ID::KEY_GREATER] = 62;
	km[ID::KEY_QUESTION] = 63;
	km[ID::KEY_AT] = 64;
	km[ID::KEY_LEFTBRACKET] = 91;
	km[ID::KEY_BACKSLASH] = 92;
	km[ID::KEY_RIGHTBRACKET] = 93;
	km[ID::KEY_CARET] = 94;
	km[ID::KEY_UNDERSCORE] = 95;
	km[ID::KEY_BACKQUOTE] = 96;
	km[ID::KEY_a] = 97;
	km[ID::KEY_b] = 98;
	km[ID::KEY_c] = 99;
	km[ID::KEY_d] = 100;
	km[ID::KEY_e] = 101;
	km[ID::KEY_f] = 102;
	km[ID::KEY_g] = 103;
	km[ID::KEY_h] = 104;
	km[ID::KEY_i] = 105;
	km[ID::KEY_j] = 106;
	km[ID::KEY_k] = 107;
	km[ID::KEY_l] = 108;
	km[ID::KEY_m] = 109;
	km[ID::KEY_n] = 110;
	km[ID::KEY_o] = 111;
	km[ID::KEY_p] = 112;
	km[ID::KEY_q] = 113;
	km[ID::KEY_r] = 114;
	km[ID::KEY_s] = 115;
	km[ID::KEY_t] = 116;
	km[ID::KEY_u] = 117;
	km[ID::KEY_v] = 118;
	km[ID::KEY_w] = 119;
	km[ID::KEY_x] = 120;
	km[ID::KEY_y] = 121;
	km[ID::KEY_z] = 122;
	km[ID::KEY_DELETE] = 127;
	km[ID::KEY_WORLD_0] = 160;
	km[ID::KEY_WORLD_1] = 161;
	km[ID::KEY_WORLD_2] = 162;
	km[ID::KEY_WORLD_3] = 163;
	km[ID::KEY_WORLD_4] = 164;
	km[ID::KEY_WORLD_5] = 165;
	km[ID::KEY_WORLD_6] = 166;
	km[ID::KEY_WORLD_7] = 167;
	km[ID::KEY_WORLD_8] = 168;
	km[ID::KEY_WORLD_9] = 169;
	km[ID::KEY_WORLD_10] = 170;
	km[ID::KEY_WORLD_11] = 171;
	km[ID::KEY_WORLD_12] = 172;
	km[ID::KEY_WORLD_13] = 173;
	km[ID::KEY_WORLD_14] = 174;
	km[ID::KEY_WORLD_15] = 175;
	km[ID::KEY_WORLD_16] = 176;
	km[ID::KEY_WORLD_17] = 177;
	km[ID::KEY_WORLD_18] = 178;
	km[ID::KEY_WORLD_19] = 179;
	km[ID::KEY_WORLD_20] = 180;
	km[ID::KEY_WORLD_21] = 181;
	km[ID::KEY_WORLD_22] = 182;
	km[ID::KEY_WORLD_23] = 183;
	km[ID::KEY_WORLD_24] = 184;
	km[ID::KEY_WORLD_25] = 185;
	km[ID::KEY_WORLD_26] = 186;
	km[ID::KEY_WORLD_27] = 187;
	km[ID::KEY_WORLD_28] = 188;
	km[ID::KEY_WORLD_29] = 189;
	km[ID::KEY_WORLD_30] = 190;
	km[ID::KEY_WORLD_31] = 191;
	km[ID::KEY_WORLD_32] = 192;
	km[ID::KEY_WORLD_33] = 193;
	km[ID::KEY_WORLD_34] = 194;
	km[ID::KEY_WORLD_35] = 195;
	km[ID::KEY_WORLD_36] = 196;
	km[ID::KEY_WORLD_37] = 197;
	km[ID::KEY_WORLD_38] = 198;
	km[ID::KEY_WORLD_39] = 199;
	km[ID::KEY_WORLD_40] = 200;
	km[ID::KEY_WORLD_41] = 201;
	km[ID::KEY_WORLD_42] = 202;
	km[ID::KEY_WORLD_43] = 203;
	km[ID::KEY_WORLD_44] = 204;
	km[ID::KEY_WORLD_45] = 205;
	km[ID::KEY_WORLD_46] = 206;
	km[ID::KEY_WORLD_47] = 207;
	km[ID::KEY_WORLD_48] = 208;
	km[ID::KEY_WORLD_49] = 209;
	km[ID::KEY_WORLD_50] = 210;
	km[ID::KEY_WORLD_51] = 211;
	km[ID::KEY_WORLD_52] = 212;
	km[ID::KEY_WORLD_53] = 213;
	km[ID::KEY_WORLD_54] = 214;
	km[ID::KEY_WORLD_55] = 215;
	km[ID::KEY_WORLD_56] = 216;
	km[ID::KEY_WORLD_57] = 217;
	km[ID::KEY_WORLD_58] = 218;
	km[ID::KEY_WORLD_59] = 219;
	km[ID::KEY_WORLD_60] = 220;
	km[ID::KEY_WORLD_61] = 221;
	km[ID::KEY_WORLD_62] = 222;
	km[ID::KEY_WORLD_63] = 223;
	km[ID::KEY_WORLD_64] = 224;
	km[ID::KEY_WORLD_65] = 225;
	km[ID::KEY_WORLD_66] = 226;
	km[ID::KEY_WORLD_67] = 227;
	km[ID::KEY_WORLD_68] = 228;
	km[ID::KEY_WORLD_69] = 229;
	km[ID::KEY_WORLD_70] = 230;
	km[ID::KEY_WORLD_71] = 231;
	km[ID::KEY_WORLD_72] = 232;
	km[ID::KEY_WORLD_73] = 233;
	km[ID::KEY_WORLD_74] = 234;
	km[ID::KEY_WORLD_75] = 235;
	km[ID::KEY_WORLD_76] = 236;
	km[ID::KEY_WORLD_77] = 237;
	km[ID::KEY_WORLD_78] = 238;
	km[ID::KEY_WORLD_79] = 239;
	km[ID::KEY_WORLD_80] = 240;
	km[ID::KEY_WORLD_81] = 241;
	km[ID::KEY_WORLD_82] = 242;
	km[ID::KEY_WORLD_83] = 243;
	km[ID::KEY_WORLD_84] = 244;
	km[ID::KEY_WORLD_85] = 245;
	km[ID::KEY_WORLD_86] = 246;
	km[ID::KEY_WORLD_87] = 247;
	km[ID::KEY_WORLD_88] = 248;
	km[ID::KEY_WORLD_89] = 249;
	km[ID::KEY_WORLD_90] = 250;
	km[ID::KEY_WORLD_91] = 251;
	km[ID::KEY_WORLD_92] = 252;
	km[ID::KEY_WORLD_93] = 253;
	km[ID::KEY_WORLD_94] = 254;
	km[ID::KEY_WORLD_95] = 255;
	km[ID::KEY_KP0] = 48;
	km[ID::KEY_KP1] = 49;
	km[ID::KEY_KP2] = 50;
	km[ID::KEY_KP3] = 51;
	km[ID::KEY_KP4] = 52;
	km[ID::KEY_KP5] = 53;
	km[ID::KEY_KP6] = 54;
	km[ID::KEY_KP7] = 55;
	km[ID::KEY_KP8] = 56;
	km[ID::KEY_KP9] = 57;
	km[ID::KEY_KP_PERIOD] = 46;
	km[ID::KEY_KP_DIVIDE] = 47;
	km[ID::KEY_KP_MULTIPLY] = 42;
	km[ID::KEY_KP_MINUS] = 45;
	km[ID::KEY_KP_PLUS] = 43;
	km[ID::KEY_KP_ENTER] = 61;
	km[ID::KEY_KP_EQUALS] = 272;
	km[ID::KEY_UP] = 273;
	km[ID::KEY_DOWN] = 274;
	km[ID::KEY_RIGHT] = 275;
	km[ID::KEY_LEFT] = 276;
	km[ID::KEY_INSERT] = 277;
	km[ID::KEY_HOME] = 278;
	km[ID::KEY_END] = 279;
	km[ID::KEY_PAGEUP] = 280;
	km[ID::KEY_PAGEDOWN] = 281;
	km[ID::KEY_F1] = 282;
	km[ID::KEY_F2] = 283;
	km[ID::KEY_F3] = 284;
	km[ID::KEY_F4] = 285;
	km[ID::KEY_F5] = 286;
	km[ID::KEY_F6] = 287;
	km[ID::KEY_F7] = 288;
	km[ID::KEY_F8] = 289;
	km[ID::KEY_F9] = 290;
	km[ID::KEY_F10] = 291;
	km[ID::KEY_F11] = 292;
	km[ID::KEY_F12] = 293;
	km[ID::KEY_F13] = 294;
	km[ID::KEY_F14] = 295;
	km[ID::KEY_F15] = 296;
	km[ID::KEY_NUMLOCK] = 300;
	km[ID::KEY_CAPSLOCK] = 301;
	km[ID::KEY_SCROLLOCK] = 302;
	km[ID::KEY_RSHIFT] = 303;
	km[ID::KEY_LSHIFT] = 304;
	km[ID::KEY_RCTRL] = 305;
	km[ID::KEY_LCTRL] = 306;
	km[ID::KEY_RALT] = 307;
	km[ID::KEY_LALT] = 308;
	km[ID::KEY_RMETA] = 309;
	km[ID::KEY_LMETA] = 310;
	km[ID::KEY_LSUPER] = 311;
	km[ID::KEY_RSUPER] = 312;
	km[ID::KEY_MODE] = 313;
	km[ID::KEY_COMPOSE] = 314;
	km[ID::KEY_HELP] = 315;
	km[ID::KEY_PRINT] = 316;
	km[ID::KEY_SYSREQ] = 317;
	km[ID::KEY_BREAK] = 318;
	km[ID::KEY_MENU] = 319;
	km[ID::KEY_POWER] = 320;
	km[ID::KEY_EURO] = 321;
	km[ID::KEY_UNDO] = 322;
	return km;
}

void	ID::Keyboard_Manager::Write(char* str, ID::Mod mod,
				    ID::Key sym, unsigned int maxLength)
{
	unsigned int	l;

	l = strlen(str);
	PRINT_DBG("S=" << (int)sym << "-M=" << (int)mod << "\n")
	if ((sym == ID::KEY_RETURN || sym == ID::KEY_KP_ENTER) && l < maxLength)
	{
		str[l] = '\n';
		str[l + 1] = 0;
	}
	sym = (ID::Key)gl_keymap[sym];
	if (sym >= 32 && sym <= 126 && l < maxLength)
	{
		if (sym >= 97 && sym <= 122)
		{
			if ((mod & KEYMOD_SHIFT && !(mod & KEYMOD_CAPS)) ||
			    (!(mod & KEYMOD_SHIFT) && mod & KEYMOD_CAPS))
				sym = (ID::Key)(sym - 32);
		}
		str[l] = sym;
		str[l + 1] = 0;
		PRINT_DBG(str);
	}
	else if (sym == 8)
	{
		if (l > 1)
			str[l - 1] = 0;
		else if (l == 1)
			str[0] = 0;
	}
}

ID::Keyboard_Manager::Keyboard_Manager()
{
}

ID::Keyboard_Manager::~Keyboard_Manager()
{
}

