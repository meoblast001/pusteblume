/**
 * Copyright (C) 2017 Braden Walters
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Sternenhimmel.hpp"
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
  Sternenhimmel window;
  window.show();

  return app.exec();
}
