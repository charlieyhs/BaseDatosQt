#ifndef INSERTARPERSONADIALOG_H
#define INSERTARPERSONADIALOG_H

#include "persona.h"
#include <QDialog>

namespace Ui {
class InsertarPersonaDialog;
}

class InsertarPersonaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertarPersonaDialog(QWidget *parent = nullptr);
    ~InsertarPersonaDialog();
    Persona persona()const{return mPersona;}
private slots:
    void on_toolButton_triggered(QAction *arg1);
    void on_toolButton_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::InsertarPersonaDialog *ui;
    Persona mPersona;
};

#endif // INSERTARPERSONADIALOG_H
