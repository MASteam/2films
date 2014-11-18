#ifndef KINOPOISK_H
#define KINOPOISK_H
#include <iostream>
#include <map>
#include <QString>
#include <structs.h>
using namespace std;

class kinopoisk {
    public:
        static films search(QString name);
        static filmdata get_film(QString link);
    private:
        static QString request(QString url);
        virtual void abstract() = 0;
};

#endif // KINOPOISK_H
