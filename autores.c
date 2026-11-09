
#include <stdio.h>
#include "autores.h"

// ==================================================
// MODULO: AUTORES
// Contiene los datos de autores y sus obras, junto
// con las funciones para realizar consultas.
// ==================================================


// ==================================================
// ARREGLO DE AUTORES
// Almacena los autores registrados en el catalogo.
// Cada autor tiene un ID unico, nombre, pais y
// especialidad literaria.
// ==================================================

Autor autores[] = {
    {1, "Edgar Allan Poe", "Estados Unidos", "Terror, misterio y romanticismo oscuro"},
    {2, "William Shakespeare", "Inglaterra", "Teatro, tragedia, comedia y poesia"},
    {3, "Julio Verne", "Francia", "Ciencia ficcion, aventuras y exploracion"},
    {4, "Jorge Luis Borges", "Argentina", "Cuento fantastico, poesia y ensayo"},
    {5, "Ernest Hemingway", "Estados Unidos", "Novela, cuento, guerra y periodismo"},
    {6, "Homero", "Grecia antigua", "Poesia epica"},
    {7, "Federico Garcia Lorca", "Espana", "Poesia, teatro y tragedia"},
    {8, "Miguel de Cervantes", "Espana", "Novela, teatro y poesia"},
    {9, "Stephen King", "Estados Unidos", "Terror, suspenso y fantasia"},
    {10, "Fiodor Dostoievski", "Rusia", "Novela psicologica y filosofia"},
    {11, "Henrik Ibsen", "Noruega", "Teatro realista y drama social"},
    {12, "Leon Tolstoi", "Rusia", "Novela historica y realismo"}
};

// Calcula la cantidad de autores almacenados en el arreglo.
int cantidadAutores = sizeof(autores) / sizeof(autores[0]);


// ==================================================
// ARREGLO DE OBRAS
// Almacena las obras asociadas a cada autor mediante
// su ID. Cada registro contiene el ID del autor,
// el titulo de la obra y su tipo o genero literario.
// ==================================================

