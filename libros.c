
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "autores.h"
#include "libros.h"

#define ARCHIVO_LIBROS "libros.dat"

// Busca un libro por ISBN y devuelve su posicion.
int buscarPosicion(char isbn[])
{
    FILE *archivo;
    Libro libro;
    int posicion = 0;

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
        return -1;

    while (fread(&libro, sizeof(Libro), 1, archivo) == 1)
    {
        if (strcmp(libro.isbn, isbn) == 0)
        {
            fclose(archivo);
            return posicion;
        }

        posicion++;
    }

    fclose(archivo);
    return -1;
}

// Agrega un nuevo libro al catalogo.
void agregarLibro(void)
{
    FILE *archivo;
    Libro libro;

    printf("\n===== AGREGAR LIBRO =====\n");

    printf("ISBN: ");
    scanf(" %19[^\n]", libro.isbn);

    if (buscarPosicion(libro.isbn) != -1)
    {
        printf("Ya existe un libro con ese ISBN.\n");
        return;
    }

    printf("Titulo: ");
    scanf(" %99[^\n]", libro.titulo);

    printf("ID del autor: ");
    scanf("%d", &libro.idAutor);

    printf("Anio de publicacion: ");
    scanf("%d", &libro.anioPublicacion);

    printf("Stock total: ");
    scanf("%d", &libro.stockTotal);

    if (libro.stockTotal < 0)
    {
        printf("El stock no puede ser negativo.\n");
        return;
    }

    libro.stockDisponible = libro.stockTotal;

    archivo = fopen(ARCHIVO_LIBROS, "ab");

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fwrite(&libro, sizeof(Libro), 1, archivo);
    fclose(archivo);

    printf("Libro agregado correctamente.\n");
}

// Modifica los datos de un libro existente.
void modificarLibro(void)
{
    FILE *archivo;
    Libro libro;
    char isbn[20];
    int encontrado = 0;

    printf("\n===== MODIFICAR LIBRO =====\n");
    printf("Ingrese ISBN: ");
    scanf(" %19[^\n]", isbn);

    archivo = fopen(ARCHIVO_LIBROS, "rb+");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    while (fread(&libro, sizeof(Libro), 1, archivo) == 1)
    {
        if (strcmp(libro.isbn, isbn) == 0)
        {
            encontrado = 1;

            printf("Nuevo titulo: ");
            scanf(" %99[^\n]", libro.titulo);

            printf("Nuevo ID del autor: ");
            scanf("%d", &libro.idAutor);

            printf("Nuevo anio: ");
            scanf("%d", &libro.anioPublicacion);

            printf("Nuevo stock total: ");
            scanf("%d", &libro.stockTotal);

            if (libro.stockTotal < 0 ||
                libro.stockTotal < libro.stockTotal - libro.stockDisponible)
            {
                printf("Stock invalido.\n");
                fclose(archivo);
                return;
            }

            libro.stockDisponible = libro.stockTotal;

            fseek(archivo, -(long)sizeof(Libro), SEEK_CUR);
            fwrite(&libro, sizeof(Libro), 1, archivo);

            printf("Libro modificado correctamente.\n");
            break;
        }
    }

    if (!encontrado)
        printf("No se encontro el libro.\n");

    fclose(archivo);
}

// Muestra todos los libros registrados.
void listarLibros(void)
{
    FILE *archivo;
    Libro libro;

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\n===== CATALOGO DE LIBROS =====\n");

    while (fread(&libro, sizeof(Libro), 1, archivo) == 1)
    {
        printf("\nISBN: %s\n", libro.isbn);
        printf("Titulo: %s\n", libro.titulo);
        printf("Autor: %s\n", obtenerNombreAutor(libro.idAutor));
        printf("Anio: %d\n", libro.anioPublicacion);
        printf("Stock: %d\n", libro.stockDisponible);
    }

    fclose(archivo);
}

