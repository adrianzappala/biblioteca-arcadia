#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "autores.h"
#include "libros.h"

#define ARCHIVO_LIBROS "libros.dat"

// Pila para guardar el historial de busquedas.
#define MAX_HISTORIAL 100

char historial[MAX_HISTORIAL][20];
int tope = -1;

// Agrega una busqueda a la pila.
void apilarBusqueda(char isbn[])
{
    if (tope < MAX_HISTORIAL - 1)
    {
        tope++;
        strcpy(historial[tope], isbn);
    }
}

// Muestra las busquedas desde la mas reciente.
void mostrarHistorialBusquedas(void)
{
    int i;

    printf("\n--- HISTORIAL DE BUSQUEDAS ---\n");

    if (tope == -1)
    {
        printf("Todavia no hay busquedas registradas.\n");
        return;
    }

    for (i = tope; i >= 0; i--)
    {
        printf("%d. ISBN: %s\n", tope - i + 1, historial[i]);
    }
}

// Busca un libro por ISBN y devuelve su posicion.
int buscarPosicion(char isbn[])
{
    FILE *archivo;
    Libro libro;
    int posicion = 0;

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
        return -1;

    while (fread(&libro, sizeof(Libro), 1, archivo))
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

// Agrega un libro al catalogo.
void agregarLibro(void)
{
    FILE *archivo;
    Libro libro;

    printf("\n--- AGREGAR LIBRO ---\n");

    printf("ISBN: ");
    scanf(" %19s", libro.isbn);

    if (buscarPosicion(libro.isbn) != -1)
    {
        printf("Ya existe un libro con ese ISBN.\n");
        return;
    }

    printf("Titulo: ");
    scanf(" %99[^\n]", libro.titulo);

    printf("Editorial: ");
    scanf(" %59[^\n]", libro.editorial);

    printf("ID del autor: ");
    scanf("%d", &libro.idAutor);

    printf("Anio de publicacion: ");
    scanf("%d", &libro.anioPublicacion);

    printf("Stock total: ");
    scanf("%d", &libro.stockTotal);

    libro.stockDisponible = libro.stockTotal;
    libro.descatalogado = 0;

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

// Modifica un libro existente.
void modificarLibro(void)
{
    FILE *archivo;
    Libro libro;
    char isbn[20];
    int posicion;

    printf("\n--- MODIFICAR LIBRO ---\n");
    printf("Ingrese el ISBN: ");
    scanf(" %19s", isbn);

    posicion = buscarPosicion(isbn);

    if (posicion == -1)
    {
        printf("No se encontro el libro.\n");
        return;
    }

    archivo = fopen(ARCHIVO_LIBROS, "rb+");

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fseek(archivo, posicion * sizeof(Libro), SEEK_SET);
    fread(&libro, sizeof(Libro), 1, archivo);

    printf("Nuevo titulo: ");
    scanf(" %99[^\n]", libro.titulo);

    printf("Nueva editorial: ");
    scanf(" %59[^\n]", libro.editorial);

    printf("Nuevo ID de autor: ");
    scanf("%d", &libro.idAutor);

    printf("Nuevo anio de publicacion: ");
    scanf("%d", &libro.anioPublicacion);

    printf("Nuevo stock total: ");
    scanf("%d", &libro.stockTotal);

    if (libro.descatalogado == 1)
        libro.stockDisponible = 0;
    else
        libro.stockDisponible = libro.stockTotal;

    fseek(archivo, posicion * sizeof(Libro), SEEK_SET);
    fwrite(&libro, sizeof(Libro), 1, archivo);

    fclose(archivo);

    printf("Libro modificado correctamente.\n");
}

// Lista todos los libros.
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

    printf("\n--- CATALOGO DE LIBROS ---\n");

    while (fread(&libro, sizeof(Libro), 1, archivo))
    {
        printf("\nISBN: %s\n", libro.isbn);
        printf("Titulo: %s\n", libro.titulo);
        printf("Editorial: %s\n", libro.editorial);
        printf("Autor: %s\n", obtenerNombreAutor(libro.idAutor));
        printf("Anio: %d\n", libro.anioPublicacion);
        printf("Stock total: %d\n", libro.stockTotal);
        printf("Stock disponible: %d\n", libro.stockDisponible);

        printf("Estado: %s\n",
               libro.descatalogado ? "DESCATALOGADO" : "En catalogo");
    }

    fclose(archivo);
}

// Busca un libro por ISBN.
void buscarLibro(void)
{
    FILE *archivo;
    Libro libro;
    char isbn[20];
    int posicion;

    printf("\n--- BUSCAR LIBRO POR ISBN ---\n");
    printf("Ingrese el ISBN: ");
    scanf(" %19s", isbn);
    apilarBusqueda(isbn);

    posicion = buscarPosicion(isbn);

    if (posicion == -1)
    {
        printf("No se encontro el libro.\n");
        return;
    }

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
        return;

    fseek(archivo, posicion * sizeof(Libro), SEEK_SET);
    fread(&libro, sizeof(Libro), 1, archivo);

    printf("\nISBN: %s\n", libro.isbn);
    printf("Titulo: %s\n", libro.titulo);
    printf("Editorial: %s\n", libro.editorial);
    printf("Autor: %s\n", obtenerNombreAutor(libro.idAutor));
    printf("Anio: %d\n", libro.anioPublicacion);
    printf("Stock total: %d\n", libro.stockTotal);
    printf("Stock disponible: %d\n", libro.stockDisponible);

    printf("Estado: %s\n",
           libro.descatalogado ? "DESCATALOGADO" : "En catalogo");

    fclose(archivo);
}

// Lista los libros que tienen ejemplares disponibles.
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

    printf("\n--- LIBROS DISPONIBLES ---\n");

    while (fread(&libro, sizeof(Libro), 1, archivo))
    {
        if (libro.stockDisponible > 0 && libro.descatalogado == 0)
        {
            printf("\n%s - %s\n", libro.isbn, libro.titulo);
            printf("Editorial: %s\n", libro.editorial);
            printf("Autor: %s\n", obtenerNombreAutor(libro.idAutor));
            printf("Stock disponible: %d\n", libro.stockDisponible);
            encontrados++;
        }
    }

    if (encontrados == 0)
        printf("No hay libros disponibles.\n");

    fclose(archivo);
}

