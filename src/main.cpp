/**
 * Copyright (C) 2017 Braden Walters
 * This file is licensed under the MIT Expat License. See LICENSE.txt.
 */

#include "Pusteblume.hpp"
#include <QApplication>

/**
 * Main program procedure.
 *
 * @param argc Amount of arguments.
 * @param argv Arguments
 * @return Program status code.
 */
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Pusteblume window;
  window.show();

  return app.exec();
}
