#include <stdio.h>
#include <stdlib.h>
#include "autores.h"
#include "libros.h"
#include "socios.h"


int main()
{
    inicializarUsuarioAdmin();

    int rol = 0;
    char nombreUsuario[50];

    while (rol == 0)
    {
        rol = iniciarSesion(nombreUsuario);
    }
    
    int opcion;
    int idAutor;
if(rol==1
    do
        {
            printf("\n==========================================\n");
            printf("   BIBLIOTECA ARCADIA - PANEL EMPLEADO\n");
            printf("   Usuario: %s\n", nombreUsuario);
            printf("==========================================\n");
            printf("--- GESTION DE SOCIOS ---\n");
            printf("1. Registrar nuevo socio\n");
            printf("2. Ver listado de socios\n");
            printf("3. Buscar socio por ID\n");
            printf("4. Buscar socio por DNI\n");
            printf("5. Modificar datos de socio\n");
            printf("6. Suspender / Reactivar socio\n");
            printf("\n--- GESTION DE CATALOGO Y AUTORES ---\n");
            printf("7. Agregar libro\n");
            printf("8. Modificar libro\n");
            printf("9. Cargar obras iniciales al catalogo\n");
            printf("10. Listar libros\n");
            printf("11. Buscar libro por ISBN\n");
            printf("12. Listar libros disponibles\n");
            printf("13. Listar autores\n");
            printf("14. Consultar obras de un autor\n");
            printf("15. Buscar libro por titulo\n");
            printf("16. Buscar libros por autor\n");
            printf("17. Buscar libros por genero\n");
            printf("18. Buscar libros por anio\n");
            printf("19. Buscar libros por inicial\n");
            printf("20. Listar libros ordenados alfabeticamente\n");
            printf("0. Salir\n");
            printf("\nSeleccione una opcion: ");

            if (scanf("%d", &opcion) != 1)
            {
                limpiarBuffer();
                opcion = -1;
                continue;
            }
            limpiarBuffer();

            switch (opcion)
            {
                case 1: registrarSocio(); break;
                case 2: listarSocios(); break;
                case 3: buscarSocioPorId(); break;
                case 4: buscarSocioPorDni(); break;
                case 5: modificarSocio(); break;
                case 6: cambiarEstadoSocio(); break;

                case 7: agregarLibro(); break;
                case 8: modificarLibro(); break;
                case 9: cargarObrasIniciales(); break;
                case 10: listarLibros(); break;
                case 11: buscarLibro(); break;
                case 12: listarLibrosDisponibles(); break;
                case 13: listarAutores(); break;
                case 14:
                    printf("Ingrese el ID del autor: ");
                    scanf("%d", &idAutor);
                    limpiarBuffer();
                    listarObrasAutor(idAutor);
                    break;
                case 15: buscarLibroPorTitulo(); break;
                case 16: buscarLibrosPorAutor(); break;
                case 17: buscarLibrosPorGenero(); break;
                case 18: buscarLibrosPorAnio(); break;
                case 19: buscarLibrosPorInicial(); break;
                case 20: listarLibrosOrdenados(); break;

                case 0:
                    printf("Cerrando sesion y saliendo del sistema...\n");
                    break;
                default:
                    printf("Opcion incorrecta.\n");
            }
switch (opcion)
            {
                case 1: registrarSocio(); break;
                case 2: listarSocios(); break;
                case 3: buscarSocioPorId(); break;
                case 4: buscarSocioPorDni(); break;
                case 5: modificarSocio(); break;
                case 6: cambiarEstadoSocio(); break;

                case 7: agregarLibro(); break;
                case 8: modificarLibro(); break;
                case 9: cargarObrasIniciales(); break;
                case 10: listarLibros(); break;
                case 11: buscarLibro(); break;
                case 12: listarLibrosDisponibles(); break;
                case 13: listarAutores(); break;
                case 14:
                    printf("Ingrese el ID del autor: ");
                    scanf("%d", &idAutor);
                    limpiarBuffer();
                    listarObrasAutor(idAutor);
                    break;
                case 15: buscarLibroPorTitulo(); break;
                case 16: buscarLibrosPorAutor(); break;
                case 17: buscarLibrosPorGenero(); break;
                case 18: buscarLibrosPorAnio(); break;
                case 19: buscarLibrosPorInicial(); break;
                case 20: listarLibrosOrdenados(); break;

                case 0:
                    printf("Cerrando sesion y saliendo del sistema...\n");
                    break;
                default:
                    printf("Opcion incorrecta.\n");
            }

        } while (opcion != 0);
    }

    else if (rol == 2)
    {
        do
        {
            printf("\n=====================================\n");
            printf("   BIENVENIDO SOCIO/A: %s\n", nombreUsuario);
            printf("=====================================\n");
            printf("1. Ver mis datos personales\n");
            printf("2. Consultar libros disponibles (Catalogo)\n");
            printf("3. Buscar libro por titulo\n");
            printf("4. Buscar libros por autor\n");
            printf("5. Buscar libros por genero\n");
            printf("6. Listar todos los libros\n");
            printf("0. Cerrar sesion\n");
            printf("Seleccione una opcion: ");

            if (scanf("%d", &opcion) != 1)
            {
                limpiarBuffer();
                opcion = -1;
                continue;
            }
            limpiarBuffer();

            switch (opcion)
            {
                case 1:
                    verMisDatos(nombreUsuario);
                    break;
                case 2:
                    listarLibrosDisponibles();
                    break;
                case 3:
                    buscarLibroPorTitulo();
                    break;
                case 4:
                    buscarLibrosPorAutor();
                    break;
                case 5:
                    buscarLibrosPorGenero();
                    break;
                case 6:
                    listarLibros();
                    break;
                case 0:
                    printf("Cerrando sesion de socio...\n");
                    break;
                default:
                    printf("Opcion invalida.\n");
            }

        } while (opcion != 0);
    }

    return 0;
}
