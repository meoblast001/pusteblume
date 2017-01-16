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

#ifndef PRESENTATION_HPP
#define PRESENTATION_HPP

#include <list>
#include <QMainWindow>
#include <QVBoxLayout>
#include "Diaspora.hpp"

/**
 * Presentation window displaying posts.
 */
class Presentation : public QMainWindow
{
  Q_OBJECT

public:
  Presentation(QString& podUrl, QString& tag, QWidget *parent = 0);
  ~Presentation();

public slots:
  void postsReady(list<PostEntity> posts);
  void postsError(const char* message);

protected:
  virtual void keyReleaseEvent(QKeyEvent* event);

private:
  Diaspora diaspora;
  QString tag;
  QVBoxLayout* resultsLayout;
};

#endif // PRESENTATION_HPP
