#include "basedatos.h"
#include <QSqlError>
#include <QSqlQuery>

#include <QVariant>

#define CREATE_TABLE \
    "CREATE TABLE IF NOT EXISTS DuData"\
    "(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"\
    "nombre TEXT NOT NULL,"\
    "pais TEXT NOT NULL,"\
    "datosArchivo BLOB NOT NULL)"


//BLOB = binary large object --- objeto binario largo
BaseDatos::BaseDatos(QObject *parent) : QObject(parent)
{

}

bool BaseDatos::iniciaBaseDatos(const QString &nombreArchivo)
{
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName(nombreArchivo);
    bool ok = mDatabase.open();
    if(!ok){
        mError = mDatabase.lastError().text();
    }
    return ok;
}

bool BaseDatos::configuraBaseDatos()
{
    QSqlQuery q;
    bool ok = q.exec(CREATE_TABLE);
    if(!ok){
        mError = q.lastError().text();
    }
    return ok;
}

bool BaseDatos::insertaPersona(const Persona &persona)
{
    QSqlQuery q;
    q.prepare("INSERT INTO DuData (nombre,pais,datosArchivo) VALUES (?,?,?)");
    q.addBindValue(persona.nombre());
    q.addBindValue(persona.pais());
    q.addBindValue(persona.datosImagen());
    bool ok = q.exec();
    if(!ok){
        mError = q.lastError().text();
    }
    return ok;
}


