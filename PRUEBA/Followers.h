#ifndef FOLLOWERS_H
#define FOLLOWERS_H
#include "Avl.h"
#include <string>
#include<conio.h>
#include<iomanip>
#include<QTextStream>

class Follower {
private:
    QString id;
    QString idF;

public:
    Follower(QString id, QString idF) : id(id), idF(idF) {}
    ~Follower(){}

    QString getid() {
        return this->id;
    }

    QString getidF() {
        return this->idF;
    }

    QString fill_space(QString fill, int n = 15) {
        return QString(n - fill.size(), ' ') + fill;
    }

    QString toString() {

        return id+" | " + fill_space(this->idF, 15);

    }

};

#endif // FOLLOWERS_H
