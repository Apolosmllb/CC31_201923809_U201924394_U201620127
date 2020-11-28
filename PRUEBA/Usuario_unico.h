#ifndef USUARIO_UNICO_H
#define USUARIO_UNICO_H

#include "Avl.h"
#include <string>
#include<conio.h>
#include<iomanip>
#include<QTextStream>


    class Cusuario_u
    {

   public:

        Cusuario_u(QString nombre) :
            nombre(nombre) {}
        ~Cusuario_u() {}

        QString getnombre() {
            return this->nombre;
        }

        QString toString() {

            return  this->nombre;

        }


           // cout << setw(4) << id << setw(25) << email << setw(15) << nombre << setw(18)<< joindate << endl;
   private:
        QString nombre;
    };










#endif // USUARIO_UNICO_H