// Devuelve la editorial inicial segun el autor.
char *obtenerEditorialInicial(int idAutor)
{
    switch (idAutor)
    {
        case 1: return "Editorial Alma";
        case 2: return "Austral";
        case 3: return "Editorial Molino";
        case 4: return "Debolsillo";
        case 5: return "Debolsillo";
        case 6: return "Gredos";
        case 7: return "Catedra";
        case 8: return "Catedra";
        case 9: return "Plaza & Janes";
        case 10: return "Alianza Editorial";
        case 11: return "Catedra";
        case 12: return "Alba Editorial";
        default: return "Editorial no especificada";
    }
}

// Devuelve el anio de primera publicacion de cada obra.
int obtenerAnioPublicacionInicial(char titulo[])
{
    static const struct {
        char titulo[120];
        int anio;
    } anios[] = {
        {"El cuervo", 1845},
        {"El corazon delator", 1843},
        {"El gato negro", 1843},
        {"La caida de la casa Usher", 1839},
        {"Los crimenes de la calle Morgue", 1841},
        {"El escarabajo de oro", 1843},
        {"El pozo y el pendulo", 1842},
        {"La carta robada", 1844},
        {"La mascara de la Muerte Roja", 1842},
        {"Eureka", 1848},

        {"Hamlet", 1600},
        {"Romeo y Julieta", 1597},
        {"Macbeth", 1606},
        {"Otelo", 1603},
        {"El rey Lear", 1606},
        {"Sueno de una noche de verano", 1595},
        {"El mercader de Venecia", 1596},
        {"Mucho ruido y pocas nueces", 1598},
        {"La tempestad", 1611},
        {"Sonetos", 1609},

        {"Viaje al centro de la Tierra", 1864},
        {"Veinte mil leguas de viaje submarino", 1870},
        {"La vuelta al mundo en ochenta dias", 1872},
        {"De la Tierra a la Luna", 1865},
        {"La isla misteriosa", 1874},
        {"Miguel Strogoff", 1876},
        {"Cinco semanas en globo", 1863},
        {"Los hijos del capitan Grant", 1867},
        {"Robur el conquistador", 1886},
        {"El faro del fin del mundo", 1905},

        {"Ficciones", 1944},
        {"El Aleph", 1949},
        {"El libro de arena", 1975},
        {"Historia universal de la infamia", 1935},
        {"El informe de Brodie", 1970},
        {"La muerte y la brujula", 1942},
        {"Fervor de Buenos Aires", 1923},
        {"El hacedor", 1960},
        {"Otras inquisiciones", 1952},
        {"El libro de los seres imaginarios", 1957},

        {"El viejo y el mar", 1952},
        {"Por quien doblan las campanas", 1940},
        {"Adios a las armas", 1929},
        {"Fiesta (Tambien sale el sol)", 1926},
        {"Paris era una fiesta", 1964},
        {"Las nieves del Kilimanjaro", 1936},
        {"Hombres sin mujeres", 1927},
        {"En nuestro tiempo", 1925},
        {"Muerte en la tarde", 1932},
        {"El ganador no se lleva nada", 1933},

        {"La Iliada", -750},
        {"La Odisea", -700},

        {"Romancero gitano", 1928},
        {"Poeta en Nueva York", 1940},
        {"Bodas de sangre", 1933},
        {"La casa de Bernarda Alba", 1945},
        {"Yerma", 1934},
        {"Mariana Pineda", 1927},
        {"Dona Rosita la soltera", 1935},
        {"Libro de poemas", 1921},
        {"Poema del cante jondo", 1931},
        {"Asi que pasen cinco anos", 1931},

        {"Don Quijote de la Mancha", 1605},
        {"Novelas ejemplares", 1613},
        {"La Galatea", 1585},
        {"Los trabajos de Persiles y Sigismunda", 1617},
        {"Rinconete y Cortadillo", 1613},
        {"El coloquio de los perros", 1613},
        {"La gitanilla", 1613},
        {"El retablo de las maravillas", 1615},
        {"La Numancia", 1585},
        {"El viaje del Parnaso", 1614},

        {"It (Eso)", 1986},
        {"El resplandor", 1977},
        {"Carrie", 1974},
        {"Cementerio de animales", 1983},
        {"Misery", 1987},
        {"La milla verde", 1996},
        {"La zona muerta", 1979},
        {"La larga marcha", 1979},
        {"La niebla", 1980},
        {"22/11/63", 2011},

        {"Crimen y castigo", 1866},
        {"Los hermanos Karamazov", 1880},
        {"El idiota", 1869},
        {"Los demonios", 1872},
        {"El jugador", 1867},
        {"Noches blancas", 1848},
        {"Memorias del subsuelo", 1864},
        {"El doble", 1846},
        {"Pobres gentes", 1846},
        {"El sueno de un hombre ridiculo", 1877},

        {"Casa de munecas", 1879},
        {"Hedda Gabler", 1890},
        {"Un enemigo del pueblo", 1882},
        {"Espectros", 1881},
        {"Peer Gynt", 1867},
        {"El pato silvestre", 1884},
        {"La dama del mar", 1888},
        {"Rosmersholm", 1886},
        {"Brand", 1866},
        {"El maestro constructor", 1892},

        {"Guerra y paz", 1869},
        {"Ana Karenina", 1878},
        {"La muerte de Ivan Ilich", 1886},
        {"Resurreccion", 1899},
        {"La sonata a Kreutzer", 1889},
        {"Hadji Murat", 1912},
        {"Los cosacos", 1863},
        {"Infancia", 1852},
        {"La felicidad conyugal", 1859},
        {"Cuanta tierra necesita un hombre", 1886}
    };

    int i;
    int cantidad = sizeof(anios) / sizeof(anios[0]);

    for (i = 0; i < cantidad; i++)
    {
        if (strcmp(titulo, anios[i].titulo) == 0)
            return anios[i].anio;
    }

    return 0;
}

