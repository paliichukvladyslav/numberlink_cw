/* ui.h */
#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>

class TextUI {
public:
  void show_main_menu();
  int ask_choice();
  int ask_gridsize();
  std::string ask_filename();
  void print(std::string &msg);
};

#endif
