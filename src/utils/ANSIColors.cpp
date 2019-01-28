#include "ANSIColors.hpp"

#include <iostream>

#ifdef _WIN64

#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

inline HANDLE getConsoleHandle(const std::streambuf* osbuf) noexcept {
	if (osbuf == std::cout.rdbuf()) {
		static const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		return hStdout;
	} else if (osbuf == std::cerr.rdbuf() || osbuf == std::clog.rdbuf()) {
		static const HANDLE hStderr = GetStdHandle(STD_ERROR_HANDLE);
		return hStderr;
	}
	return INVALID_HANDLE_VALUE;
}

inline bool setWinTermAnsiColors(const std::streambuf* osbuf) noexcept {
	HANDLE h = getConsoleHandle(osbuf);
	if (h == INVALID_HANDLE_VALUE)
		return false;
	DWORD dwMode = 0;
	if (!GetConsoleMode(h, &dwMode))
		return false;
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	return SetConsoleMode(h, dwMode) != 0;
}

void ansi::initializeANSIColors() {
	setWinTermAnsiColors(std::cout.rdbuf());
	setWinTermAnsiColors(std::clog.rdbuf());
	setWinTermAnsiColors(std::cerr.rdbuf());
}
#endif

std::string ansi::color(std::string s, ansi::colors colors) {
	if (colors & 0x0001) /* reset */
		return s = "\x1B[0m" + s;
	bool semicolon = false;
	if (colors & 0x0002) { /* bold */
		s = "1m" + s;
		semicolon = true;
	}
	if (colors & 0x0004) { /* underline */
		s = "4m" + s;
		if (semicolon)
			s = ';' + s;
		semicolon = true;
	}
	if (colors & 0x0008) { /* inverse */
		s = "7m" + s;
		if (semicolon)
			s = ';' + s;
		semicolon = true;
	}
	if (colors & 0x0010) { /* foreground color */
		if (semicolon)
			s = ';' + s;
		s = (colors & 0x0030 ? '9' : '3') + std::to_string(colors >> 6 & 0x0007) + 'm' + s;
	}
	if (colors & 0x0200) { /* background color */
		if (semicolon)
			s = ';' + s;
		s = (colors & 0x0600 ? "10" : "4") + std::to_string(colors >> 11 & 0x0007) + 'm' + s;
	}
	return s = "\033[" + s + "\033[0m";
}

std::string ansi::color(const char* s, ansi::colors colors) {
	std::string str = s;
	return color(str, colors);
}