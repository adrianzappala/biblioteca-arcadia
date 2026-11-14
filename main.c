#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"

void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inicializarUsuarioAdmin()
{
    FILE *archivo = fopen("usuarios.dat", "rb");
    if (archivo == NULL)
    {
        archivo = fopen("usuarios.dat", "wb");
        if (archivo != NULL)
        {
            UsuarioEmpleado admin;
            strcpy(admin.usuario, "admin");
            strcpy(admin.contrasenia, "1234");
            strcpy(admin.nombreEmpleado, "Administrador Principal");

            fwrite(&admin, sizeof(UsuarioEmpleado), 1, archivo);
            fclose(archivo);
        }
    }
    else
    {
        fclose(archivo);
    }
}

int existeDni(const char dniBuscado[])
{
    FILE *archivo = fopen("socios.dat", "rb");
    if (archivo == NULL) return 0;

    Socio s;
    int encontrado = 0;
    while (fread(&s, sizeof(Socio), 1, archivo) == 1)
    {
        if (strcmp(s.dni, dniBuscado) == 0)
        {
            encontrado = 1;
            break;
        }
    }
    fclose(archivo);
    return encontrado;
}

void registrarSocio()
{
    Socio nuevoSocio;

    printf("\n--- REGISTRO DE NUEVO SOCIO ---\n");
    printf("Ingrese ID de socio (ej: S01): ");
    scanf("%s", nuevoSocio.idSocio);

    printf("Ingrese DNI: ");
    scanf("%s", nuevoSocio.dni);

    if (existeDni(nuevoSocio.dni))
    {
        printf("¡Error! Ya existe un socio registrado con el DNI %s.\n", nuevoSocio.dni);
        return;
    }

    limpiarBuffer();

    printf("Ingrese Nombre y Apellido: ");
    fgets(nuevoSocio.nombre, sizeof(nuevoSocio.nombre), stdin);
    nuevoSocio.nombre[strcspn(nuevoSocio.nombre, "\n")] = 0;

    printf("Ingrese Telefono: ");
    scanf("%s", nuevoSocio.telefono);

    printf("Ingrese Direccion: ");
    scanf("%s", nuevoSocio.direccion);

    printf("Ingrese Nombre de Usuario para el Socio: ");
    scanf("%s", nuevoSocio.usuario);
    limpiarBuffer();

    printf("Ingrese Contrasenia para el Socio: ");
    scanf("%s", nuevoSocio.contrasenia);
    limpiarBuffer();

    strcpy(nuevoSocio.estado, "Activo");
    strcpy(nuevoSocio.estado, "Activo");


    FILE *archivo = fopen("socios.dat", "ab");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fwrite(&nuevoSocio, sizeof(Socio), 1, archivo);
    fclose(archivo);

    printf("¡Socio guardado con exito en 'socios.dat'!\n");
}


void listarSocios()
{
    FILE *archivo = fopen("socios.dat", "rb");
    if (archivo == NULL)
    {
        printf("\nAun no hay socios registrados.\n");
        return;
    }

    Socio s;
    printf("\n--- LISTA DE SOCIOS ---\n");
    while (fread(&s, sizeof(Socio), 1, archivo) == 1)
    {
        printf("ID: %s | DNI: %s | Nombre: %s | Estado: %s\n",
               s.idSocio, s.dni, s.nombre, s.estado);
    }
    fclose(archivo);
}

void buscarSocioPorId()
{
    char idBuscado[10];
    printf("\n--- BUSCAR SOCIO POR ID ---\n");
    printf("Ingrese el ID del socio a buscar (ej: S01): ");
    scanf("%s", idBuscado);
    limpiarBuffer();

    FILE *archivo = fopen("socios.dat", "rb");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo de socios (o aun no hay registros).\n");
        return;
    }

    Socio s;
    int encontrado = 0;
    while (fread(&s, sizeof(Socio), 1, archivo) == 1)
    {
        if (strcmp(s.idSocio, idBuscado) == 0)
        {
            encontrado = 1;
            printf("\n¡Socio encontrado!\n");
            printf("----------------------------------------\n");
            printf("ID de Socio : %s\n", s.idSocio);
            printf("DNI         : %s\n", s.dni);
            printf("Nombre      : %s\n", s.nombre);
            printf("Telefono    : %s\n", s.telefono);
            printf("Direccion   : %s\n", s.direccion);
            printf("Estado      : %s\n", s.estado);
            printf("----------------------------------------\n");
            break;
        }
    }

    if (!encontrado)
    {
        printf("No se encontro ningun socio con el ID '%s'.\n", idBuscado);
    }

    fclose(archivo);
}


