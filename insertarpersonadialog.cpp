#include "insertarpersonadialog.h"
#include "ui_insertarpersonadialog.h"
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QCompleter>
#include <QFileSystemModel>


InsertarPersonaDialog::InsertarPersonaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertarPersonaDialog)
{
    ui->setupUi(this);
    auto fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::rootPath());

    ui->nombreArchivoLineEdit->setCompleter(new QCompleter(fileSystemModel,this));

}

InsertarPersonaDialog::~InsertarPersonaDialog()
{
    delete ui;
}

void InsertarPersonaDialog::on_toolButton_clicked()
{
    auto nombreArchivo = QFileDialog::getOpenFileName(this,"Abrir imagen",QDir::rootPath(),
                                 "Imagenes (*.png *.jpg *.jpeg);;"
                                 "Cualquier Archivo (*.*)");
    ui->nombreArchivoLineEdit->setText(nombreArchivo);

}

void InsertarPersonaDialog::on_buttonBox_accepted()
{
    QFile archivo(ui->nombreArchivoLineEdit->text());
    if(!archivo.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this,"Error",archivo.errorString());
        return;
    }

    mPersona = Persona(ui->nombreLineEdit->text(),
                       ui->paisLineEdit->text(),archivo.readAll());
    archivo.close();
    accept();
}

void InsertarPersonaDialog::on_buttonBox_rejected()
{
    reject();
}
