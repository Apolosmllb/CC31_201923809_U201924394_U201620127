#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<ventanaprincipal.h>
#include"Usuario.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    vector<Cusuario*> usuarios;
    Avl<Cusuario*,QString>* arbol_indx_email;
    Avl<Cusuario*, QString>* arbol_indx_nombre;
    Avl<Cusuario*, QString>* arbol_indx_id;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();
    void buscar_usuario();
    void leer();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
