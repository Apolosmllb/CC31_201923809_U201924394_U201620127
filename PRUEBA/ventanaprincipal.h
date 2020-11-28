#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include"Avl.h"
#include"Usuario.h"
#include <vector>
#include"Publicaciones.h"
#include"Comentarios.h"
#include"Followers.h"
#include"Iteraciones.h"
#include"Usuario_unico.h"

namespace Ui {
class VentanaPrincipal;
}

class VentanaPrincipal : public QMainWindow
{

    Q_OBJECT

    //USUARIOS
    Avl<Cusuario*,QString>* arbol_indx_email1;
    Avl<Cusuario*, QString>* arbol_indx_nombre1;
    Avl<Cusuario*, QString>* arbol_indx_id1;
    Avl<Cusuario_u*, QString>* arbol_indx_nombre_unico;

    //PUBLICACIONES
    vector<CPublicacion*> Publicaciones;
    Avl<CPublicacion*,long>* Pub_indx_numlikes;
    Avl<CPublicacion*,QString>* Pub_indx_id;
    //COMENTARIOS
    Avl<Comentario*,QString>* comentarios_indx_id;
    //FOLLOWERS
    Avl<Follower*,QString>* followers_indx_id;


public:
       Cusuario* u;
       Follower* F;

    explicit VentanaPrincipal(QWidget *parent = nullptr);
    ~VentanaPrincipal();

private:
    Ui::VentanaPrincipal *ui;
private slots:
    void CargarDatos();

    void mostrar_publicaciones_indx();

    void mostrar_publicaciones();

    void buscar_id(QString id);

    void on_Binicio_clicked();

    void mostrar_usuarios_indx();
    void buscar_usuario(QString name);

    void on_ListaPublicaciones_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_7_clicked();
    void on_L_BUSCAR_returnPressed();
};

#endif // VENTANAPRINCIPAL_H
