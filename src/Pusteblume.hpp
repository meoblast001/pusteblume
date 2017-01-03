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

#ifndef PUSTEBLUME_HPP
#define PUSTEBLUME_HPP

#include <list>
#include <QMainWindow>
#include <QWebView>
#include "Diaspora.hpp"

/**
 * Main application window.
 */
class Pusteblume : public QMainWindow
{
  Q_OBJECT

public:
  Pusteblume(QWidget *parent = 0);
  ~Pusteblume();

public slots:
  void postsReady(list<QString> posts);
  void postsError(const char* message);

private:
  Diaspora diaspora;
  QWebView* webkit;
};

#endif // PUSTEBLUME_HPP
