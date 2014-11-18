#include "kinopoisk.h"
#include "structs.h"
#include <iostream>
#include <map>
#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QRegExp>
#include <QTextCodec>
using namespace std;

QString kinopoisk::request(QString url) {
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QNetworkAccessManager *manager = new QNetworkAccessManager(0);
    QUrl _url(url);
    QNetworkRequest request;
    request.setUrl(_url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; 2films client) Efog/2films (KHTML, like Gecko) Chrome/36.0.1944.0 Efog/0.0.1");
    QNetworkReply *r = manager->get(request);
    QEventLoop wait;
    QObject::connect(r, SIGNAL(finished()), &wait, SLOT(quit()));
    wait.exec();
    QByteArray reply_win1251 = r->readAll();
    QString reply = codec->toUnicode(reply_win1251);
    return reply;
}

filmdata kinopoisk::get_film(QString link) {
    filmdata answer;
    QString url = link;
    QString reply = kinopoisk::request(url);
    QRegExp rating("<span class=\"rating_ball\">(.+)<\\/span>");
    QRegExp ratingCount("<span class=\"ratingCount\" itemprop=\"ratingCount\">(.+)<\\/span>");
    rating.setMinimal(true);
    ratingCount.setMinimal(true);
    rating.indexIn(reply, 0);
    ratingCount.indexIn(reply, 0);
    answer._rating.value = rating.cap(1);
    answer._rating.count = ratingCount.cap(1).toInt();
    answer.trailer = link + "video/";
    return answer;
}

films kinopoisk::search(QString name) {
    name = QString(name.toUtf8());
    QString reply = kinopoisk::request("http://www.kinopoisk.ru/index.php?first=no&kp_query=" + name);
    film *results_temp = new film[11];
    QRegExp list("<div class=\"info\">(.+)<\\/div>");
    list.setMinimal(true);
    int pos = 0, i = 0;
    while ((pos = list.indexIn(reply, pos)) != -1) {
        QString temp_result = list.cap(1);
        film temp;
        QRegExp name("<p class=\"name\"><a href=\".+\">(.+)<\\/a>");
        QRegExp year("year\">(.+)<");
        QRegExp genre("<br \\/>\\((.+)\\)");
        QRegExp link("href=\"\\/level\\/1\\/film\\/([0-9]+)\\/sr\\/1\\/");
        name.setMinimal(true);
        year.setMinimal(true);
        genre.setMinimal(true);
        name.indexIn(temp_result, 0);
        year.indexIn(temp_result, 0);
        genre.indexIn(temp_result, 0);
        link.indexIn(temp_result, 0);
        temp.name = name.cap(1).replace(QRegExp("&nbsp;"), " ");
        temp.year = year.cap(1);
        temp.genre = genre.cap(1);
        temp.link = "http://www.kinopoisk.ru/film/" + link.cap(1) + "/";
        if (!temp.name.isEmpty() && !temp.year.isEmpty() && !temp.genre.isEmpty() && !temp.link.isEmpty()) {
            results_temp[i] = temp;
            i++;
        }
        pos += list.matchedLength();
    }
    films results;
    results.length = i;
    results.list = results_temp;
    return results;
}
