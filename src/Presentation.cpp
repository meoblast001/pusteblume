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

  // Scroll area with results layout.
  auto scrollArea = new QScrollArea();
  mainLayout->addWidget(scrollArea);

  // Create central widget for scroll area and its layout.
  auto scrollCentral = new QWidget();
  resultsLayout = new QVBoxLayout();
  scrollCentral->setLayout(resultsLayout);

  // Set scroll area central widget.
  scrollArea->setWidget(scrollCentral);
  scrollArea->setWidgetResizable(true);

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
  for (auto post = posts.cbegin(); post != posts.cend(); ++post) {
    auto postWidget = new PostWidget(this);
    postWidget->load(*post);
    resultsLayout->addWidget(postWidget);
  }
}

void Presentation::postsError(const char* message)
{
  auto error = new QLabel();
  resultsLayout->addWidget(error);
  error->setText(message);
}

void Presentation::keyReleaseEvent(QKeyEvent* event)
{
  if (Qt::Key_Escape == event->key()) {
    close();
    QMainWindow::keyReleaseEvent(event);
  }
}
