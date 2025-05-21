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
  void show_secondary_menu();

  int ask_choice(int min, int max);
  int ask_gridsize();
  std::string ask_filename();
  bool ask_editor();

  void print(std::string &msg);
};

#endif
