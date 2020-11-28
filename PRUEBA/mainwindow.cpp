#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ventanaprincipal.h>
#include <QFile>
#include<QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this-> arbol_indx_nombre = new Avl<Cusuario*, QString>([](Cusuario* a) {return a->getnombre(); });
    this-> arbol_indx_email =  new Avl<Cusuario*, QString>([](Cusuario* a) {return a->getemail(); });
    this->arbol_indx_id = new Avl<Cusuario*, QString>([](Cusuario* a) {return a->getID(); });
  //  connect(ui->pushButton,SIGNAL(released())this,SLOT)
      leer();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

  buscar_usuario();

}

void MainWindow::buscar_usuario(){
    Cusuario* t;
    Cusuario* t1;
    QString usuario;
    QString email;

    if((ui->Lusuario->text() != "") && (ui->Lemail->text() != "")){

        usuario = ui->Lusuario->text();
        email = ui->Lemail->text();

        if((t=arbol_indx_nombre->find(usuario)) && (t1=arbol_indx_email->find(email))){
        QMessageBox::about(this," Inicio Sesion "," Hola : "+ t->toString()+"  ");
        VentanaPrincipal *ventana1 = new VentanaPrincipal(this);
        ventana1->show();
        }else QMessageBox::about(this,"  ", " USUARIO NO REGISTRADO");

    }
}
void MainWindow::leer(){
    QString email, name, joinDate;
    QString id;

    auto cID = [=](Cusuario* t1, Cusuario* t2)->bool {return t1->getID().compare(t2->getID())>=0 ; };
    auto cNAME = [=](Cusuario* t1, Cusuario* t2)->bool {return t1->getnombre().compare(t2->getnombre())>=0; };
    auto cEMAIL = [=](Cusuario* t1, Cusuario* t2)->bool {return t1->getemail().compare(t2->getemail())>=0; };
    QFile file("users.tsv");
        if(file.open(QIODevice::ReadOnly)){
            QTextStream in(&file);
            while(!in.atEnd()){
                QString linea = in.readLine();
                QStringList palabras= linea.split("\t");
                id =palabras[0];
                email=palabras[1];
                name= palabras[2];
                joinDate=palabras[3];
                Cusuario* t = new Cusuario(id,email,name,joinDate);
                arbol_indx_nombre->add(t,cNAME);
                arbol_indx_email->add(t,cEMAIL);
                arbol_indx_id->add(t,cID);
            }
            file.close();
        }
}


// Avl<Cusuario*,QString>* arbol_indx_email;
// Avl<Cusuario*, QString>* hola;
// this-> hola = new Avl<Cusuario*, QString>([](Cusuario* a) {return a->getnombre(); });
// this-> arbol_indx_email =new  Avl<Cusuario*, QString>([](Cusuario* a) {return a->getemail(); });
// connect(ui->Binicio,SIGNAL(released()),this,SLOT(listOrdLikes()));
