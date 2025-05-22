#ifndef APP_H
#define APP_H

#include "common.h"

class App {
private:

  Grid *grid;
  Solver *solver;
  TextUI *ui;

  void import_from_file();
  void import_from_editor();
  void randomize();

  void run_solver();

public:
  App();
  ~App();
  void run();

};

#endif
