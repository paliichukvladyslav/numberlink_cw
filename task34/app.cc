#include <iostream>
#include <fstream>
#include <limits>
#include "app.h"

App::App()
  : grid(NULL),
    solver(NULL),
    ui(NULL)
{}

App::~App() {
  if (grid) delete grid;
  if (solver) delete solver;
  if (ui) delete ui;
}

void App::run() {

  ui = new TextUI();

  while (true) {
    ui->show_main_menu();
    int choice = ui->ask_choice(1, 4);
    if (choice == 1) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      import_from_file();
    }
    else if (choice == 2) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      import_from_editor();
    }
    else if (choice == 3) {
      randomize();
    }
    else if (choice == 4) {
      ui->print("Вихід з програми...");
      break;
    }
    else {
      ui->print("Некоректний вибір");
    }
  }


}
void App::import_from_file() {
  std::string filename = ui->ask_filename();
  Grid *new_grid = new Grid(0);
  if (!new_grid->load_from_file(filename)) {
    ui->print("Помилка при зчитуванні файлу");
    delete new_grid;
    return;
  }
 
  if (grid) delete grid;
  grid = new_grid;

  run_solver();
}

void App::import_from_editor() {

  std::ofstream out(TEMP_FNAME);

  /* підготовимо пусту сітку в тимчасовому файлі*/
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      out << ".";
    }
    out << "\n";
  }

  out.close();

  if (!ui->ask_editor()) {
    ui->print("Редактор не відкрився. Перевірте свою змінну середовища $EDITOR.");
    return;
  }

  Grid *new_grid = new Grid(0);
  std::string file_to_open = TEMP_FNAME;
  if (!new_grid->load_from_file(file_to_open)) {
    ui->print("Помилка при зчитуванні файлу");
    delete new_grid;
    return;
  }

}

void App::randomize() {

	int size = ui->ask_grid_size();
	if (size < 2) {
		ui->print("Розмір має бути >= 2");
		return;
	}

	Grid *new_grid = new Grid(size);
	new_grid->random_fill(size / 2);

	if (grid) delete grid;
	grid = new_grid;

  run_solver();

}

void App::run_solver() {
  if (!grid) return;

  Solver *new_solver = new Solver(grid);
  bool success = new_solver->solve();

  if (solver) delete solver;
  solver = new_solver;


  if (success) {
    ui->print("Рішення знайдено.");
    grid->display_grid();
  } else {
    ui->print("Рішення не знайдено.");
    grid->display_grid();
  }


}

