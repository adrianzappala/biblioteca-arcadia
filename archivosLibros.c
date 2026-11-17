#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivosLibros.h"

#define CAPACIDAD_INICIAL 32

int cargarLibros(Libro **lista, int *cantidad)
{
    FILE *archivo;
    Libro *arreglo, *nuevo;
    int capacidad = CAPACIDAD_INICIAL;
    int n = 0;

    *lista = NULL;
    *cantidad = 0;

    arreglo = (Libro *)malloc(capacidad * sizeof(Libro));
    if (arreglo == NULL)
    {
        return 0;
    }

    archivo = fopen(ARCHIVO_LIBROS_DAT, "rb");
    if (archivo == NULL)
    {
        *lista = arreglo;
        return 1;
    }

    while (fread(&arreglo[n], sizeof(Libro), 1, archivo) == 1)
    {
        n++;
        if (n == capacidad)
        {
            capacidad *= 2;
            nuevo = (Libro *)realloc(arreglo, capacidad * sizeof(Libro));
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

void liberarLibros(Libro **lista, int *cantidad)
{
    free(*lista);
    *lista = NULL;
    *cantidad = 0;
}

int buscarLibroEnLista(const Libro *lista, int cantidad, const char isbn[])
{
    int i;
    for (i = 0; i < cantidad; i++)
    {
        if (strcmp(lista[i].isbn, isbn) == 0)
        {
            return i;
        }
    }
    return -1;
}
