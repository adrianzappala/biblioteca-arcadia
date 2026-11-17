#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivosSocios.h"

#define CAPACIDAD_INICIAL 16

int cargarSocios(Socio **lista, int *cantidad)
{
    FILE *archivo;
    Socio *arreglo, *nuevo;
    int capacidad = CAPACIDAD_INICIAL;
    int n = 0;

    *lista = NULL;
    *cantidad = 0;

    arreglo = (Socio *)malloc(capacidad * sizeof(Socio));
    if (arreglo == NULL)
    {
        return 0;
    }

    archivo = fopen(ARCHIVO_SOCIOS, "rb");
    if (archivo == NULL)
    {
        *lista = arreglo;
        return 1;
    }

    while (fread(&arreglo[n], sizeof(Socio), 1, archivo) == 1)
    {
        n++;
        if (n == capacidad)
        {
            capacidad *= 2;
            nuevo = (Socio *)realloc(arreglo, capacidad * sizeof(Socio));
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

int guardarSocios(const Socio *lista, int cantidad)
{
    FILE *archivo = fopen(ARCHIVO_SOCIOS, "wb");
    size_t escritos;

    if (archivo == NULL)
    {
        return 0;
    }
    escritos = fwrite(lista, sizeof(Socio), cantidad, archivo);
    fclose(archivo);
    return escritos == (size_t)cantidad;
}

void liberarSocios(Socio **lista, int *cantidad)
{
    free(*lista);
    *lista = NULL;
    *cantidad = 0;
}

int buscarSocioEnLista(const Socio *lista, int cantidad, const char idSocio[])
{
    int i;
    for (i = 0; i < cantidad; i++)
    {
        if (strcmp(lista[i].idSocio, idSocio) == 0)
        {
            return i;
        }
    }
    return -1;
}