void buscarSocioPorDni()
{
    char dniBuscado[15];
    printf("\n--- BUSCAR SOCIO POR DNI ---\n");
    printf("Ingrese el DNI a buscar: ");
    scanf("%s", dniBuscado);
    limpiarBuffer();

    FILE *archivo = fopen("socios.dat", "rb");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo de socios.\n");
        return;
    }

    Socio s;
    int encontrado = 0;
    while (fread(&s, sizeof(Socio), 1, archivo) == 1)
    {
        if (strcmp(s.dni, dniBuscado) == 0)
        {
            encontrado = 1;
            printf("\n¡Socio encontrado!\n");
            printf("----------------------------------------\n");
            printf("ID de Socio : %s\n", s.idSocio);
            printf("DNI         : %s\n", s.dni);
            printf("Nombre      : %s\n", s.nombre);
            printf("Telefono    : %s\n", s.telefono);
            printf("Direccion   : %s\n", s.direccion);
            printf("Estado      : %s\n", s.estado);
            printf("----------------------------------------\n");
            break;
        }
    }

    if (!encontrado)
    {
        printf("No se encontro ningun socio con el DNI '%s'.\n", dniBuscado);
    }

    fclose(archivo);
}

void modificarSocio()
{
    char idBuscado[10];
    printf("\n--- MODIFICAR DATOS DE SOCIO ---\n");
    printf("Ingrese el ID del socio a modificar: ");
    scanf("%s", idBuscado);
    limpiarBuffer();

    FILE *archivo = fopen("socios.dat", "rb");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo de socios.\n");
        return;
    }


    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL)
    {
        printf("Error al crear archivo temporal.\n");
        fclose(archivo);
        return;
    }

    Socio s;
    int encontrado = 0;

    while (fread(&s, sizeof(Socio), 1, archivo) == 1)
    {
        if (strcmp(s.idSocio, idBuscado) == 0)
        {
            encontrado = 1;
            printf("\nSocio encontrado: %s\n", s.nombre);
            printf("Ingrese nuevo telefono: ");
            scanf("%s", s.telefono);
            limpiarBuffer();

            printf("Ingrese nueva direccion: ");
            scanf("%s", s.direccion);
            limpiarBuffer();

            printf("¡Datos actualizados con exito!\n");
        }
        fwrite(&s, sizeof(Socio), 1, temp);
    }

    fclose(archivo);
    fclose(temp);

    remove("socios.dat");
    rename("temp.dat", "socios.dat");

    if (!encontrado)
    {
        printf("No se encontro ningun socio con el ID '%s'.\n", idBuscado);
    }
}

