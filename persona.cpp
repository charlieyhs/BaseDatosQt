#include "persona.h"

Persona::Persona(const QString &nombre, const QString &pais, const QByteArray &datosImagen)
{
    mNombre = nombre;
    mPais = pais;
    mDatosImagen = datosImagen;
}
