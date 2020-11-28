#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include <QFile>
#include<iostream>
#include<queue>
#include<Avl.h>
#include"Comentarios.h"
#include"Followers.h"
#include"Publicaciones.h"
#include<QFileDialog>
#include"Usuario_unico.h"

using namespace std;
VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);

    //----------------------------------------USUARIOS--------------------------------------------
    this-> arbol_indx_nombre1 = new Avl<Cusuario*, QString>([](Cusuario* a) {return a->getnombre(); });
    this-> arbol_indx_email1 =  new Avl<Cusuario*, QString>([](Cusuario* a) {return a->getemail(); });
    this->arbol_indx_id1 = new Avl<Cusuario*, QString>([](Cusuario* a) {return a->getID(); });
    this->arbol_indx_nombre_unico= new Avl<Cusuario_u*, QString>([](Cusuario_u* u) {return u->getnombre(); });

    //-------------------------------------PUBLICACIONES----------------------------------------------------
    this-> Pub_indx_numlikes =  new Avl<CPublicacion*,long>([](CPublicacion* p) {return p->getnumlikes(); });
   this->Pub_indx_id=new Avl<CPublicacion*,QString>([](CPublicacion* p) {return p->getid(); });

  //--------------------------------------COMENTARIOS------------------------------------------
    this->comentarios_indx_id=new Avl<Comentario*,QString>([](Comentario* a) {return a->getid(); });

    //---------------------------------------FOLLOWERS--------------------------------------------
    this-> followers_indx_id=new Avl<Follower*,QString>([](Follower* a) {return a->getid(); });


    connect(ui->Binicio,SIGNAL(released()),this,SLOT(mostrar_publicaciones()));
    connect(ui->Binicio_2,SIGNAL(released()),this,SLOT(mostrar_publicaciones_indx()));
    ui->stackedWidget->setCurrentIndex(0);


    this->CargarDatos();
    this->mostrar_usuarios_indx();

  //  this->CargarPublicaciones();


}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::CargarDatos(){



//----------------------------------------------PUBLICACIONES----------------------------------------------------
    QString idU,title,pubdate;
    QString id;
    long numlikes;
    QString tmp;


    QFile fileP("publications.tsv");
     auto cNAME_p = [=](CPublicacion* t1, CPublicacion* t2)->bool {return t1->getnumlikes()<=t2->getnumlikes(); };
     auto cID_p=  [=](CPublicacion* t1, CPublicacion* t2)->bool {return t1->getid().compare(t2->getid())>=0; };
    if(fileP.open(QIODevice::ReadOnly)){
        QTextStream in(&fileP);

        while(!in.atEnd()){

            QString linea = in.readLine();
            QStringList palabrasp= linea.split("\t");
            id= palabrasp[0];

            idU=palabrasp[1];
            title =palabrasp[2];
            pubdate=palabrasp[4];
            tmp=palabrasp[5];
            numlikes=tmp.toLong();

            //TODO AGREGAR

          CPublicacion* P= new CPublicacion(id,idU,title,pubdate,numlikes);
          Publicaciones.push_back(P);

         Pub_indx_numlikes->add(P,cNAME_p);
         Pub_indx_id->add(P,cID_p);

        }

        fileP.close();
    }
//------------------------------------------USUARIOS---------------------------------------------------------
    QString email, name, joindate;
    QString id_u;

    auto cID_u = [=](Cusuario* t1, Cusuario* t2)->bool {return t1->getID().compare(t2->getID())>=0 ; };
    auto cNAME_u = [=](Cusuario* t1, Cusuario* t2)->bool {return t1->getnombre().compare(t2->getnombre())>=0; };
    auto cEMAIL_u = [=](Cusuario* t1, Cusuario* t2)->bool {return t1->getemail().compare(t2->getemail())>=0; };
    auto cNAME_u2 = [=](Cusuario_u* t1, Cusuario_u* t2)->bool {return t1->getnombre().compare(t2->getnombre())>=0; };
    QFile file_u("users.tsv");
        if(file_u.open(QIODevice::ReadOnly)){

            QTextStream in(&file_u);
            while(!in.atEnd()){
                QString linea_u = in.readLine();
                QStringList palabras_u= linea_u.split("\t");
                id_u =palabras_u[0];

                email=palabras_u[1];
                name= palabras_u[2];
                joindate=palabras_u[3];
                u = new Cusuario(id_u,email,name,joindate);
                arbol_indx_nombre1->add(u,cNAME_u);
                arbol_indx_email1->add(u,cEMAIL_u);
                arbol_indx_id1->add(u,cID_u);

                Cusuario_u* a= new Cusuario_u(name);
                arbol_indx_nombre_unico->add(a,cNAME_u2);
            }


            file_u.close();
        }


//------------------------------------------Comentarios---------------------------------------------------------

        QString id_c;
        QString idPub, date, text;

        auto cID_C = [=](Comentario* t1, Comentario* t2)->bool {return t1->getid().compare(t2->getid())>=0 ; };
        QFile file_C("comment.tsv");
            if(file_C.open(QIODevice::ReadOnly)){

                QTextStream in(&file_C);
                while(!in.atEnd()){
                    QString linea_c = in.readLine();
                    QStringList palabras_c= linea_c.split("\t");
                    id_c =palabras_c[0];
                    idPub=palabras_c[1];
                    date= palabras_c[2];
                    text=palabras_c[3];
                    Comentario* c = new Comentario(id_c,idPub,date,text);
                    comentarios_indx_id->add(c,cID_C);
                }
                file_C.close();
            }

//------------------------------------------FOLLOWERS---------------------------------------------------------
            QString id_f;
            QString idF;

            auto cID_F= [=](Follower* f1, Follower* f2)->bool {return f1->getid().compare(f2->getid())>=0 ; };
            QFile file_F("Seguidores.tsv");
                if(file_F.open(QIODevice::ReadOnly)){
                   QTextStream in(&file_F);
                    while(!in.atEnd()){
                        QString linea_f = in.readLine();
                        QStringList palabras_f= linea_f.split(",");
                        id_f =palabras_f[0];
                        idF=palabras_f[1];
                       F= new Follower(id_f,idF);
                       followers_indx_id->add(F,cID_F);
                    }
                    file_F.close();
                }


}

