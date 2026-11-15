#ifndef PRESTAMOS_H
#define PRESTAMOS_H

#include <time.h>

#define DIAS_PRESTAMO 15

typedef struct {
    int idPrestamo;
    char idSocio[10];
    char isbn[20];
    time_t fechaPrestamo;
    time_t fechaVencimiento;
    time_t fechaDevolucion;
    int devuelto;
} Prestamo;

enum { LISTAR_TODOS, LISTAR_ACTIVOS, LISTAR_DEVUELTOS, LISTAR_VENCIDOS };

// Funciones que tiene que dar el catalogo (Adrian)
// catalogoStockDisponible: stock del ISBN, o -1 si no existe
// catalogoModificarStock: suma delta (+1 / -1) al stock disponible
int catalogoStockDisponible(const char isbn[]);
int catalogoModificarStock(const char isbn[], int delta);

void registrarPrestamo(void);
void registrarDevolucion(void);
void listarPrestamos(int filtro, const char idSocio[]);
void menuPrestamos(void);

#endif