// Carga las obras iniciales al catalogo.
void cargarObrasIniciales(void)
{
    FILE *archivo;
    Libro libro;
    Libro libroExistente;
    int i;
    int existeRabia = 0;

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo != NULL)
    {
        if (fread(&libroExistente, sizeof(Libro), 1, archivo) == 1)
        {
            printf("El catalogo ya tiene libros cargados.\n");
            fclose(archivo);
            return;
        }

        fclose(archivo);
    }

    archivo = fopen(ARCHIVO_LIBROS, "ab");

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo de libros.\n");
        return;
    }

    for (i = 0; i < cantidadObras; i++)
    {
        memset(&libro, 0, sizeof(Libro));

        sprintf(libro.isbn, "ARC%04d", i + 1);
        strcpy(libro.titulo, obras[i].titulo);
        strcpy(libro.editorial, obtenerEditorialInicial(obras[i].idAutor));

        libro.idAutor = obras[i].idAutor;
        libro.anioPublicacion =
            obtenerAnioPublicacionInicial(obras[i].titulo);

        libro.stockTotal = 3;
        libro.stockDisponible = 3;
        libro.descatalogado = 0;

        if (strcmp(obras[i].titulo, "Rabia") == 0 &&
            obras[i].idAutor == 9)
        {
            libro.descatalogado = 1;
            libro.stockDisponible = 0;
            existeRabia = 1;
        }

        fwrite(&libro, sizeof(Libro), 1, archivo);
    }

    // Rabia no esta incluida actualmente en el arreglo obras[].
    if (!existeRabia)
    {
        memset(&libro, 0, sizeof(Libro));

        sprintf(libro.isbn, "ARC%04d", cantidadObras + 1);
        strcpy(libro.titulo, "Rabia");
        strcpy(libro.editorial, "Plaza & Janes");

        libro.idAutor = 9;
        libro.anioPublicacion = 1977;
        libro.stockTotal = 0;
        libro.stockDisponible = 0;
        libro.descatalogado = 1;

        fwrite(&libro, sizeof(Libro), 1, archivo);
    }

    fclose(archivo);

    printf("Se cargaron %d obras al catalogo.\n",
           cantidadObras + (existeRabia ? 0 : 1));
}

