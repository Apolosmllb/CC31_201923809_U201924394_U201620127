#ifndef __USUARIO_H__
#define __USUARIO_H__

#include "Avl.h"
#include <string>
#include<conio.h>
#include<iomanip>
#include<QTextStream>





    class Cusuario
    {

   public:

        Cusuario(QString id, QString email, QString nombre, QString joindate) :
            id(id),email(email),nombre(nombre),joindate(joindate) {}
        ~Cusuario() {}

        QString getID(){
            return id;
        }

        QString getnombre() {
            return this->nombre;
        }
        QString getemail() {
            return this->email;
        }

        QString fill_space(QString fill, int n = 15){
            return QString(n-fill.size(),' ') +  fill;
        }

        QString toString() {

            return   id+" | " + this->email + " | " + this->nombre + " | " +joindate;

        }

           // cout << setw(4) << id << setw(25) << email << setw(15) << nombre << setw(18)<< joindate << endl;
   private:
        QString id;
        QString email, nombre, joindate;
    };




#endif