// Busca y muestra un libro por ISBN.
void buscarLibro(void)
{
    FILE *archivo;
    Libro libro;
    char isbn[20];
    int encontrado = 0;

    printf("\nIngrese ISBN: ");
    scanf(" %19[^\n]", isbn);

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    while (fread(&libro, sizeof(Libro), 1, archivo) == 1)
    {
        if (strcmp(libro.isbn, isbn) == 0)
        {
            printf("\nTitulo: %s\n", libro.titulo);
            printf("ISBN: %s\n", libro.isbn);
            printf("Autor: %s\n", obtenerNombreAutor(libro.idAutor));
            printf("Anio: %d\n", libro.anioPublicacion);
            printf("Stock total: %d\n", libro.stockTotal);
            printf("Stock disponible: %d\n", libro.stockDisponible);

            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("Libro no encontrado.\n");

    fclose(archivo);
}

// Muestra solamente los libros disponibles.
void listarLibrosDisponibles(void)
{
    FILE *archivo;
    Libro libro;
    int encontrados = 0;

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\n===== LIBROS DISPONIBLES =====\n");

    while (fread(&libro, sizeof(Libro), 1, archivo) == 1)
    {
        if (libro.stockDisponible > 0)
        {
            printf("\n%s - %s\n", libro.titulo, libro.isbn);
            printf("Autor: %s\n", obtenerNombreAutor(libro.idAutor));
            printf("Stock disponible: %d\n", libro.stockDisponible);
            encontrados = 1;
        }
    }

    if (!encontrados)
        printf("No hay libros disponibles.\n");

    fclose(archivo);
}

// Carga automaticamente todas las obras de autores.c al catalogo.
void cargarObrasIniciales(void)
{
    FILE *archivo;
    Libro libro;
    int i;

    archivo = fopen(ARCHIVO_LIBROS, "ab");

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo de libros.\n");
        return;
    }

    for (i = 0; i < cantidadObras; i++)
    {
        sprintf(libro.isbn, "ARC%04d", i + 1);

        strcpy(libro.titulo, obras[i].titulo);
        libro.idAutor = obras[i].idAutor;
        libro.anioPublicacion = 0;
        libro.stockTotal = 3;
        libro.stockDisponible = 3;

        fwrite(&libro, sizeof(Libro), 1, archivo);
    }

    fclose(archivo);

    printf("Se cargaron %d obras al catalogo.\n", cantidadObras);
}

// Busca libros por coincidencia en el titulo.
void buscarLibroPorTitulo(void)
{
    FILE *archivo;
    Libro libro;
    char tituloBuscado[100];
    int encontrados = 0;

    printf("\n===== BUSCAR LIBRO POR TITULO =====\n");
    printf("Ingrese el titulo o una palabra: ");
    scanf(" %99[^\n]", tituloBuscado);

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    while (fread(&libro, sizeof(Libro), 1, archivo) == 1)
    {
        if (strstr(libro.titulo, tituloBuscado) != NULL)
        {
            printf("\nISBN: %s\n", libro.isbn);
            printf("Titulo: %s\n", libro.titulo);
            printf("Autor: %s\n", obtenerNombreAutor(libro.idAutor));
            printf("Stock disponible: %d\n", libro.stockDisponible);

            encontrados++;
        }
    }

    if (encontrados == 0)
        printf("No se encontraron coincidencias.\n");

    fclose(archivo);
}

// Busca los libros correspondientes a un autor.
void buscarLibrosPorAutor(void)
{
    FILE *archivo;
    Libro libro;
    int idAutor;
    int encontrados = 0;

    printf("\n===== BUSCAR LIBROS POR AUTOR =====\n");

    listarAutores();

    printf("\nIngrese el ID del autor: ");
    scanf("%d", &idAutor);

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    while (fread(&libro, sizeof(Libro), 1, archivo) == 1)
    {
        if (libro.idAutor == idAutor)
        {
            printf("\n%s - ISBN: %s\n", libro.titulo, libro.isbn);
            printf("Autor: %s\n", obtenerNombreAutor(libro.idAutor));
            encontrados++;
        }
    }

    if (encontrados == 0)
        printf("No se encontraron libros para ese autor.\n");

    fclose(archivo);
}

// Compara textos sin distinguir mayusculas y minusculas.
int contieneTexto(char texto[], char buscado[])
{
    char textoMinuscula[100];
    char buscadoMinuscula[100];
    int i;

    strcpy(textoMinuscula, texto);
    strcpy(buscadoMinuscula, buscado);

    for (i = 0; textoMinuscula[i] != '\0'; i++)
        textoMinuscula[i] = tolower((unsigned char)textoMinuscula[i]);

    for (i = 0; buscadoMinuscula[i] != '\0'; i++)
        buscadoMinuscula[i] = tolower((unsigned char)buscadoMinuscula[i]);

    return strstr(textoMinuscula, buscadoMinuscula) != NULL;
}

// Busca libros por genero, sin distinguir mayusculas y minusculas.
void buscarLibrosPorGenero(void)
{
    FILE *archivo;
    Libro libro;
    char generoBuscado[100];
    int i, encontrados = 0;

    printf("\n===== BUSCAR LIBROS POR GENERO =====\n");
    printf("Ingrese el genero: ");
    scanf(" %99[^\n]", generoBuscado);

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    while (fread(&libro, sizeof(Libro), 1, archivo) == 1)
    {
        for (i = 0; i < cantidadObras; i++)
        {
            if (libro.idAutor == obras[i].idAutor &&
                strcmp(libro.titulo, obras[i].titulo) == 0 &&
                contieneTexto(obras[i].tipo, generoBuscado))
            {
                printf("\nISBN: %s\n", libro.isbn);
                printf("Titulo: %s\n", libro.titulo);
                printf("Autor: %s\n", obtenerNombreAutor(libro.idAutor));
                printf("Genero: %s\n", obras[i].tipo);

                encontrados++;
                break;
            }
        }
    }

    if (encontrados == 0)
        printf("No se encontraron libros para ese genero.\n");

    fclose(archivo);
}

// Busca libros por año de publicacion.
void buscarLibrosPorAnio(void)
{
    FILE *archivo;
    Libro libro;
    int anioBuscado;
    int encontrados = 0;

    printf("\n===== BUSCAR LIBROS POR ANIO =====\n");
    printf("Ingrese el anio: ");
    scanf("%d", &anioBuscado);

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    while (fread(&libro, sizeof(Libro), 1, archivo) == 1)
    {
        if (libro.anioPublicacion == anioBuscado)
        {
            printf("\nISBN: %s\n", libro.isbn);
            printf("Titulo: %s\n", libro.titulo);
            printf("Autor: %s\n", obtenerNombreAutor(libro.idAutor));
            printf("Anio: %d\n", libro.anioPublicacion);

            encontrados++;
        }
    }

    if (encontrados == 0)
        printf("No se encontraron libros de ese anio.\n");

    fclose(archivo);
}

// Busca libros por la inicial de su titulo.
void buscarLibrosPorInicial(void)
{
    FILE *archivo;
    Libro libro;
    char inicial;
    int encontrados = 0;

    printf("\n===== BUSCAR LIBROS POR INICIAL =====\n");
    printf("Ingrese una letra: ");
    scanf(" %c", &inicial);

    inicial = tolower((unsigned char)inicial);

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    while (fread(&libro, sizeof(Libro), 1, archivo) == 1)
    {
        if (tolower((unsigned char)libro.titulo[0]) == inicial)
        {
            printf("\nISBN: %s\n", libro.isbn);
            printf("Titulo: %s\n", libro.titulo);
            printf("Autor: %s\n", obtenerNombreAutor(libro.idAutor));

            encontrados++;
        }
    }

    if (encontrados == 0)
        printf("No se encontraron libros con esa inicial.\n");

    fclose(archivo);
}

// Lista los libros ordenados alfabeticamente por titulo.
void listarLibrosOrdenados(void)
{
    FILE *archivo;
    Libro libros[200];
    Libro auxiliar;
    int cantidad = 0;
    int i, j;

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    while (cantidad < 200 &&
           fread(&libros[cantidad], sizeof(Libro), 1, archivo) == 1)
    {
        cantidad++;
    }

    fclose(archivo);

    for (i = 0; i < cantidad - 1; i++)
    {
        for (j = 0; j < cantidad - i - 1; j++)
        {
            if (strcmp(libros[j].titulo, libros[j + 1].titulo) > 0)
            {
                auxiliar = libros[j];
                libros[j] = libros[j + 1];
                libros[j + 1] = auxiliar;
            }
        }
    }

    printf("\n===== LIBROS ORDENADOS POR TITULO =====\n");

    for (i = 0; i < cantidad; i++)
    {
        printf("\nISBN: %s\n", libros[i].isbn);
        printf("Titulo: %s\n", libros[i].titulo);
        printf("Autor: %s\n", obtenerNombreAutor(libros[i].idAutor));
    }
}
