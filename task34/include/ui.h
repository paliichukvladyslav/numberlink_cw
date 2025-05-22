/* ui.h */
#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>

#define TEMP_FNAME "/tmp/numberlink.txt"

class TextUI {
	private:
		bool file_exists(std::string &filename);
	public:

		void show_main_menu();

		int ask_choice(int min, int max);
		int ask_grid_size();
		std::string ask_filename();
		bool ask_editor();

		void print(const std::string &msg);
};

#endif