// Busca libros por titulo.
void buscarLibroPorTitulo(void)
{
    FILE *archivo;
    Libro libro;
    char titulo[100];
    int encontrados = 0;

    printf("\nIngrese el titulo o parte del titulo: ");
    scanf(" %99[^\n]", titulo);

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\n--- RESULTADOS ---\n");

    while (fread(&libro, sizeof(Libro), 1, archivo))
    {
        if (strstr(libro.titulo, titulo) != NULL)
        {
            printf("%s - %s\n", libro.isbn, libro.titulo);
            encontrados++;
        }
    }

    if (encontrados == 0)
        printf("No se encontraron libros.\n");

    fclose(archivo);
}

// Busca libros por autor.
void buscarLibrosPorAutor(void)
{
    FILE *archivo;
    Libro libro;
    int idAutor;
    int encontrados = 0;

    printf("\nIngrese el ID del autor: ");
    scanf("%d", &idAutor);

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\n--- LIBROS DEL AUTOR ---\n");

    while (fread(&libro, sizeof(Libro), 1, archivo))
    {
        if (libro.idAutor == idAutor)
        {
            printf("%s - %s\n", libro.isbn, libro.titulo);
            encontrados++;
        }
    }

    if (encontrados == 0)
        printf("No se encontraron libros de ese autor.\n");

    fclose(archivo);
}

