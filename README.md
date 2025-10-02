# Sistema de Biblioteca - Fase 3 Arlette Catalan

## Descripción
Sistema de gestión de biblioteca en C++ con operaciones CRUD para autores, libros, estudiantes y préstamos.

## Archivos
- `biblioteca.h` - Estructuras y declaraciones
- `biblioteca.cpp` - Implementación de la clase
- `main.cpp` - Función principal
- `biblioteca.exe` - Ejecutable compilado

## Compilación
```bash
g++ -std=c++11 -Wall -Wextra -O2 -o biblioteca main.cpp biblioteca.cpp
```

## Uso
```bash
./biblioteca
```

## Funcionalidades
- Agregar autores, libros, estudiantes
- Realizar y devolver préstamos
- Listar todas las entidades
- Consultas: libros prestados por estudiante, autores con más libros
- Persistencia en archivos CSV

## Entidades
- **Autor**: ID, Nombre, Nacionalidad
- **Libro**: ID, Título, ISBN, Año, ID_Autor
- **Estudiante**: ID, Nombre, Grado  
- **Préstamo**: ID, ID_Libro, ID_Estudiante, Fechas
