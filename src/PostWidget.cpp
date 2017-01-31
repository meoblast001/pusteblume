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

#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QUrl>
#include <QNetworkRequest>
#include <QImage>
#include <QPixmap>
#include "PostWidget.hpp"

PostWidget::PostWidget(QWidget *parent) : QWidget(parent)
{
  // Margins.
  setContentsMargins(5, 5, 5, 5);

  // Layout containing user image and rest.
  auto hLayout = new QHBoxLayout();
  setLayout(hLayout);

  // Create user image widget.
  userImage = new QLabel();
  hLayout->addWidget(userImage);
  userImage->setFixedSize(100, 100);

  // Layout containing user name and post.
  auto vLayout = new QVBoxLayout();
  hLayout->addLayout(vLayout);

  // Create user name widget.
  userName = new QLabel();
  vLayout->addWidget(userName);
  userName->setFixedHeight(25);
  // Set larger and bold font.
  QFont font = userName->font();
  font.setPixelSize(25);
  font.setBold(true);
  userName->setFont(font);

  // Create post body widget.
  postBody = new QWebView(this);
  vLayout->addWidget(postBody);
}

void PostWidget::load(const PostEntity& entity)
{
  // Set user name.
  userName->setText(entity.getAuthorName());

  // Set post body.
  postBody->setHtml(entity.getText());

  QUrl url(entity.getAvatarMedium());
  activeReply = networkManager.get(QNetworkRequest(url));
  connect(activeReply, SIGNAL(finished()), this, SLOT(httpFinished()));
}

void PostWidget::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);
  painter.drawRoundedRect(0, 0, width() - 3, height() - 3, 3, 3);
  QWidget::paintEvent(event);
}

void PostWidget::httpFinished()
{
  if (NULL == activeReply || QNetworkReply::NoError != activeReply->error()) {
    return;
  }
  auto response = activeReply->readAll();

  // Load data to image and set to label.
  QImage image;
  image.loadFromData(response);
  userImage->setPixmap(QPixmap::fromImage(image));
}
