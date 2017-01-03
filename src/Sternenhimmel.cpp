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

#include <QVBoxLayout>
#include "Sternenhimmel.hpp"

Sternenhimmel::Sternenhimmel(QWidget *parent) :
  QMainWindow(parent),
  diaspora("https", "pod.geraspora.de")
{
  // Set title.
  setWindowTitle("Sternenhimmel");

  // Create layout.
  auto mainLayout = new QVBoxLayout();

  // Create test WebKit.
  webkit = new QWebView();
  webkit->setHtml(QString("<html><body><b>Hello world!</b></body></html>"));
  mainLayout->addWidget(webkit);

  // Connect Diaspora signals to window slots.
  connect(&diaspora, SIGNAL(finished(list<PostEntity>)),
          this, SLOT(postsReady(list<PostEntity>)));
  connect(&diaspora, SIGNAL(error(const char*)),
          this, SLOT(postsError(const char*)));

  // Set central widget with layout.
  auto central = new QWidget();
  central->setLayout(mainLayout);
  setCentralWidget(central);

  // Query Diaspora for 33c3.
  diaspora.fetchPosts(QString("33c3"));
}

Sternenhimmel::~Sternenhimmel()
{
}

void Sternenhimmel::postsReady(list<PostEntity> posts)
{
  if (posts.cbegin() != posts.cend()) {
    const PostEntity post = *posts.begin();
    webkit->setHtml(post.getText());
  } else {
    webkit->setHtml("Error");
  }
}

void Sternenhimmel::postsError(const char* message)
{
  webkit->setHtml(message);
}
