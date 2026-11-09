# Biblioteca Arcadia
## Planificación y diseño del módulo Catálogo

**Proyecto:** Sistema de gestión bibliotecaria Biblioteca Arcadia  
**Materia:** Programación I — Tecnicatura Universitaria en Programación  
**Responsable del módulo:** Adrián  
**Etapa:** Diseño y planificación inicial  
**Versión del documento:** 0.1


### 1. Introducción
Dentro del proyecto Biblioteca Arcadia, mi responsabilidad es desarrollar el módulo Catálogo, encargado de administrar la 
información bibliográfica de los libros y los datos correspondientes a sus autores.
El objetivo de esta etapa es establecer una planificación del trabajo antes de comenzar con la implementación en lenguaje C. 
Se busca definir las funcionalidades que tendrá el módulo, los datos que necesitará administrar, su organización y los puntos
que deberán coordinarse con los demás integrantes del equipo.
El desarrollo se realizará de manera progresiva. Cada avance será documentado y registrado en GitHub, desde el diseño inicial
hasta la implementación, las pruebas y la integración con el sistema general.


### 2. Objetivo del módulo
El módulo Catálogo tendrá como objetivo administrar los libros y autores de Biblioteca Arcadia, permitiendo registrar nuevos 
libros, modificar información existente, gestionar bajas, realizar búsquedas, aplicar filtros, ordenar resultados y generar 
listados. También contemplará una carga inicial de autores y sus obras, que servirá como información de referencia para el 
catálogo.


### 3. Alcance y funcionalidades
Las funcionalidades previstas para el módulo son:

**Administración de autores**
- Carga inicial de autores.
- Consulta y listado de autores.
- Consulta de obras asociadas a cada autor.
- Búsqueda de autores.

**Administración de libros**
- Carga inicial de libros.
- Alta de nuevos libros.
- Modificación de información.
- Baja lógica de libros, conservando sus registros.

**Búsquedas y filtros**
- Búsqueda por ISBN.
- Búsqueda por título.
- Búsqueda por autor.
- Búsqueda por género.
- Búsqueda por año de publicación.
- Búsqueda según la inicial del título.

**Ordenamientos y listados**
- Ordenamiento por título.
- Ordenamiento por autor.
- Ordenamiento por año de publicación.
- Listado general del catálogo.
- Consulta de libros dados de baja.



### 4. Diseño conceptual
El módulo estará organizado en dos componentes principales:

**Autores:** contendrá la información de referencia de los autores, como identificador, nombre, país y especialidad. 
También permitirá consultar las obras asociadas.

**Libros:** contendrá los registros bibliográficos de los libros de la biblioteca, incluyendo su ISBN, título, autor, 
año de publicación, stock y demás atributos que se acuerden para el sistema.
Ambos componentes estarán relacionados, ya que cada libro deberá estar asociado a un autor.
El módulo también ofrecerá operaciones de consulta para que otros componentes del sistema puedan acceder a la información 
de los libros cuando sea necesario.



### 5. Estructuras de datos previstas
Para los autores se contempla inicialmente una estructura con los siguientes campos:
- Identificador del autor.
- Nombre.
- País.
- Especialidad.

Para los libros se parte de la estructura propuesta en la consigna, que incluye:
- ISBN.
- Título.
- Autor.
- Año de publicación.
- Stock total.
- Stock disponible.

Se analizará la incorporación de campos adicionales para representar el género literario y el estado del registro, 
necesario para implementar las bajas lógicas.
Las modificaciones a las estructuras compartidas deberán acordarse con el equipo antes de su implementación.



### 6. Baja lógica de libros
Se propone implementar un mecanismo de baja lógica. En lugar de eliminar físicamente un libro, se modificará su estado 
para indicar que ya no se encuentra habilitado en el catálogo.
Esta alternativa permite conservar la información del registro y distinguir entre libros activos e inactivos.
También deberá definirse, junto con el responsable del módulo de préstamos, cómo proceder cuando se solicite la baja 
de un libro que tenga ejemplares prestados.




### 7. Organización prevista
Se propone organizar el módulo mediante archivos separados:

- `autores.h`: declaraciones y definiciones correspondientes al módulo de autores, según la distribución final de estructuras.
- `autores.c`: implementación de las operaciones de autores.
- `catalogo.h`: declaraciones de las funciones del catálogo.
- `catalogo.c`: implementación de las operaciones sobre libros.
- `estructuras.h`: estructuras compartidas por los distintos módulos del proyecto.

La organización definitiva dependerá de los acuerdos del equipo y de la estructura general del proyecto.



### 8. Integración con otros módulos
El catálogo deberá poder proporcionar información sobre los libros al módulo de préstamos, por ejemplo, para verificar la 
existencia de un ISBN, consultar el estado de un libro y acceder a los datos de stock.
También deberá coordinarse con el módulo responsable de archivos y reportes para definir cómo se almacenarán y recuperarán 
los registros.
La intención es evitar dependencias innecesarias y permitir que cada módulo trabaje mediante funciones e interfaces 
previamente acordadas.



### 9. Metodología de trabajo y control de versiones
El desarrollo se realizará por etapas, procurando completar y probar cada funcionalidad antes de avanzar a la siguiente.
Se utilizará Git y GitHub para registrar los avances del módulo. Se realizarán commits que describan los cambios efectuados, 
tanto en la documentación como en el código fuente.
De esta manera quedará registrado el proceso de desarrollo, incluyendo la planificación, el diseño de estructuras, la 
implementación de funciones, las pruebas y las correcciones realizadas.



### 10. Etapas previstas
1. Diseño y planificación del módulo.
2. Coordinación de estructuras y funciones con el equipo.
3. Desarrollo del módulo de autores.
4. Desarrollo de las operaciones básicas de libros.
5. Implementación de bajas lógicas.
6. Desarrollo de búsquedas y filtros.
7. Implementación de ordenamientos y listados.
8. Coordinación del almacenamiento de datos.
9. Pruebas e integración con el sistema general.
10. Documentación final del desarrollo.


### 11. Decisiones pendientes
Antes de comenzar con la implementación definitiva será necesario acordar:

- La incorporación del género literario a la estructura de libros.
- La representación del estado activo o inactivo.
- La forma de relacionar los libros con los autores.
- El tratamiento de libros que tengan préstamos activos al solicitar su baja.
- Las funciones que necesitarán los demás módulos para consultar información del catálogo.
- La forma de almacenamiento y recuperación de los registros.



### 12. Conclusión de la etapa

Esta primera planificación establece el alcance del módulo Catálogo y organiza las funcionalidades que se desarrollarán durante el proyecto.

A partir de este diseño se avanzará hacia la definición técnica de las estructuras, la interfaz de funciones y la implementación progresiva de cada operación, manteniendo un registro de los cambios y coordinando las decisiones que afecten al resto del equipo.
