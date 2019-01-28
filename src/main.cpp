#include <cstring>
#include <iostream>

#if defined(_WIN64)
#include <locale>
#include <fstream>

#endif

#include "Game.hpp"
#include "utils/ANSIColors.hpp"

void help();
void version();

int new_save(const char *save);
int load_save(const char *save);

int main(int argc, char *argv[]) {
	#if defined(_WIN64)
		ansi::initializeANSIColors();
	#endif
	if (argc == 1) {
		Game game;
		game.run();
	} else if (argc == 2) {
        if (std::strncmp(argv[1], "--", 2) == 0) {
            if (std::strcmp(argv[1] + 2, "help") == 0)
                help();
            else if (std::strcmp(argv[1] + 2, "version") == 0)
				version();
            else if (std::strncmp(argv[1] + 2, "new_save", 8) == 0) {
                if (*(argv[1] + 10) == '=')
	                return new_save(argv[1] + 11);
	            return new_save("untitled");
            } else if (std::strncmp(argv[1] + 2, "load_save", 9) == 0)
	            return load_save(argv[1] + 12);
            else
            	std::cout << "Unknown option." << std::endl;
        }
    } else {
		std::cout << "Too many args. Aborting." << std::endl;
		return -1;
	}
    return 0;
}

void help() {
	std::cout << ansi::color("ageofwar 0.1", ansi::strong_black_foreground) << " (" << ansi::color("amd64", ansi::strong_black_background) << ")" << std::endl
		<< "Usage: ageofwar [OPTION]" << std::endl
		<< "ageofwar, try to survive and destroy the ennemy base." << std::endl << std::endl

		<< "  --new_save[=FILE]  creates a new game on save FILE, if FILE is not defined 'saves/untitled' is used." << std::endl
		<< "  --load_save=FILE   load a save FILE." << std::endl
		<< "      --help     display this help and exit" << std::endl
		<< "      --version  output version information and exit" << std::endl;
}

void version() {
	std::cout << "ageofwar (lcsdavid loirirs) 1.0" << std::endl
		<< "Copyright (C) 2019 Free Lucas' Software Foundation, Inc." << std::endl
		<< "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>." << std::endl
		<< "This is free software: you are free to change and redistribute it." << std::endl
		<< "There is NO WARRANTY, to the extent permitted by law." << std::endl << std::endl

		<< "Written by Lucas V. David.";
}

int new_save(const char *save) {
	std::string s = save;
	s += + ".sav";
	std::ifstream ifs(s);
	if (ifs.is_open()) {
		std::cout << "Save already exists. Override Y/n" << std::endl;
		if (std::cin.get() == 'n') {
			std::cout << "Exiting...";
			return 0;
		}
		ifs.close();
	}
	std::ofstream ofs(s, std::ios_base::trunc);
	ofs.close();
	std::cout << "Creating game " << ansi::color(save, ansi::normal_green_foreground) << '.' << std::endl;
	Game game(save);
	game.run();
	return 0;
}

int load_save(const char *save) {
	std::string s = save;
	s += + ".sav";
	std::ifstream ifs(s);
	if (!ifs.is_open() || ifs.eof()) {
		std::cerr << "Invalid save name. Aborting." << std::endl;
		return -1;
	}
	std::cout << "Loading game " << ansi::color(save, ansi::normal_green_foreground) << '.' << std::endl;
	Game game(save);
	game.run();
	return 0;
}
