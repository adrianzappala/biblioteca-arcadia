#ifndef LIBROS_H
#define LIBROS_H

typedef struct
{
    char isbn[20];
    char titulo[100];
    char editorial[60];
    int idAutor;
    int anioPublicacion;
    int stockTotal;
    int stockDisponible;
} Libro; Libro;

// Funciones del modulo de libros
void agregarLibro(void);
void modificarLibro(void);
void listarLibros(void);
void buscarLibro(void);
void listarLibrosDisponibles(void);
void cargarObrasIniciales(void);
void buscarLibroPorTitulo(void);
void buscarLibrosPorAutor(void);
void buscarLibrosPorGenero(void);
void buscarLibrosPorAnio(void);
void buscarLibrosPorInicial(void);
void listarLibrosOrdenados(void);

#endif
