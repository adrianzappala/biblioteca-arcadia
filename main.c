
#include <stdio.h>
#include <stdlib.h>
#include "autores.h"
#include "libros.h"

int main()
{
    int opcion;
    int idAutor;

    do
    {
        printf("\n===== BIBLIOTECA ARCADIA =====\n");
        printf("1. Agregar libro\n");
        printf("2. Modificar libro\n");
        printf("3. Listar libros\n");
        printf("4. Buscar libro por ISBN\n");
        printf("5. Listar libros disponibles\n");
        printf("6. Listar autores\n");
        printf("7. Consultar obras de un autor\n");
        printf("8. Cargar obras iniciales al catalogo\n");
        printf("9. Buscar libro por titulo\n");
        printf("10. Buscar libros por autor\n");
        printf("11. Buscar libros por genero\n");
        printf("12. Buscar libros por anio\n");
        printf("13. Buscar libros por inicial\n");
        printf("14. Listar libros ordenados alfabeticamente\n");
        printf("15. Mostrar historial de busquedas\n");
        printf("16. Resumen de stock por autor\n");
        printf("17. Listar libros con memoria dinamica\n");
        printf("18. Listar libros recursivamente\n");
        printf("19. Sistema de recomendaciones\n");
        printf("0. Salir\n");
        printf("\nSeleccione una opcion: ");


        scanf("%d", &opcion);

        switch (opcion)
        {
            case 1:
                agregarLibro();
                break;

            case 2:
                modificarLibro();
                break;

            case 3:
                listarLibros();
                break;

            case 4:
                buscarLibro();
                break;

            case 5:
                listarLibrosDisponibles();
                break;

            case 6:
                listarAutores();
                break;

            case 7:
                printf("Ingrese el ID del autor: ");
                scanf("%d", &idAutor);
                listarObrasAutor(idAutor);
                break;

            case 8:
                cargarObrasIniciales();
                break;

            case 9:
                buscarLibroPorTitulo();
                break;

            case 10:
                buscarLibrosPorAutor();
                break;

            case 11:
                buscarLibrosPorGenero();
                break;

            case 12:
                buscarLibrosPorAnio();
                break;

            case 13:
                buscarLibrosPorInicial();
                break;

            case 14:
                listarLibrosOrdenados();
                break;

            case 15:
                mostrarHistorialBusquedas();
                break;

           case 16:
               mostrarResumenStockAutores();
               break;

           case 17:
               listarLibrosMemoriaDinamica();
               break;

           case 18:
               listarLibrosRecursivo();
               break;

           case 19:
               recomendarLibros();
               break;

            case 0:
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("Opcion incorrecta.\n");
        }

    } while (opcion != 0);

    return 0;
}
