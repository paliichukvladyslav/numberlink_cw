/* ui.cc */
#include <iostream>
#include <limits>
#include "ui.h"

void TextUI::show_main_menu() {
  std::cout << "\n=== Numberlink ===\n";
  std::cout << "1. Ввести з файлу\n";
  std::cout << "2. Згенерувати випадково\n";
  std::cout << "3. Вийти\n";
  std::cout << "Ваш вибір: ";
}

int TextUI::ask_choice() {
  int choice;
  std::cin >> choice;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return choice;
}

int TextUI::ask_gridsize()  {
  std::cout << "Введіть розмір поля (n): ";
  int n;
  std::cin >> n;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return n;
}

std::string TextUI::ask_filename() {
  std::cout << "Введіть назву файлу: ";
  std::string fname;
  std::getline(std::cin, fname);
  return fname;
}

void TextUI::print(std::string &msg) {
  std::cout << msg << "\n";
}