void VentanaPrincipal::mostrar_publicaciones_indx(){
ui->ListaPublicaciones->clear();
ui->ListaPublicaciones->addItem("  id: idU:      Fecha:   Likes:\t\tPublicaciones:");
Pub_indx_numlikes->inOrder(ui->ListaPublicaciones);

}

void VentanaPrincipal::mostrar_usuarios_indx(){
    ui->ListaUsuarios->clear();
    arbol_indx_nombre_unico->inOrder(ui->ListaUsuarios);
}
void VentanaPrincipal::mostrar_publicaciones(){
    ui->ListaPublicaciones->clear();
    ui->ListaPublicaciones->addItem(" id: idU:      Fecha:   Likes:\t\tPublicaciones:");

    for(auto i: Publicaciones)
    ui->ListaPublicaciones->addItem(i->toString());
 }

void VentanaPrincipal::buscar_id(QString id){
  Comentario* c;

  CPublicacion* a;

     if((u = arbol_indx_id1->find(id))){
      ui->M_nombre->setText(u->getnombre());
     }


    if((F = followers_indx_id->find(id))){
     ui->M_Follower->setText(F->getidF());
    }else ui->M_Follower->setText("F->getidF()");

    if((c= comentarios_indx_id->find(id))){
        ui->M_Comentarios->setText(c->getText());
    }

  if(( a=Pub_indx_id->find(id))){
       ui->M_Publicacion->setText(a->getPUB());
   }

}




void VentanaPrincipal::on_Binicio_clicked(){
   ui->stackedWidget->setCurrentIndex(0);
}

 // mostrarDatos();


void VentanaPrincipal::on_ListaPublicaciones_itemDoubleClicked(QListWidgetItem *item)
{
    ui->stackedWidget->setCurrentIndex(1);

    QStringList data = item->text().split(" | ");

    buscar_id(data[0]);

}
//clorie@gmail Mecos

void VentanaPrincipal::on_pushButton_7_clicked()
{
    //CAMBIO DE IMAGEN DE PERFIL


        QString filename = QFileDialog::getOpenFileName(this,tr("Open Image"),"C:\\",tr("Image Files(*.png *.jpg *bmp)"));
            QPixmap* imagen = new QPixmap(filename);
            //ui->logo->setPixmap(*imagen);
            ui->label_2->setPixmap(*imagen);


}
void VentanaPrincipal::buscar_usuario(QString name){
    Cusuario_u* unico;
     ui->ListaUsuarios->clear();
  if((unico=arbol_indx_nombre_unico->find(name))){
      ui->ListaUsuarios->clear();
      ui->ListaUsuarios->addItem(unico->getnombre());
  }else  {
      ui->ListaUsuarios->clear();
      ui->ListaUsuarios->addItem("Not Found");
  }




}

void VentanaPrincipal::on_L_BUSCAR_returnPressed()
{
   buscar_usuario( ui->L_BUSCAR->text());
}
