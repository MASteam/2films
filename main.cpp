#include <QCoreApplication>
#include <kinopoisk.h>
#include <iostream>
#include <structs.h>
#include <QString>
#include <QTextStream>
using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QTextStream qin(stdin);
    QString filmname = "";
    if (argc != 2) {
        cout << "Введите название фильма: ";
        filmname = qin.readLine();
    } else {
        filmname = argv[1];
    }
    films found = kinopoisk::search(filmname);
    if (found.length == 0) {
        cout << "Не найдено ни одного фильма. Попробуйте уточнить запрос.\r\n";
        return 0;
    }
    for (int i = 0; i < found.length; i++) {
        film f = found.list[i];
        QString output("Совпадение №" + QString::number(i + 1) + ": " + f.name + " (" + f.year + ") - " + f.genre);
        cout << output.toUtf8().constData() << "\r\n";
    }
    int filmnum = 0;
    while (filmnum < 1 || filmnum > found.length) {
        cout << "\r\nВведите номер нужного фильма: ";
        cin >> filmnum;
        if (filmnum < 1 || filmnum > found.length) cout << "Неверный номер фильма; попробуйте еще раз.";
    }

    return 0;//a.exec();
}
