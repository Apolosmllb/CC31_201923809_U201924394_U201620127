#ifndef PUBLICACIONES_H
#define PUBLICACIONES_H
#include "Avl.h"
#include <string>
#include<conio.h>
#include<iomanip>
#include<QTextStream>



    class CPublicacion
    {

   public:

        CPublicacion(QString id, QString idU,QString title, QString pubdate,long numlikes) :
            id(id),idU(idU),title(title),pubdate(pubdate),numlikes(numlikes) {}
        ~CPublicacion() {}

        long getnumlikes() {
            return this->numlikes;
        }
        QString getid(){
            return this->id;
        }
         QString getPUB(){
                return this->title;
          }

        QString fill_space(QString fill, int n = 15){
            int sep = n-fill.size();
            if(sep%2 !=0)
            return QString((sep/2),' ')+fill + QString((sep/2)+1,' ');
            return QString((sep/2),' ') + fill + QString((sep/2),' ');
        }

        QString toString() {

            QString tmp;
            tmp=QString("%1").arg(numlikes);

            return  id+" | " + fill_space(this->idU,4)
                    + "|" + fill_space(this->pubdate,12)
                    + "|" + fill_space(tmp,6)
                    + "|" + fill_space(this->title,150);
                }

           // cout << setw(4) << id << setw(25) << email << setw(15) << nombre << setw(18)<< joindate << endl;
   private:
       QString id;
       QString idU,title,pubdate;
       long numlikes;

    };





#endif // PUBLICACIONES_H
