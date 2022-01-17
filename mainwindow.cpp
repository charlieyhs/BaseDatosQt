#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "basedatos.h"
#include "insertarpersonadialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mBaseDatos = new BaseDatos(this);
    mModel = nullptr;

    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addActions({ui->actionInsertar_Persona,
                              ui->actionEliminar_Persona});

    ui->label->setText("No hay imagen");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSalir_triggered()
{
    close();
}

void MainWindow::on_actionNuevo_base_de_datos_triggered()
{
    abreBaseDatos(GUARDAR);

}

void MainWindow::on_actionAbrir_Base_de_datos_triggered()
{
    abreBaseDatos(ABRIR);

}

void MainWindow::abreBaseDatos(MainWindow::Apertura apertura)
{
    QString nombreArchivo;
    if(apertura == ABRIR){
        nombreArchivo = QFileDialog::getOpenFileName(this,"Abrir base de datos",
                                                          QDir::rootPath(),
                                                          "Base de datos (*.db);;Cualquier Tipo (*.*)");

    }else{
        nombreArchivo = QFileDialog::getSaveFileName(this,"Nueva base de datos",
                                                          QDir::rootPath(),
                                                          "Base de datos (*.db);;Cualquier Tipo (*.*)");
    }
    if(nombreArchivo.isEmpty()){
        return;
    }
    if(!mBaseDatos->iniciaBaseDatos(nombreArchivo)){
        QMessageBox::critical(this,"Error1",mBaseDatos->getError());
        return;
    }
    if(!mBaseDatos->configuraBaseDatos()){
        QMessageBox::critical(this,"Error2",mBaseDatos->getError());
        return;
    }

    delete mModel;
    mModel = new QSqlTableModel(this);
    mModel->setTable("DuData");
    mModel->select();
    ui->tableView->setModel(mModel);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(3);
    mModel->setHeaderData(1,Qt::Horizontal,"Nombre");
    mModel->setHeaderData(2,Qt::Horizontal,"País");
}

void MainWindow::on_actionInsertar_Persona_triggered()
{
    InsertarPersonaDialog d(this);
    if(d.exec() == QDialog::Rejected){
        return;
    }
    if(!mBaseDatos->insertaPersona(d.persona())){
        QMessageBox::critical(this,"Error3",mBaseDatos->getError());
        return;
    }
    if(mModel){
        mModel->select();
    }


}

void MainWindow::on_actionEliminar_Persona_triggered()
{
    if(!mModel){
        return;
    }
    mModel->removeRow(ui->tableView->currentIndex().row());
    mModel->select();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    if(!index.isValid()){
        return;
    }
    const int id = mModel->index(index.row(),0).data().toInt();
    QSqlQuery q;
    q.exec(QString("SELECT datosArchivo FROM DuData WHERE id=%1").arg(id));
    q.next();

    QPixmap pixmap;
    if(!pixmap.loadFromData(q.value(0).toByteArray())){
        ui->label->setText("<b>Error de Imagen</b>");
        return;
    }
    pixmap = pixmap.scaled(200,200);
    ui->label->setPixmap(pixmap);

}
