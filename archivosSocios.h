#ifndef ARCHIVOS_SOCIOS_H
#define ARCHIVOS_SOCIOS_H

#include "estructuras.h"

#define ARCHIVO_SOCIOS "socios.dat"

int cargarSocios(Socio **lista, int *cantidad);

int guardarSocios(const Socio *lista, int cantidad);

void liberarSocios(Socio **lista, int *cantidad);

int buscarSocioEnLista(const Socio *lista, int cantidad, const char idSocio[]);

#endif
