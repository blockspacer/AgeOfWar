#ifndef AGEOFWAR_TEXTCOLOR_HPP
#define AGEOFWAR_TEXTCOLOR_HPP

#include <string>

namespace ansi {
#ifdef _WIN64
	void initializeANSIColors();
#endif

	enum colors : std::int_least16_t {
		/* STYLES */
		reset = 0x0001, /* priority */
		bold = 0x0002, underline = 0x0004, inverse = 0x0008,
		/* NORMAL FOREGROUND COLORS */
		normal_black_foreground = 0x0010, normal_red_foreground = 0x0050,
		normal_green_foreground = 0x0090, normal_yellow_foreground = 0x00D0,
		normal_blue_foreground = 0x0110, normal_magenta_foreground = 0x0150,
		normal_cyan_foreground = 0x0190, normal_white_foreground = 0x01D0,
		/* STRONG FOREGROUND COLORS */
		strong_black_foreground = 0x0030, strong_red_foreground = 0x0070,
		strong_green_foreground = 0x00B0, strong_yellow_foreground = 0x00F0,
		strong_blue_foreground = 0x0130, strong_magenta_foreground = 0x0170,
		strong_cyan_foreground = 0x01B0, strong_white_foreground = 0x01F0,
		/* NORMAL BACKGROUND COLORS */
		normal_black_background = 0x0200, normal_red_background = 0x0A00,
		normal_green_background = 0x1200, normal_yellow_background = 0x1A00,
		normal_blue_background = 0x2200, normal_magenta_background = 0x2A00,
		normal_cyan_background = 0x3200, normal_white_background = 0x3A00,
		/* STRONG BACKGROUND COLORS */
		strong_black_background = 0x0600, strong_red_background = 0x0E00,
		strong_green_background = 0x1600, strong_yellow_background = 0x1E00,
		strong_blue_background = 0x2600, strong_magenta_background = 0x2E00,
		strong_cyan_background = 0x3600, strong_white_background = 0x3E00,
	};


	std::string color(const char* s, colors colors);
	std::string color(std::string s, colors colors);
}

#endif
