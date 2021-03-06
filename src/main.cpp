#include <cstring>
#include <iostream>
#include <fstream>

#include "Game.hpp"
#include "utils/ANSIColors.hpp"

void help();
void version();

int new_save(const char *save, bool AI);
int load_save(const char *save, bool AI);

int main(int argc, char *argv[]) {
	#if defined(_WIN64)
		ansi::initializeANSIColors();
	#endif
	bool game = false, noSave = true, newOrLoad = false, AI = false;
	if (argc >= 2) {
		for (int i = 1; i < argc; i++) {
			if (argv[i][0] == '-') {
				if (argv[i][1] == '-') {
					if (std::strcmp(&argv[i][2], "help") == 0)
						help();
					else if (std::strcmp(&argv[i][2], "version") == 0)
						version();
					else if (std::strncmp(&argv[i][2], "new_save", 8) == 0)
						game = !(noSave = newOrLoad = false);
					else if (std::strncmp(argv[1] + 2, "load_save", 9) == 0)
						game = !(noSave = !(newOrLoad = true));
					else {
						std::cout << "Unknown option. Abort." << std::endl;
						return -1;
					}
				} else if (std::strcmp(&argv[1][1], "ai") == 0)
					AI = true;
				else {
					std::cout << "Unknown option. Abort." << std::endl;
					return -1;
				}
			}
		}
    }
	if (game) {
		if (noSave) {
			Game game(AI);
			game.run();
			return 0;
		}
		if (!newOrLoad) {
			if (*(argv[1] + 10) == '=')
				return new_save(&argv[1][12], AI);
			return new_save("untitled", AI);
		} else
			return load_save(argv[1] + 12, AI);
	}
}

void help() {
	std::cout << ansi::color("ageofwar 0.1", ansi::strong_black_foreground) << " (" << ansi::color("amd64", ansi::strong_black_background) << ")" << std::endl
		<< "Usage: ageofwar [OPTION]" << std::endl
		<< "ageofwar, try to survive and destroy the ennemy base." << std::endl << std::endl

		<< "  -ai                fight against AI." << std::endl
		<< "  --new_save[=TITLE]  creates a new game on save TITLE, if TITLE is not defined 'saves/untitled' is used." << std::endl
		<< "  --load_save=TITLE   load a save TITLE." << std::endl
		<< "      --help     display this help and exit" << std::endl
		<< "      --version  output version information and exit" << std::endl;
}

void version() {
	std::cout << "ageofwar (lcsdavid loisirs) 1.0" << std::endl
		<< "Copyright (C) 2019 Free Lucas' Software Foundation, Inc." << std::endl
		<< "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>." << std::endl
		<< "This is free software: you are free to change and redistribute it." << std::endl
		<< "There is NO WARRANTY, to the extent permitted by law." << std::endl << std::endl

		<< "Written by Lucas V. David." << std::endl;
}

int new_save(const char *save, bool AI) {
	std::string s = "saves/";
	s += save;
	s += + ".sav";
	std::ifstream ifs(s);
	if (ifs.is_open()) {
		ifs.peek();
		if (ifs.eof()) {
			std::cout << "Save already exists. Override Y/n" << std::endl;
			if (std::cin.get() == 'n') {
				std::cout << "Exiting...";
				return 0;
			}
		}
		ifs.close();
	}
	std::ofstream ofs(s, std::ios_base::trunc);
	if (!ofs.is_open()) {
		std::cout << "Cannot create save file..." << std::endl;
		return -1;
	}
	ofs.close();
	std::cout << "Creating game " << ansi::color(save, ansi::normal_green_foreground) << '.' << std::endl;
	Game game(save, AI);
	game.run();
	return 0;
}

int load_save(const char *save, bool AI) {
	std::string s = "saves/";
	s += save;
	s += + ".sav";
	std::ifstream ifs(s);
	if (!ifs.is_open() || ifs.eof()) {
		std::cerr << "Invalid save name. Aborting." << std::endl;
		return -1;
	}
	std::cout << "Loading game " << ansi::color(save, ansi::normal_green_foreground) << '.' << std::endl;
	Game game(save, AI);
	game.run();
	return 0;
}
