#ifndef STRUCTS_H
#define STRUCTS_H
#include <QString>

struct film {
    QString name;
    QString year;
    QString genre;
    QString link;
};

struct films {
    film* list;
    int length;
};

struct rating {
    QString value;
    int count;
};

struct filmdata {
    rating _rating;
    QString trailer;
    QString torrent;
};

#endif // STRUCTS_H
