#ifndef AUTORES_H
#define AUTORES_H

typedef struct {
    int idAutor;
    char nombre[60];
    char pais[30];
    char especialidad[100];
} Autor;

typedef struct {
    int idAutor;
    char titulo[120];
    char tipo[100];
} Obra;

// Funciones del modulo de autores
void listarAutores(void);
void listarObrasAutor(int idAutor);

#endif