void cambiarEstadoSocio()
{
    char idBuscado[10];
    printf("\n--- CAMBIAR ESTADO DE SOCIO (Activo / Suspendido) ---\n");
    printf("Ingrese el ID del socio: ");
    scanf("%s", idBuscado);
    limpiarBuffer();

    FILE *archivo = fopen("socios.dat", "rb");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo de socios.\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL)
    {
        printf("Error al crear archivo temporal.\n");
        fclose(archivo);
        return;
    }

    Socio s;
    int encontrado = 0;

    while (fread(&s, sizeof(Socio), 1, archivo) == 1)
    {
        if (strcmp(s.idSocio, idBuscado) == 0)
        {
            encontrado = 1;
            printf("\nSocio: %s | Estado actual: %s\n", s.nombre, s.estado);

            if (strcmp(s.estado, "Activo") == 0)
            {
                strcpy(s.estado, "Suspendido");
                printf("El socio ha sido SUSPENDIDO.\n");
            }
            else
            {
                strcpy(s.estado, "Activo");
                printf("El socio ha sido REACTIVADO.\n");
            }
        }
        fwrite(&s, sizeof(Socio), 1, temp);
    }

    fclose(archivo);
    fclose(temp);

    remove("socios.dat");
    rename("temp.dat", "socios.dat");

    if (!encontrado)
    {
        printf("No se encontro ningun socio con el ID '%s'.\n", idBuscado);
    }
}
int iniciarSesion(char nombreLogueado[])
{
    char user[20];
    char pass[20];

    printf("\n=============================\n");
    printf("   BIBLIOTECA ARCADIA - LOGIN\n");
    printf("=============================\n");
    printf("Usuario: ");
    scanf("%s", user);
    limpiarBuffer();

    printf("Contrasenia: ");
    scanf("%s", pass);
    limpiarBuffer();

    FILE *archEmp = fopen("usuarios.dat", "rb");
    if (archEmp != NULL)
    {
        UsuarioEmpleado emp;
        while (fread(&emp, sizeof(UsuarioEmpleado), 1, archEmp) == 1)
        {
            if (strcmp(emp.usuario, user) == 0 && strcmp(emp.contrasenia, pass) == 0)
            {
                strcpy(nombreLogueado, emp.nombreEmpleado);
                fclose(archEmp);
                return 1; // Rol 1: Empleado
            }
        }
        fclose(archEmp);
    }

    FILE *archSoc = fopen("socios.dat", "rb");
    if (archSoc != NULL)
    {
        Socio s;
        while (fread(&s, sizeof(Socio), 1, archSoc) == 1)
        {
            if (strcmp(s.usuario, user) == 0 && strcmp(s.contrasenia, pass) == 0)
            {
                if (strcmp(s.estado, "Suspendido") == 0)
                {
                    printf("\n[Aviso] Su cuenta se encuentra SUSPENDIDA. No puede iniciar sesion.\n");
                    fclose(archSoc);
                    return 0;
                }
                strcpy(nombreLogueado, s.nombre);
                fclose(archSoc);
                return 2;
            }
            fclose(archSoc);
        }

        printf("\n[Error] Usuario o contrasenia incorrectos.\n");
        return 0;
    }
}
    int main()
    {
        inicializarUsuarioAdmin();

        int rol = 0;
        char nombreUsuario[50];

        while (rol == 0)
        {
            rol = iniciarSesion(nombreUsuario);
        }

        if (rol == 1)
        {
            int opcion;
            do
            {
                printf("\n=====================================\n");
                printf("   PANEL DE EMPLEADO: %s\n", nombreUsuario);
                printf("=====================================\n");
                printf("1. Registrar nuevo socio\n");
                printf("2. Ver listado de socios\n");
                printf("3. Buscar socio por ID\n");
                printf("4. Buscar socio por DNI\n");
                printf("5. Modificar datos de socio\n");
                printf("6. Suspender / Reactivar socio\n");
                printf("0. Cerrar sesion\n");
                printf("Seleccione una opcion: ");

                if (scanf("%d", &opcion) != 1)
                {
                    limpiarBuffer();
                    continue;
                }
                limpiarBuffer();

                switch(opcion)
                {
                case 1:
                    registrarSocio();
                    break;
                case 2:
                    listarSocios();
                    break;
                case 3:
                    buscarSocioPorId();
                    break;
                case 4:
                    buscarSocioPorDni();
                    break;
                case 5:
                    modificarSocio();
                    break;
                case 6:
                    cambiarEstadoSocio();
                    break;
                case 0:
                    printf("Cerrando sesion...\n");
                    break;
                default:
                    printf("Opcion invalida.\n");
                }
            }
            while(opcion != 0);
        }

        else if (rol == 2)
        {
            int opcion;
            do
            {
                printf("\n=====================================\n");
                printf("   BIENVENIDO SOCIO/A: %s\n", nombreUsuario);
                printf("=====================================\n");
                printf("1. Ver mis datos personales\n");
                printf("2. Consultar libros disponibles (Catálogo)\n");
                printf("0. Cerrar sesion\n");
                printf("Seleccione una opcion: ");

                if (scanf("%d", &opcion) != 1)
                {
                    limpiarBuffer();
                    continue;
                }
                limpiarBuffer();

                switch(opcion)
                {
                case 1:
                    printf("\n--- MIS DATOS ---\n");
                    printf("Hola %s, tu cuenta esta activa.\n", nombreUsuario);
                    break;
                case 2:
                    printf("\n[Proximamente] Aqui podras ver el catalogo de libros de tu compañero Adrian.\n");
                    break;
                case 0:
                    printf("Cerrando sesion de socio...\n");
                    break;
                default:
                    printf("Opcion invalida.\n");
                }
            }
            while(opcion != 0);
        }

        return 0;
}