Obra obras[] = {

    // Edgar Allan Poe (ID 1)
    {1, "El cuervo", "Poesia"},
    {1, "El corazon delator", "Cuento de terror psicologico"},
    {1, "El gato negro", "Cuento de terror"},
    {1, "La caida de la casa Usher", "Cuento gotico"},
    {1, "Los crimenes de la calle Morgue", "Cuento policial"},
    {1, "El escarabajo de oro", "Cuento de misterio y aventuras"},
    {1, "El pozo y el pendulo", "Cuento de terror"},
    {1, "La carta robada", "Cuento policial"},
    {1, "La mascara de la Muerte Roja", "Cuento de terror gotico"},
    {1, "Eureka", "Ensayo filosofico y cosmologico"},

    // William Shakespeare (ID 2)
    {2, "Hamlet", "Tragedia"},
    {2, "Romeo y Julieta", "Tragedia romantica"},
    {2, "Macbeth", "Tragedia"},
    {2, "Otelo", "Tragedia"},
    {2, "El rey Lear", "Tragedia"},
    {2, "Sueno de una noche de verano", "Comedia fantastica"},
    {2, "El mercader de Venecia", "Drama y comedia"},
    {2, "Mucho ruido y pocas nueces", "Comedia romantica"},
    {2, "La tempestad", "Drama fantastico"},
    {2, "Sonetos", "Poesia lirica"},

    // Julio Verne (ID 3)
    {3, "Viaje al centro de la Tierra", "Ciencia ficcion y aventuras"},
    {3, "Veinte mil leguas de viaje submarino", "Ciencia ficcion y aventuras"},
    {3, "La vuelta al mundo en ochenta dias", "Novela de aventuras"},
    {3, "De la Tierra a la Luna", "Ciencia ficcion"},
    {3, "La isla misteriosa", "Aventuras y supervivencia"},
    {3, "Miguel Strogoff", "Novela de aventuras historicas"},
    {3, "Cinco semanas en globo", "Aventuras y exploracion"},
    {3, "Los hijos del capitan Grant", "Aventuras"},
    {3, "Robur el conquistador", "Ciencia ficcion"},
    {3, "El faro del fin del mundo", "Aventuras y misterio"},

    // Jorge Luis Borges (ID 4)
    {4, "Ficciones", "Cuentos fantasticos y filosoficos"},
    {4, "El Aleph", "Cuentos fantasticos"},
    {4, "El libro de arena", "Cuentos fantasticos"},
    {4, "Historia universal de la infamia", "Narrativa breve"},
    {4, "El informe de Brodie", "Cuentos"},
    {4, "La muerte y la brujula", "Cuento policial"},
    {4, "Fervor de Buenos Aires", "Poesia"},
    {4, "El hacedor", "Poesia y prosa"},
    {4, "Otras inquisiciones", "Ensayos"},
    {4, "El libro de los seres imaginarios", "Bestiario y literatura fantastica"},

    // Ernest Hemingway (ID 5)
    {5, "El viejo y el mar", "Novela corta"},
    {5, "Por quien doblan las campanas", "Novela belica"},
    {5, "Adios a las armas", "Novela romantica y belica"},
    {5, "Fiesta (Tambien sale el sol)", "Novela"},
    {5, "Paris era una fiesta", "Memorias"},
    {5, "Las nieves del Kilimanjaro", "Cuento"},
    {5, "Hombres sin mujeres", "Coleccion de cuentos"},
    {5, "En nuestro tiempo", "Cuentos"},
    {5, "Muerte en la tarde", "Ensayo sobre tauromaquia"},
    {5, "El ganador no se lleva nada", "Coleccion de cuentos"},

    // Homero (ID 6)
    {6, "La Iliada", "Poema epico y belico"},
    {6, "La Odisea", "Poema epico y de aventuras"},

    // Federico Garcia Lorca (ID 7)
    {7, "Romancero gitano", "Poesia"},
    {7, "Poeta en Nueva York", "Poesia surrealista"},
    {7, "Bodas de sangre", "Tragedia teatral"},
    {7, "La casa de Bernarda Alba", "Drama teatral"},
    {7, "Yerma", "Tragedia teatral"},
    {7, "Mariana Pineda", "Drama historico"},
    {7, "Dona Rosita la soltera", "Drama"},
    {7, "Libro de poemas", "Poesia"},
    {7, "Poema del cante jondo", "Poesia"},
    {7, "Asi que pasen cinco anos", "Teatro surrealista"},

    // Miguel de Cervantes (ID 8)
    {8, "Don Quijote de la Mancha", "Novela de aventuras y satira"},
    {8, "Novelas ejemplares", "Coleccion de novelas cortas"},
    {8, "La Galatea", "Novela pastoril"},
    {8, "Los trabajos de Persiles y Sigismunda", "Novela bizantina y de aventuras"},
    {8, "Rinconete y Cortadillo", "Novela picaresca"},
    {8, "El coloquio de los perros", "Novela dialogada y satirica"},
    {8, "La gitanilla", "Novela corta"},
    {8, "El retablo de las maravillas", "Entremes teatral"},
    {8, "La Numancia", "Tragedia historica"},
    {8, "El viaje del Parnaso", "Poesia narrativa y satira literaria"},

    // Stephen King (ID 9)
    {9, "It (Eso)", "Terror sobrenatural"},
    {9, "El resplandor", "Terror psicologico"},
    {9, "Carrie", "Terror sobrenatural"},
    {9, "Cementerio de animales", "Terror"},
    {9, "Misery", "Suspenso psicologico"},
    {9, "La milla verde", "Drama y fantasia sobrenatural"},
    {9, "La zona muerta", "Suspenso y ciencia ficcion"},
    {9, "La larga marcha", "Distopia y suspenso"},
    {9, "La niebla", "Terror y ciencia ficcion"},
    {9, "22/11/63", "Ciencia ficcion e historia alternativa"},

    // Fiodor Dostoievski (ID 10)
    {10, "Crimen y castigo", "Novela psicologica y policial"},
    {10, "Los hermanos Karamazov", "Novela filosofica"},
    {10, "El idiota", "Novela psicologica"},
    {10, "Los demonios", "Novela politica y filosofica"},
    {10, "El jugador", "Novela psicologica"},
    {10, "Noches blancas", "Novela corta romantica"},
    {10, "Memorias del subsuelo", "Novela filosofica"},
    {10, "El doble", "Novela psicologica y fantastica"},
    {10, "Pobres gentes", "Novela epistolar"},
    {10, "El sueno de un hombre ridiculo", "Cuento filosofico"},

    // Henrik Ibsen (ID 11)
    {11, "Casa de munecas", "Drama social"},
    {11, "Hedda Gabler", "Drama psicologico"},
    {11, "Un enemigo del pueblo", "Drama social y politico"},
    {11, "Espectros", "Drama psicologico y familiar"},
    {11, "Peer Gynt", "Drama poetico y fantastico"},
    {11, "El pato silvestre", "Drama realista"},
    {11, "La dama del mar", "Drama psicologico y simbolico"},
    {11, "Rosmersholm", "Drama psicologico y politico"},
    {11, "Brand", "Drama filosofico"},
    {11, "El maestro constructor", "Drama psicologico y simbolista"},

    // Leon Tolstoi (ID 12)
    {12, "Guerra y paz", "Novela historica y epica"},
    {12, "Ana Karenina", "Novela realista y romantica"},
    {12, "La muerte de Ivan Ilich", "Novela corta filosofica"},
    {12, "Resurreccion", "Novela social"},
    {12, "La sonata a Kreutzer", "Novela corta psicologica"},
    {12, "Hadji Murat", "Novela historica y belica"},
    {12, "Los cosacos", "Novela de aventuras y costumbres"},
    {12, "Infancia", "Novela autobiografica"},
    {12, "La felicidad conyugal", "Novela romantica"},
    {12, "Cuanta tierra necesita un hombre", "Cuento filosofico"}
};

