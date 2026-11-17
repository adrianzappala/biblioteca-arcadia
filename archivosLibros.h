#ifndef ARCHIVOS_LIBROS_H
#define ARCHIVOS_LIBROS_H

#include "libros.h"

#define ARCHIVO_LIBROS_DAT "libros.dat"

/* Igual que cargarPrestamos: arreglo dinamico + puntero doble.
 * Devuelve 1 (aunque el archivo no exista) y 0 si falta memoria. */
int cargarLibros(Libro **lista, int *cantidad);

/* Libera el arreglo y deja el puntero en NULL y la cantidad en 0. */
void liberarLibros(Libro **lista, int *cantidad);

/* Devuelve la posicion del libro con ese ISBN en el arreglo, o -1. */
int buscarLibroEnLista(const Libro *lista, int cantidad, const char isbn[]);

#endif