// Comprueba si un texto contiene otro sin distinguir mayusculas.
int contieneTexto(char texto[], char busqueda[])
{
    char textoCopia[150];
    char busquedaCopia[150];
    int i;

    strcpy(textoCopia, texto);
    strcpy(busquedaCopia, busqueda);

    for (i = 0; textoCopia[i] != '\0'; i++)
        textoCopia[i] = (char)tolower((unsigned char)textoCopia[i]);

    for (i = 0; busquedaCopia[i] != '\0'; i++)
        busquedaCopia[i] = (char)tolower((unsigned char)busquedaCopia[i]);

    return strstr(textoCopia, busquedaCopia) != NULL;
}

// Busca libros por genero.
void buscarLibrosPorGenero(void)
{
    FILE *archivo;
    Libro libro;
    char genero[100];
    int encontrados = 0;

    printf("\nIngrese el genero: ");
    scanf(" %99[^\n]", genero);

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\n--- LIBROS POR GENERO ---\n");

    while (fread(&libro, sizeof(Libro), 1, archivo))
    {
        int i;

        for (i = 0; i < cantidadObras; i++)
        {
            if (strcmp(obras[i].titulo, libro.titulo) == 0 &&
                contieneTexto(obras[i].tipo, genero))
            {
                printf("%s - %s\n", libro.isbn, libro.titulo);
                encontrados++;
                break;
            }
        }
    }

    if (encontrados == 0)
        printf("No se encontraron libros de ese genero.\n");

    fclose(archivo);
}

// Busca libros por anio.
void buscarLibrosPorAnio(void)
{
    FILE *archivo;
    Libro libro;
    int anio;
    int encontrados = 0;

    printf("\nIngrese el anio: ");
    scanf("%d", &anio);

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\n--- LIBROS POR ANIO ---\n");

    while (fread(&libro, sizeof(Libro), 1, archivo))
    {
        if (libro.anioPublicacion == anio)
        {
            printf("%s - %s\n", libro.isbn, libro.titulo);
            encontrados++;
        }
    }

    if (encontrados == 0)
        printf("No se encontraron libros de ese anio.\n");

    fclose(archivo);
}

