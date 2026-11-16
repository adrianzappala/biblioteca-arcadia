#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "prestamos.h"

// Modulo de prestamos: se guardan en "prestamos.dat" y nunca se borran.

static void limpiarEntrada(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Devuelve 1 si el socio esta activo, 0 si esta suspendido y -1 si no existe.
static int estadoSocio(const char idSocio[])
{
    FILE *archivo = fopen("socios.dat", "rb");
    Socio s;

    if (archivo == NULL)
    {
        return -1;
    }
    while (fread(&s, sizeof(Socio), 1, archivo) == 1)
    {
        if (strcmp(s.idSocio, idSocio) == 0)
        {
            fclose(archivo);
            return strcmp(s.estado, "Activo") == 0;
        }
    }
    fclose(archivo);
    return -1;
}

// Como los prestamos no se borran, el proximo ID es cantidad de registros + 1.
static int siguienteId(void)
{
    FILE *archivo = fopen("prestamos.dat", "rb");
    long bytes;

    if (archivo == NULL)
    {
        return 1;
    }
    fseek(archivo, 0, SEEK_END);
    bytes = ftell(archivo);
    fclose(archivo);
    return (int)(bytes / sizeof(Prestamo)) + 1;
}

void registrarPrestamo(void)
{
    Prestamo p;
    FILE *archivo;
    int estado, stock;

    memset(&p, 0, sizeof(Prestamo));
    printf("\n--- REGISTRAR PRESTAMO ---\n");
    printf("ID de socio: ");
    scanf("%9s", p.idSocio);
    printf("ISBN del libro: ");
    scanf("%19s", p.isbn);
    limpiarEntrada();

    estado = estadoSocio(p.idSocio);
    if (estado == -1)
    {
        printf("No existe un socio con ese ID.\n");
        return;
    }
    if (estado == 0)
    {
        printf("El socio esta suspendido.\n");
        return;
    }

    stock = catalogoStockDisponible(p.isbn);
    if (stock < 0)
    {
        printf("No existe un libro con ese ISBN.\n");
        return;
    }
    if (stock == 0)
    {
        printf("No hay ejemplares disponibles.\n");
        return;
    }

    p.idPrestamo = siguienteId();
    p.fechaPrestamo = time(NULL);
    p.fechaVencimiento = p.fechaPrestamo + DIAS_PRESTAMO * 24 * 60 * 60;

    archivo = fopen("prestamos.dat", "ab");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }
    fwrite(&p, sizeof(Prestamo), 1, archivo);
    fclose(archivo);

    catalogoModificarStock(p.isbn, -1);
    printf("Prestamo %d registrado. Vence en %d dias.\n", p.idPrestamo, DIAS_PRESTAMO);
}

void registrarDevolucion(void)
{
    FILE *archivo = fopen("prestamos.dat", "r+b");
    Prestamo p;
    int id, encontrado = 0;

    printf("\n--- REGISTRAR DEVOLUCION ---\n");
    printf("ID del prestamo: ");
    if (scanf("%d", &id) != 1)
    {
        limpiarEntrada();
        printf("El ID debe ser un numero.\n");
        if (archivo != NULL) fclose(archivo);
        return;
    }
    limpiarEntrada();

    if (archivo == NULL)
    {
        printf("Aun no hay prestamos registrados.\n");
        return;
    }

    while (!encontrado && fread(&p, sizeof(Prestamo), 1, archivo) == 1)
    {
        if (p.idPrestamo == id)
        {
            encontrado = 1;
            if (p.devuelto)
            {
                printf("Ese prestamo ya fue devuelto.\n");
            }
            else
            {
                p.devuelto = 1;
                p.fechaDevolucion = time(NULL);
                fseek(archivo, -(long)sizeof(Prestamo), SEEK_CUR);
                fwrite(&p, sizeof(Prestamo), 1, archivo);
                catalogoModificarStock(p.isbn, 1);
                printf("Devolucion registrada.\n");
            }
        }
    }
    fclose(archivo);

    if (!encontrado)
    {
        printf("No existe un prestamo con ese ID.\n");
    }
}

// Lista prestamos segun el filtro. Si idSocio no es NULL, solo los de ese socio.
void listarPrestamos(int filtro, const char idSocio[])
{
    FILE *archivo = fopen("prestamos.dat", "rb");
    Prestamo p;
    time_t hoy = time(NULL);
    char prestado[11], vence[11];
    int cantidad = 0, mostrar;

    if (archivo == NULL)
    {
        printf("\nAun no hay prestamos registrados.\n");
        return;
    }

    printf("\n%-5s %-8s %-15s %-11s %-11s %s\n", "ID", "SOCIO", "ISBN", "PRESTADO", "VENCE", "ESTADO");
    while (fread(&p, sizeof(Prestamo), 1, archivo) == 1)
    {
        mostrar = (idSocio == NULL || strcmp(p.idSocio, idSocio) == 0);
        if (filtro == LISTAR_ACTIVOS && p.devuelto) mostrar = 0;
        if (filtro == LISTAR_DEVUELTOS && !p.devuelto) mostrar = 0;
        if (filtro == LISTAR_VENCIDOS && (p.devuelto || hoy <= p.fechaVencimiento)) mostrar = 0;

        if (mostrar)
        {
            strftime(prestado, sizeof(prestado), "%d/%m/%Y", localtime(&p.fechaPrestamo));
            strftime(vence, sizeof(vence), "%d/%m/%Y", localtime(&p.fechaVencimiento));
            printf("%-5d %-8s %-15s %-11s %-11s %s\n", p.idPrestamo, p.idSocio, p.isbn,
                   prestado, vence,
                   p.devuelto ? "Devuelto" : (hoy > p.fechaVencimiento ? "VENCIDO" : "Activo"));
            cantidad++;
        }
    }
    fclose(archivo);

    if (cantidad == 0)
    {
        printf("No hay prestamos para mostrar.\n");
    }
}

void menuPrestamos(void)
{
    int opcion;

    do
    {
        printf("\n=== PRESTAMOS ===\n");
        printf("1. Registrar prestamo\n");
        printf("2. Registrar devolucion\n");
        printf("3. Ver prestamos activos\n");
        printf("4. Ver prestamos devueltos\n");
        printf("5. Ver historial completo\n");
        printf("6. Ver prestamos vencidos\n");
        printf("0. Volver\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1)
        {
            limpiarEntrada();
            opcion = -1;
        }
        else
        {
            limpiarEntrada();
        }

        switch (opcion)
        {
        case 1: registrarPrestamo(); break;
        case 2: registrarDevolucion(); break;
        case 3: listarPrestamos(LISTAR_ACTIVOS, NULL); break;
        case 4: listarPrestamos(LISTAR_DEVUELTOS, NULL); break;
        case 5: listarPrestamos(LISTAR_TODOS, NULL); break;
        case 6: listarPrestamos(LISTAR_VENCIDOS, NULL); break;
        case 0: break;
        default: printf("Opcion invalida.\n");
        }
    }
    while (opcion != 0);
}
