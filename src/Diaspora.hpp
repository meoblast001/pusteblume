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

#ifndef DIASPORA_HPP
#define DIASPORA_HPP

#include <list>
#include <exception>
#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "PostEntity.hpp"

using namespace std;

/**
 * Class to query posts in diaspora* from tags and parse the Markdown. This uses
 * an internal, private API, which is subject to change at any time without
 * warning.
 */
class Diaspora : public QObject
{
  Q_OBJECT

public:
  /**
   * JSON parse exception.
   */
  class ParseException : public exception
  {
  public:
    ParseException(const char* message) : message(message) { }

    virtual const char* what() const throw ()
    {
      return message;
    }

  private:
    const char* message;
  };

  Diaspora(const QString& scheme, const QString& podHost);
  void fetchPosts(const QString& tag);

signals:
  void finished(const list<PostEntity> posts);
  void error(const char* error);

protected:
  static list<PostEntity> parseJson(const QJsonDocument& json)
    throw (ParseException);
  static QString parseMarkdown(const QString& markdown) throw (ParseException);

private:
  QUrl podUrl;
  QNetworkAccessManager networkManager;
  QNetworkReply* activeReply;

  static PostEntity parsePostJson(const QJsonObject& json)
    throw (ParseException);

private slots:
  void httpFinished();
  void httpError(QNetworkReply::NetworkError code);
  void httpSslError();
};

#endif // DIASPORA_HPP
