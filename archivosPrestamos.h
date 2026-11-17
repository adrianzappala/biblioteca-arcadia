#ifndef ARCHIVOS_PRESTAMOS_H
#define ARCHIVOS_PRESTAMOS_H

#include "prestamos.h"

#define ARCHIVO_PRESTAMOS "prestamos.dat"

/*
 * Carga todos los prestamos de prestamos.dat en un arreglo dinamico.
 *   lista    : puntero DOBLE. La funcion hace malloc/realloc y modifica
 *              la direccion del arreglo del que llama.
 *   cantidad : se carga con la cantidad de registros leidos.
 * Devuelve 1 si pudo cargar (aunque no haya registros), 0 si hubo error
 * de memoria. Si el archivo no existe, devuelve 1 con cantidad = 0.
 * Quien llama debe liberar con liberarPrestamos().
 */
int cargarPrestamos(Prestamo **lista, int *cantidad);

/* Reescribe prestamos.dat completo con el arreglo recibido. 1 = ok. */
int guardarPrestamos(const Prestamo *lista, int cantidad);

/* Libera el arreglo y deja el puntero en NULL y la cantidad en 0. */
void liberarPrestamos(Prestamo **lista, int *cantidad);

#endif
