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

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QWebView>
#include "Presentation.hpp"
#include "PostWidget.hpp"

Presentation::Presentation(QString& podUrl, QString& tag, QWidget *parent) :
  QMainWindow(parent),
  tag(tag),
  diaspora("https", podUrl)
{
  // Set title and minimum size.
  setWindowTitle("Sternenhimmel");
  setMinimumSize(450, 550);

  // Create layout.
  auto mainLayout = new QVBoxLayout();

  // Primary post with no maximum size.
  firstPost = new PostWidget();
  mainLayout->addWidget(firstPost);

  // Secondary post with maximum size to keep the primary post larger.
  secondPost = new PostWidget();
  secondPost->setMaximumHeight(300);
  mainLayout->addWidget(secondPost);

  // Connect Diaspora signals to window slots.
  connect(&diaspora, SIGNAL(finished(list<PostEntity>)),
          this, SLOT(postsReady(list<PostEntity>)));
  connect(&diaspora, SIGNAL(error(const char*)),
          this, SLOT(postsError(const char*)));

  // Set central widget with layout.
  auto central = new QWidget();
  central->setLayout(mainLayout);
  setCentralWidget(central);

  // Make window full screen.
  showFullScreen();

  // Query diaspora for tag.
  diaspora.fetchPosts(this->tag);
}

Presentation::~Presentation()
{
}

void Presentation::postsReady(list<PostEntity> posts)
{
  auto postEntity = posts.cbegin();
  if (postEntity == posts.cend()) {
    return;
  }
  firstPost->load(*postEntity);

  ++postEntity;
  if (postEntity == posts.cend()) {
    return;
  }
  secondPost->load(*postEntity);
}

void Presentation::postsError(const char* message)
{
  // TODO: Error message.
}

void Presentation::keyReleaseEvent(QKeyEvent* event)
{
  if (Qt::Key_Escape == event->key()) {
    close();
    QMainWindow::keyReleaseEvent(event);
  }
}
