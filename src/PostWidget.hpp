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

#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLabel>
#include <QWebView>
#include "PostEntity.hpp"

class PostWidget : public QWidget
{
  Q_OBJECT

public:
  explicit PostWidget(QWidget* parent = 0);
  void clear();
  void load(const PostEntity& entity);

protected:
  virtual void paintEvent(QPaintEvent* event) override;

private:
  QNetworkAccessManager networkManager;
  QNetworkReply* activeReply;
  QLabel* userImage;
  QLabel* userName;
  QWebView* postBody;

private slots:
  void httpFinished();
};

#endif // POSTWIDGET_H
