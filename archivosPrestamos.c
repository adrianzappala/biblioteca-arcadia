#include <stdio.h>
#include <stdlib.h>
#include "archivosPrestamos.h"

#define CAPACIDAD_INICIAL 16

/*
 * Lee prestamos.dat registro por registro. El arreglo empieza chico y se
 * duplica con realloc cuando se llena. Como realloc puede MOVER el bloque
 * de memoria, la direccion cambia: por eso la funcion recibe un puntero
 * doble (Prestamo **) y no un puntero simple.
 */
int cargarPrestamos(Prestamo **lista, int *cantidad)
{
    FILE *archivo;
    Prestamo *arreglo, *nuevo;
    int capacidad = CAPACIDAD_INICIAL;
    int n = 0;

    *lista = NULL;
    *cantidad = 0;

    arreglo = (Prestamo *)malloc(capacidad * sizeof(Prestamo));
    if (arreglo == NULL)
    {
        return 0;
    }

    archivo = fopen(ARCHIVO_PRESTAMOS, "rb");
    if (archivo == NULL)
    {
        /* Todavia no hay prestamos: no es un error. */
        *lista = arreglo;
        return 1;
    }

    while (fread(&arreglo[n], sizeof(Prestamo), 1, archivo) == 1)
    {
        n++;
        if (n == capacidad)
        {
            capacidad *= 2;
            nuevo = (Prestamo *)realloc(arreglo, capacidad * sizeof(Prestamo));
            if (nuevo == NULL)
            {
                free(arreglo);
                fclose(archivo);
                return 0;
            }
            arreglo = nuevo;
        }
    }
    fclose(archivo);

    *lista = arreglo;
    *cantidad = n;
    return 1;
}

int guardarPrestamos(const Prestamo *lista, int cantidad)
{
    FILE *archivo = fopen(ARCHIVO_PRESTAMOS, "wb");
    size_t escritos;

    if (archivo == NULL)
    {
        return 0;
    }
    escritos = fwrite(lista, sizeof(Prestamo), cantidad, archivo);
    fclose(archivo);
    return escritos == (size_t)cantidad;
}

void liberarPrestamos(Prestamo **lista, int *cantidad)
{
    free(*lista);
    *lista = NULL;
    *cantidad = 0;
}
