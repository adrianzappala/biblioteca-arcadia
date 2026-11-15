# Avances – Módulo de Catálogo
**Proyecto: Biblioteca Arcadia**

Durante la jornada se continuó con el desarrollo del módulo de Catálogo, trabajando en la organización de autores, obras y libros, así como en la incorporación de persistencia mediante archivos binarios.

### 1. Organización de autores y obras
- Se definieron las estructuras `Autor` y `Obra`.
- Se incorporó un listado inicial de 12 autores.
- Se cargaron 112 obras asociadas a dichos autores.
- Se implementaron funciones para listar autores y consultar las obras correspondientes a cada uno.

### 2. Estructura de libros
Se definió la estructura `Libro`, con los siguientes atributos:
- ISBN.
- Título.
- ID del autor.
- Año de publicación.
- Stock total.
- Stock disponible.

### 3. Gestión del catálogo
Se implementaron las siguientes funcionalidades:
- Alta de libros.
- Modificación de libros existentes.
- Listado general de libros.
- Búsqueda por ISBN.
- Listado de libros disponibles.
- Control de ISBN duplicados al registrar nuevos libros.
- Validación básica del stock.

### 4. Persistencia de datos
Se incorporó el archivo binario `libros.dat` para almacenar los registros del catálogo.

Se implementaron operaciones de lectura y escritura mediante `fread()`, `fwrite()` y las funciones de apertura y cierre de archivos.

### 5. Carga inicial del catálogo
Se desarrolló una función para incorporar automáticamente las obras definidas en el módulo de autores al catálogo de libros.

Como resultado, se logró cargar correctamente un total de **112 obras**, asignándoles códigos internos consecutivos, un stock inicial de 3 ejemplares y su correspondiente ID de autor.

### 6. Integración y pruebas
Se integraron los módulos `autores.c` y `libros.c` mediante sus respectivos archivos de cabecera.

También se desarrolló un menú principal en `main.c` para acceder a las funcionalidades implementadas.

Se realizaron pruebas de compilación y ejecución, verificando la carga inicial, el almacenamiento y el listado de los 112 registros.

### Próximas tareas
- Incorporar búsquedas y filtros por título, autor, género y año.
- Implementar opciones de ordenamiento del catálogo.
- Mejorar la visualización de los datos de los autores.
- Continuar con las pruebas y la integración con los demás módulos del sistema.

**Estado actual:** módulo de Catálogo en desarrollo.
