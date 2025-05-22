/* ui.cc */
#include <iostream>
#include <limits>
#include <fstream>
#include <cstdlib>
#include "ui.h"

void TextUI::show_main_menu() {
	std::cout << "\n=== Numberlink ===\n";
	std::cout << "1. Ввести з файлу\n";
	std::cout << "2. Ввести вручну\n";
	std::cout << "3. Згенерувати випадково\n";
	std::cout << "4. Вийти\n";
	std::cout << "Ваш вибір: ";
}

int TextUI::ask_choice(int min, int max) {
	while(true) {
		int choice;
		std::cin >> choice;
		if (std::cin.fail() || choice < min || choice > max) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Вибір виходить за межі\n";
			continue;
		}
		return choice;
	}
}

bool TextUI::file_exists(std::string &filename) {
	std::ifstream f(filename.c_str());
	return f.good();
}

std::string TextUI::ask_filename() {
	std::cout << "Введіть назву файлу: ";
	std::string fname;
	std::getline(std::cin, fname);
	if (file_exists(fname)) {
		return fname;
	} else {
		std::cerr << "Файл не існує";
		throw "invalid file\n";
	}
}

int TextUI::ask_grid_size()  {
	std::cout << "Введіть розмір сітки (n): ";
	int n;
	std::cin >> n;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return n;
}


bool TextUI::ask_editor() {
	char *editor = std::getenv("EDITOR");
	if (!editor) editor = (char *)"nano";

	std::string command = std::string(editor) + " " + TEMP_FNAME;
	int status = std::system(command.c_str());

	return status == 0;
}

void TextUI::print(const std::string &msg) {
	std::cout << msg << "\n";
}
