#ifndef PERSONA_H
#define PERSONA_H

#include <QString>
#include <QByteArray>

class Persona
{
public:
    Persona(const QString &nombre="", const QString &pais="",const QByteArray &datosImagen = QByteArray());
    QString nombre()const{return mNombre;}
    QString pais()const{return mPais;}
    QByteArray datosImagen()const{return mDatosImagen;}

private:
    QString mNombre;
    QString mPais;
    QByteArray mDatosImagen;
};

#endif // PERSONA_H
