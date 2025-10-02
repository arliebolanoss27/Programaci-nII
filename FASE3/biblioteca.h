#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// Estructuras para representar las entidades
struct Autor {
    int id;
    string nombre;
    string nacionalidad;
};

struct Libro {
    int id;
    string titulo;
    string isbn;
    int ano;
    int id_autor;
};

struct Estudiante {
    int id;
    string nombre;
    string grado;
};

struct Prestamo {
    int id;
    int id_libro;
    int id_estudiante;
    string fecha_prestamo;
    string fecha_devolucion;
};

// Clase principal para manejar la base de datos
class BibliotecaDB {
private:
    vector<Autor> autores;
    vector<Libro> libros;
    vector<Estudiante> estudiantes;
    vector<Prestamo> prestamos;
    
    int next_autor_id;
    int next_libro_id;
    int next_estudiante_id;
    int next_prestamo_id;
    
public:
    BibliotecaDB();
    
    // Métodos CRUD para Autor
    void agregarAutor(string nombre, string nacionalidad);
    void listarAutores();
    
    // Métodos CRUD para Libro
    void agregarLibro(string titulo, string isbn, int ano, int id_autor);
    void listarLibros();
    
    // Métodos CRUD para Estudiante
    void agregarEstudiante(string nombre, string grado);
    void listarEstudiantes();
    
    // Métodos CRUD para Préstamo
    void agregarPrestamo(int id_libro, int id_estudiante);
    void listarPrestamos();
    void devolverLibro(int id_prestamo);
    
    // Consultas básicas
    void listarLibrosPrestadosPorEstudiante(int id_estudiante);
    void listarAutoresConMasLibros();
    
    // Persistencia
    void guardarDatos();
    void cargarDatos();
    
    // Menú principal
    void mostrarMenu();
    void ejecutarOpcion(int opcion);
};

#endif
