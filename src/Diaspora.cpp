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

#include <QNetworkRequest>
#include <QJsonArray>
#include <QJsonObject>
#include "Diaspora.hpp"

Diaspora::Diaspora(const QString& scheme, const QString& podHost)
{
  podUrl.setScheme(scheme);
  podUrl.setHost(podHost);
}

void Diaspora::fetchPosts(const QString& tag)
{
  // Construct specific URL for tag's posts.
  QUrl url = podUrl;
  url.setPath(QString("/tags/") + tag + QString(".json"));
  // Create network request.
  activeReply = networkManager.get(QNetworkRequest(url));
  connect(activeReply, SIGNAL(finished()), this, SLOT(httpFinished()));
}

list<PostEntity> Diaspora::parseJson(const QJsonDocument& json)
{
  // Result collection.
  auto entities = list<PostEntity>();

  // Search through JSON array.
  // TODO: Refactor.
  if (json.isArray()) {
    QJsonArray jsonPosts = json.array();
    for (auto iPost = jsonPosts.begin(); iPost != jsonPosts.end(); ++iPost) {
      if (iPost->isObject()) {
        auto postObj = iPost->toObject();
        auto textVal = postObj.take("text");
        if (textVal.type() == QJsonValue::String) {
          auto text = textVal.toString();
          auto authorVal = postObj.take("author");
          if (authorVal.type() == QJsonValue::Object) {
            auto authorObj = authorVal.toObject();
            auto nameVal = authorObj.take("name");
            if (nameVal.type() == QJsonValue::String) {
              auto authorName = nameVal.toString();
              entities.push_back(PostEntity(authorName, text));
            }
          }
        }
      }
    }
  }
  // Error case.
  return entities;
}

void Diaspora::httpFinished()
{
  auto response = activeReply->readAll();
  auto json = QJsonDocument::fromJson(response);
  if (json.isNull()) {
    emit error("JSON parse error.");
  }
  auto entities = parseJson(json);
  emit finished(entities);
}

void Diaspora::httpError(QNetworkReply::NetworkError code)
{
  const char* message;
  switch (code) {
    case QNetworkReply::ConnectionRefusedError:
      message = "Connection refused.";
      break;
    case QNetworkReply::RemoteHostClosedError:
      message = "Remote host closed.";
      break;
    case QNetworkReply::HostNotFoundError:
      message = "Host not found.";
      break;
    default:
      message = "Other.";
      break;
  }
  emit error(message);
}

void Diaspora::httpSslError()
{
  emit error("SSL error.");
}
