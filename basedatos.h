#ifndef BASEDATOS_H
#define BASEDATOS_H

#include "persona.h"

#include <QObject>
#include <QSqlDatabase>


class BaseDatos : public QObject
{
    Q_OBJECT
public:
    explicit BaseDatos(QObject *parent = nullptr);
    bool iniciaBaseDatos(const QString &nombreArchivo);
    bool configuraBaseDatos();
    QString getError()const {return mError;}
    bool insertaPersona(const Persona &persona);
private:
    QSqlDatabase mDatabase;
    QString mError;
};

#endif // BASEDATOS_H
