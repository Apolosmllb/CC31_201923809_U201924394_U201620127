#ifndef ITERACIONES_H
#define ITERACIONES_H

#include "Avl.h"
#include <string>
#include<conio.h>
#include<iomanip>
#include<QTextStream>

class Iteraction {
private:
    QString idUser, idPub, date, share;

public:
    Iteraction(QString idUser, QString idPub, QString date, QString share) :
        idUser(idUser), idPub(idPub), date(date), share(share){}
    ~Iteraction(){}

    QString getidUser() {
        return this->idUser;
    }

    QString getidPub() {
        return this->idPub;
    }

    QString getDate() {
        return this->date;
    }

    QString getShare() {
        return this->share;
    }

    QString fill_space(QString fill, int n = 15) {
        return QString(n - fill.size(), ' ') + fill;
    }

    QString toString() {

        return fill_space(this->idUser, 15) + " | " + fill_space(this->idPub, 15)
            + " | " + fill_space(this->date, 15) + " | " + fill_space(share);

    }
};
#endif // ITERACIONES_H