// Calcula la cantidad de obras almacenadas en el arreglo.
int cantidadObras = sizeof(obras) / sizeof(obras[0]);


// ==================================================
// FUNCION: LISTAR AUTORES
// Muestra los datos de todos los autores registrados.
// No recibe parametros ni devuelve valores.
// ==================================================

void listarAutores(void)
{
    int i;

    printf("\n===== LISTADO DE AUTORES =====\n\n");

    // Recorre el arreglo y muestra los datos de cada autor.
    for (i = 0; i < cantidadAutores; i++)
    {
        printf("ID: %d\n", autores[i].idAutor);
        printf("Nombre: %s\n", autores[i].nombre);
        printf("Pais: %s\n", autores[i].pais);
        printf("Especialidad: %s\n\n", autores[i].especialidad);
    }
}


// ==================================================
// FUNCION: LISTAR OBRAS DE UN AUTOR
// Recibe el ID de un autor y muestra las obras que
// estan asociadas a ese identificador.
// No devuelve valores.
// ==================================================

void listarObrasAutor(int idAutor)
{
    int i;
    int encontrado = 0;

    printf("\n===== OBRAS DEL AUTOR =====\n\n");

    // Recorre las obras y compara el ID de cada una
    // con el ID recibido como parametro.
    for (i = 0; i < cantidadObras; i++)
    {
        if (obras[i].idAutor == idAutor)
        {
            printf("Titulo: %s\n", obras[i].titulo);
            printf("Tipo: %s\n\n", obras[i].tipo);

            // Indica que se encontro al menos una obra.
            encontrado = 1;
        }
    }

    // Informa si no existen obras asociadas al ID recibido.
    if (encontrado == 0)
    {
        printf("No se encontraron obras para ese autor.\n");
    }
}
