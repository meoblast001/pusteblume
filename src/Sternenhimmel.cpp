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
#include <QWebView>
#include "Sternenhimmel.hpp"

Sternenhimmel::Sternenhimmel(QWidget *parent) :
  QMainWindow(parent),
  diaspora("https", "pod.geraspora.de")
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

  // Query Diaspora for 33c3.
  diaspora.fetchPosts(QString("33c3"));
}

Sternenhimmel::~Sternenhimmel()
{
}

void Sternenhimmel::postsReady(list<PostEntity> posts)
{
  for (auto post = posts.cbegin(); post != posts.cend(); ++post) {
    auto authorName = new QLabel();
    resultsLayout->addWidget(authorName);
    authorName->setText(post->getAuthorName());

    auto webView = new QWebView();
    resultsLayout->addWidget(webView);
    webView->setHtml(post->getText());
    webView->setMinimumHeight(200);
  }
}

void Sternenhimmel::postsError(const char* message)
{
  auto error = new QLabel();
  resultsLayout->addWidget(error);
  error->setText(message);
}
