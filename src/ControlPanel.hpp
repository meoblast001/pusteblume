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

#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPlainTextEdit>
#include "Presentation.hpp"

class ControlPanel : public QMainWindow
{
  Q_OBJECT

public:
  ControlPanel(QWidget *parent = 0);
  ~ControlPanel();

public slots:
  void startPresentation();

private:
  const int TEXT_EDIT_HEIGHT = 30;
  QStackedWidget* central;
  Presentation* presentation;
  QPlainTextEdit* podUrlEdit;
  QPlainTextEdit* tagEdit;
};

#endif // CONTROLPANEL_H
