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


void Diaspora::httpFinished()
{
  auto response = activeReply->readAll();
  list<QString> collection { QString(response) };
  emit finished(collection);
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
