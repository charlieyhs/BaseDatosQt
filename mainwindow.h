#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class BaseDatos;
class QSqlTableModel;

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Apertura{
        ABRIR,GUARDAR
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSalir_triggered();
    void on_actionNuevo_base_de_datos_triggered();
    void on_actionAbrir_Base_de_datos_triggered();

    void on_actionInsertar_Persona_triggered();

    void on_actionEliminar_Persona_triggered();

    void on_tableView_clicked(const QModelIndex &index);

private:
    void abreBaseDatos(Apertura apertura);

    Ui::MainWindow *ui;
    BaseDatos *mBaseDatos;
    QSqlTableModel *mModel;
};
#endif // MAINWINDOW_H
