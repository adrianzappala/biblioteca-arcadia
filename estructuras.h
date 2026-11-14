#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

typedef struct {
    char idSocio[10];
    char dni[15];
    char nombre[50];
    char telefono[20];
    char direccion[30];
    char estado[15];
    char usuario[20];
    char contrasenia[20];
} Socio;

typedef struct {
    char usuario[20];
    char contrasenia[20];
    char nombreEmpleado[50];
} UsuarioEmpleado;

#endif // ESTRUCTURAS_H_INCLUDED
