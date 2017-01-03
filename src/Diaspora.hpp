/**
 * Copyright (C) 2017 Braden Walters
 *
 * This file is licensed under the MIT Expat License. See LICENSE.txt.
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

#ifndef DIASPORA_HPP
#define DIASPORA_HPP

#include <list>
#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

using namespace std;

/**
 * Class to query posts in Diasporas from tags and parse the Markdown. This uses
 * an internal, private API, which is subject to change at any time without
 * warning.
 */
class Diaspora : public QObject
{
  Q_OBJECT

public:
  Diaspora(const QString& scheme, const QString& podHost);
  void fetchPosts(const QString& tag);

signals:
  void finished(const list<QString> posts);
  void error(const char* error);

private:
  QUrl podUrl;
  QNetworkAccessManager networkManager;
  QNetworkReply* activeReply;

private slots:
  void httpFinished();
  void httpError(QNetworkReply::NetworkError code);
  void httpSslError();
};

#endif // DIASPORA_HPP
