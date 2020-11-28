#ifndef COMENTARIOS_H
#define COMENTARIOS_H
#include "Avl.h"
#include <string>
#include<conio.h>
#include<iomanip>
#include<QTextStream>

class Comentario {

private:

    QString id;
    QString idPub, date, text;

public:
    Comentario(QString id, QString idPub, QString date, QString text) :
        id(id), idPub(idPub), date(date), text(text) {}
    ~Comentario(){}

    QString getText() {
        return this->text;
    }

    QString getidPub() {
        return this->idPub;
    }

    QString getid() {
        return this->id;
    }

    QString getDate() {
        return this->date;
    }

    QString fill_space(QString fill, int n = 15) {
        return QString(n - fill.size(), ' ') + fill;
    }

    QString toString() {


        return id+" | " + fill_space(this->idPub, 15)
            + " | " + fill_space(this->date, 15) + " | " + fill_space(text);

    }
};
#endif // COMENTARIOS_H
