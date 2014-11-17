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

#endif // STRUCTS_H
