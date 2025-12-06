

#include "WordNetSynonyms.h"

#include <vector>
#include <string>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QByteArray>
#include <QString>

std::vector<std::string> getSynonyms(const std::string& word)
{
    std::vector<std::string> synonyms;
    if (word.empty()) return synonyms;

    QString qWord = QString::fromStdString(word).toLower();
    qWord.replace(' ', '+');

    QUrl url(QString("http://api.datamuse.com/words?rel_syn=%1").arg(qWord));

    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    QEventLoop loop;


    QNetworkReply* reply = manager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        reply->deleteLater();
        return synonyms;
    }

    QByteArray data = reply->readAll();
    reply->deleteLater();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isArray()) {
        return synonyms;
    }

    QJsonArray arr = doc.array();
    for (const QJsonValue& val : arr) {
        if (!val.isObject()) continue;
        QJsonObject obj = val.toObject();
        QString w = obj.value("word").toString().trimmed();
        if (w.isEmpty()) continue;

        std::string ws = w.toStdString();
        if (ws == word) continue;
        if (std::find(synonyms.begin(), synonyms.end(), ws) == synonyms.end()) {
            synonyms.push_back(ws);
        }
    }

    return synonyms;
}