// Busca libros por inicial.
void buscarLibrosPorInicial(void)
{
    FILE *archivo;
    Libro libro;
    char inicial;
    int encontrados = 0;

    printf("\nIngrese la inicial: ");
    scanf(" %c", &inicial);

    inicial = (char)toupper((unsigned char)inicial);

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\n--- LIBROS POR INICIAL ---\n");

    while (fread(&libro, sizeof(Libro), 1, archivo))
    {
        if (toupper((unsigned char)libro.titulo[0]) == inicial)
        {
            printf("%s - %s\n", libro.isbn, libro.titulo);
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
    Libro libro;
    Libro libros[200];
    int cantidad = 0;
    int i, j;
    Libro auxiliar;

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    while (fread(&libro, sizeof(Libro), 1, archivo) && cantidad < 200)
    {
        libros[cantidad] = libro;
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

    printf("\n--- CATALOGO ORDENADO POR TITULO ---\n");

    for (i = 0; i < cantidad; i++)
    {
        printf("%s - %s\n", libros[i].isbn, libros[i].titulo);
    }
}

// Muestra el resumen de stock de libros por autor utilizando una matriz.
void mostrarResumenStockAutores(void)
{
    FILE *archivo;
    Libro libro;
    int resumen[12][2] = {0};
    int i;

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    while (fread(&libro, sizeof(Libro), 1, archivo))
    {
        if (libro.idAutor >= 1 && libro.idAutor <= 12)
        {
            resumen[libro.idAutor - 1][0] += libro.stockTotal;
            resumen[libro.idAutor - 1][1] += libro.stockDisponible;
        }
    }

    fclose(archivo);

    printf("\n--- RESUMEN DE STOCK POR AUTOR ---\n");

    for (i = 0; i < 12; i++)
    {
        printf("\nAutor: %s\n", obtenerNombreAutor(i + 1));
        printf("Stock total: %d\n", resumen[i][0]);
        printf("Stock disponible: %d\n", resumen[i][1]);
    }
}

// Carga los libros utilizando memoria dinamica.
void listarLibrosMemoriaDinamica(void)
{
    FILE *archivo;
    Libro *libros;
    Libro libro;
    int cantidad = 0;
    int i;

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    // Cuenta la cantidad de libros.
    while (fread(&libro, sizeof(Libro), 1, archivo))
    {
        cantidad++;
    }

    if (cantidad == 0)
    {
        printf("El catalogo esta vacio.\n");
        fclose(archivo);
        return;
    }

    // Reserva memoria segun la cantidad de libros.
    libros = (Libro *) malloc(cantidad * sizeof(Libro));

    if (libros == NULL)
    {
        printf("No se pudo reservar memoria.\n");
        fclose(archivo);
        return;
    }

    // Vuelve al inicio del archivo.
    rewind(archivo);

    // Carga los libros en memoria.
    for (i = 0; i < cantidad; i++)
    {
        fread(&libros[i], sizeof(Libro), 1, archivo);
    }

    fclose(archivo);

    printf("\n--- LIBROS CARGADOS EN MEMORIA DINAMICA ---\n");

    for (i = 0; i < cantidad; i++)
    {
        printf("%s - %s\n", libros[i].isbn, libros[i].titulo);
    }

    printf("\nCantidad de libros: %d\n", cantidad);

    // Libera la memoria reservada.
    free(libros);
}

// Muestra los libros utilizando recursividad.
void mostrarLibrosRecursivos(Libro libros[], int cantidad, int posicion)
{
    // Condicion de finalizacion.
    if (posicion >= cantidad)
        return;

    printf("%s - %s\n",
           libros[posicion].isbn,
           libros[posicion].titulo);

    // Llamada recursiva.
    mostrarLibrosRecursivos(libros, cantidad, posicion + 1);
}

// Carga los libros y los muestra recursivamente.
void listarLibrosRecursivo(void)
{
    FILE *archivo;
    Libro libro;
    Libro *libros;
    int cantidad = 0;
    int i;

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    while (fread(&libro, sizeof(Libro), 1, archivo))
        cantidad++;

    if (cantidad == 0)
    {
        printf("El catalogo esta vacio.\n");
        fclose(archivo);
        return;
    }

    libros = (Libro *) malloc(cantidad * sizeof(Libro));

    if (libros == NULL)
    {
        printf("No se pudo reservar memoria.\n");
        fclose(archivo);
        return;
    }

    rewind(archivo);

    for (i = 0; i < cantidad; i++)
        fread(&libros[i], sizeof(Libro), 1, archivo);

    fclose(archivo);

    printf("\n--- CATALOGO CON RECORRIDO RECURSIVO ---\n");

    mostrarLibrosRecursivos(libros, cantidad, 0);

    free(libros);
}

// Recomienda libros segun el autor elegido.
void recomendarLibros(void)
{
    FILE *archivo;
    Libro libro;
    int idAutor;
    int encontrados = 0;

    printf("\n--- SISTEMA DE RECOMENDACIONES ---\n");

    listarAutores();

    printf("\nIngrese el ID del autor que le interesa: ");
    scanf("%d", &idAutor);

    archivo = fopen(ARCHIVO_LIBROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\n--- LIBROS RECOMENDADOS ---\n");

    while (fread(&libro, sizeof(Libro), 1, archivo))
    {
        if (libro.idAutor == idAutor &&
            libro.stockDisponible > 0 &&
            libro.descatalogado == 0)
        {
            printf("\n%s - %s\n", libro.isbn, libro.titulo);
            printf("Editorial: %s\n", libro.editorial);
            printf("Stock disponible: %d\n", libro.stockDisponible);

            encontrados++;
        }
    }

    if (encontrados == 0)
    {
        printf("No hay recomendaciones disponibles para ese autor.\n");
    }

    fclose(archivo);
}
