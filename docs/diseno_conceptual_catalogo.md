# Biblioteca Arcadia

## Diseño conceptual del módulo Catálogo

**Proyecto:** Sistema de gestión bibliotecaria Biblioteca Arcadia  
**Materia:** Programación I — Tecnicatura Universitaria en Programación  
**Responsable del módulo:** Adrián  
**Etapa:** Diseño conceptual  
**Versión:** 0.1

---

### 1. Introducción

En este documento se presenta el diseño conceptual del módulo Catálogo de Biblioteca Arcadia.
El propósito es representar cómo estará organizado el módulo, cuáles serán sus componentes principales y qué operaciones 
permitirá realizar.
El diseño servirá como referencia durante la posterior implementación en lenguaje C.



### 2. Organización general

El módulo Catálogo estará dividido en dos componentes principales:

- **Autores:** administrará la información de referencia de los autores y sus obras.
- **Libros:** administrará los registros bibliográficos de los libros que forman parte de la biblioteca.

Ambos componentes estarán relacionados, ya que cada libro deberá estar asociado a un autor.
Es importante distinguir entre los autores y sus obras de referencia y los libros que efectivamente forman parte del 
inventario de Biblioteca Arcadia.


### 3. Diagrama conceptual

```text
                  BIBLIOTECA ARCADIA
                          |
                       CATÁLOGO
                          |
               +----------+----------+
               |                     |
            AUTORES                LIBROS
               |                     |
        +------+------+       +------+-------+
        |      |      |       |      |       |
      Cargar  Listar Buscar   Alta Modificar Baja
        |      |      |       |      |       |
        +------+------+       +------+-------+
               |                     |
        Consulta de obras       Búsquedas y filtros
                                     |
                         +-----------+-----------+
                         |     |     |     |     |
                        ISBN Título Autor Género Año
                                     |
                                  Inicial
                                     |
                              ORDENAMIENTOS
                                     |
                                  LISTADOS
```



### 4. Componente de autores

Este componente contendrá información de referencia de los autores, incluyendo:

- Identificador.
- Nombre.
- País.
- Especialidad.

Permitirá realizar una carga inicial, consultar y listar autores, y consultar las obras asociadas a cada uno.


### 5. Componente de libros

Este componente administrará los libros registrados en Biblioteca Arcadia.

Las operaciones previstas son:
- Carga inicial de libros.
- Alta de nuevos libros.
- Modificación de información.
- Baja lógica de libros.

La baja lógica permitirá marcar un libro como inactivo sin eliminar definitivamente su registro.


### 6. Búsquedas, filtros y ordenamientos

El catálogo permitirá localizar libros utilizando distintos criterios:
- ISBN.
- Título.
- Autor.
- Género.
- Año de publicación.
- Inicial del título.

También se contemplan ordenamientos por título, autor y año de publicación, además de listados generales y consultas 
de libros dados de baja.


### 7. Relación con otros módulos

El módulo Catálogo deberá proporcionar información al módulo de préstamos cuando sea necesario consultar la existencia de 
un libro, su estado o los datos relacionados con el stock.
También deberá coordinarse con el módulo de archivos y reportes para establecer cómo se almacenarán y recuperarán los 
registros.
Cada módulo conservará sus propias responsabilidades y se comunicará con los demás mediante funciones previamente acordadas.


### 8. Consideraciones para la implementación

El diseño se implementará utilizando lenguaje C, mediante estructuras, funciones y archivos separados `.c` y `.h`.
Los nombres definitivos de las funciones y las estructuras compartidas se acordarán con los demás integrantes antes de 
realizar la integración.


### 9. Conclusión

Este diseño conceptual establece la organización general del módulo Catálogo y permite visualizar sus principales componentes y funcionalidades.

Servirá como guía para comenzar la implementación, primero desarrollando el componente de autores y posteriormente las operaciones correspondientes a los libros.
