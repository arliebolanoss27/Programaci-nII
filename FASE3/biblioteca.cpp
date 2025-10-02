#include "biblioteca.h"
#include <ctime>

// Constructor
BibliotecaDB::BibliotecaDB() : next_autor_id(1), next_libro_id(1), 
                             next_estudiante_id(1), next_prestamo_id(1) {
    cargarDatos();
}

// ============ CRUD AUTOR ============
void BibliotecaDB::agregarAutor(string nombre, string nacionalidad) {
    Autor autor;
    autor.id = next_autor_id++;
    autor.nombre = nombre;
    autor.nacionalidad = nacionalidad;
    autores.push_back(autor);
    cout << "Autor agregado con ID: " << autor.id << endl;
}

void BibliotecaDB::listarAutores() {
    cout << "\n=== AUTORES ===" << endl;
    for (const auto& autor : autores) {
        cout << "ID: " << autor.id << " - " << autor.nombre 
             << " (" << autor.nacionalidad << ")" << endl;
    }
}

// ============ CRUD LIBRO ============
void BibliotecaDB::agregarLibro(string titulo, string isbn, int ano, int id_autor) {
    Libro libro;
    libro.id = next_libro_id++;
    libro.titulo = titulo;
    libro.isbn = isbn;
    libro.ano = ano;
    libro.id_autor = id_autor;
    libros.push_back(libro);
    cout << "Libro agregado con ID: " << libro.id << endl;
}

void BibliotecaDB::listarLibros() {
    cout << "\n=== LIBROS ===" << endl;
    for (const auto& libro : libros) {
        cout << "ID: " << libro.id << " - " << libro.titulo 
             << " (" << libro.ano << ") - Autor ID: " << libro.id_autor << endl;
    }
}

// ============ CRUD ESTUDIANTE ============
void BibliotecaDB::agregarEstudiante(string nombre, string grado) {
    Estudiante estudiante;
    estudiante.id = next_estudiante_id++;
    estudiante.nombre = nombre;
    estudiante.grado = grado;
    estudiantes.push_back(estudiante);
    cout << "Estudiante agregado con ID: " << estudiante.id << endl;
}

void BibliotecaDB::listarEstudiantes() {
    cout << "\n=== ESTUDIANTES ===" << endl;
    for (const auto& estudiante : estudiantes) {
        cout << "ID: " << estudiante.id << " - " << estudiante.nombre 
             << " (" << estudiante.grado << ")" << endl;
    }
}

// ============ CRUD PRÉSTAMO ============
void BibliotecaDB::agregarPrestamo(int id_libro, int id_estudiante) {
    Prestamo prestamo;
    prestamo.id = next_prestamo_id++;
    prestamo.id_libro = id_libro;
    prestamo.id_estudiante = id_estudiante;
    
    time_t now = time(0);
    prestamo.fecha_prestamo = ctime(&now);
    prestamo.fecha_prestamo.erase(prestamo.fecha_prestamo.length() - 1);
    prestamo.fecha_devolucion = "";
    
    prestamos.push_back(prestamo);
    cout << "Préstamo realizado con ID: " << prestamo.id << endl;
}

void BibliotecaDB::listarPrestamos() {
    cout << "\n=== PRÉSTAMOS ===" << endl;
    for (const auto& prestamo : prestamos) {
        cout << "ID: " << prestamo.id << " - Libro: " << prestamo.id_libro 
             << " - Estudiante: " << prestamo.id_estudiante 
             << " - Fecha: " << prestamo.fecha_prestamo;
        if (!prestamo.fecha_devolucion.empty()) {
            cout << " - Devuelto: " << prestamo.fecha_devolucion;
        }
        cout << endl;
    }
}

void BibliotecaDB::devolverLibro(int id_prestamo) {
    for (auto& prestamo : prestamos) {
        if (prestamo.id == id_prestamo) {
            time_t now = time(0);
            prestamo.fecha_devolucion = ctime(&now);
            prestamo.fecha_devolucion.erase(prestamo.fecha_devolucion.length() - 1);
            cout << "Libro devuelto exitosamente." << endl;
            return;
        }
    }
    cout << "Préstamo no encontrado." << endl;
}

// ============ CONSULTAS BÁSICAS ============
void BibliotecaDB::listarLibrosPrestadosPorEstudiante(int id_estudiante) {
    cout << "\n=== LIBROS PRESTADOS POR ESTUDIANTE " << id_estudiante << " ===" << endl;
    
    for (const auto& prestamo : prestamos) {
        if (prestamo.id_estudiante == id_estudiante && prestamo.fecha_devolucion.empty()) {
            cout << "Libro ID: " << prestamo.id_libro 
                 << " - Préstamo: " << prestamo.fecha_prestamo << endl;
        }
    }
}

void BibliotecaDB::listarAutoresConMasLibros() {
    cout << "\n=== AUTORES CON MÁS LIBROS ===" << endl;
    
    for (const auto& autor : autores) {
        int cantidad = 0;
        for (const auto& libro : libros) {
            if (libro.id_autor == autor.id) {
                cantidad++;
            }
        }
        if (cantidad > 0) {
            cout << autor.nombre << ": " << cantidad << " libros" << endl;
        }
    }
}

// ============ PERSISTENCIA ============
void BibliotecaDB::guardarDatos() {
    // Guardar autores
    ofstream archivo("autores.txt");
    for (const auto& autor : autores) {
        archivo << autor.id << "," << autor.nombre << "," << autor.nacionalidad << endl;
    }
    archivo.close();
    
    // Guardar libros
    archivo.open("libros.txt");
    for (const auto& libro : libros) {
        archivo << libro.id << "," << libro.titulo << "," << libro.isbn 
                << "," << libro.ano << "," << libro.id_autor << endl;
    }
    archivo.close();
    
    // Guardar estudiantes
    archivo.open("estudiantes.txt");
    for (const auto& estudiante : estudiantes) {
        archivo << estudiante.id << "," << estudiante.nombre << "," << estudiante.grado << endl;
    }
    archivo.close();
    
    // Guardar préstamos
    archivo.open("prestamos.txt");
    for (const auto& prestamo : prestamos) {
        archivo << prestamo.id << "," << prestamo.id_libro << "," << prestamo.id_estudiante 
                << "," << prestamo.fecha_prestamo << "," << prestamo.fecha_devolucion << endl;
    }
    archivo.close();
    
    cout << "Datos guardados." << endl;
}

void BibliotecaDB::cargarDatos() {
    // Cargar autores
    ifstream archivo("autores.txt");
    string linea;
    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(',');
        size_t pos2 = linea.find(',', pos1 + 1);
        
        if (pos1 != string::npos && pos2 != string::npos) {
            Autor autor;
            autor.id = stoi(linea.substr(0, pos1));
            autor.nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            autor.nacionalidad = linea.substr(pos2 + 1);
            autores.push_back(autor);
            if (autor.id >= next_autor_id) next_autor_id = autor.id + 1;
        }
    }
    archivo.close();
    
    // Cargar libros
    archivo.open("libros.txt");
    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(',');
        size_t pos2 = linea.find(',', pos1 + 1);
        size_t pos3 = linea.find(',', pos2 + 1);
        size_t pos4 = linea.find(',', pos3 + 1);
        
        if (pos4 != string::npos) {
            Libro libro;
            libro.id = stoi(linea.substr(0, pos1));
            libro.titulo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            libro.isbn = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            libro.ano = stoi(linea.substr(pos3 + 1, pos4 - pos3 - 1));
            libro.id_autor = stoi(linea.substr(pos4 + 1));
            libros.push_back(libro);
            if (libro.id >= next_libro_id) next_libro_id = libro.id + 1;
        }
    }
    archivo.close();
    
    // Cargar estudiantes
    archivo.open("estudiantes.txt");
    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(',');
        size_t pos2 = linea.find(',', pos1 + 1);
        
        if (pos1 != string::npos && pos2 != string::npos) {
            Estudiante estudiante;
            estudiante.id = stoi(linea.substr(0, pos1));
            estudiante.nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            estudiante.grado = linea.substr(pos2 + 1);
            estudiantes.push_back(estudiante);
            if (estudiante.id >= next_estudiante_id) next_estudiante_id = estudiante.id + 1;
        }
    }
    archivo.close();
    
    // Cargar préstamos
    archivo.open("prestamos.txt");
    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(',');
        size_t pos2 = linea.find(',', pos1 + 1);
        size_t pos3 = linea.find(',', pos2 + 1);
        size_t pos4 = linea.find(',', pos3 + 1);
        
        if (pos3 != string::npos) {
            Prestamo prestamo;
            prestamo.id = stoi(linea.substr(0, pos1));
            prestamo.id_libro = stoi(linea.substr(pos1 + 1, pos2 - pos1 - 1));
            prestamo.id_estudiante = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1));
            prestamo.fecha_prestamo = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            if (pos4 != string::npos) {
                prestamo.fecha_devolucion = linea.substr(pos4 + 1);
            }
            prestamos.push_back(prestamo);
            if (prestamo.id >= next_prestamo_id) next_prestamo_id = prestamo.id + 1;
        }
    }
    archivo.close();
}

// ============ MENÚ PRINCIPAL ============
void BibliotecaDB::mostrarMenu() {
    cout << "\n=== SISTEMA DE BIBLIOTECA ===" << endl;
    cout << "1. Agregar Autor" << endl;
    cout << "2. Agregar Libro" << endl;
    cout << "3. Agregar Estudiante" << endl;
    cout << "4. Realizar Préstamo" << endl;
    cout << "5. Devolver Libro" << endl;
    cout << "6. Listar Autores" << endl;
    cout << "7. Listar Libros" << endl;
    cout << "8. Listar Estudiantes" << endl;
    cout << "9. Listar Préstamos" << endl;
    cout << "10. Libros prestados por estudiante" << endl;
    cout << "11. Autores con más libros" << endl;
    cout << "12. Guardar Datos" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opción: ";
}

void BibliotecaDB::ejecutarOpcion(int opcion) {
    string nombre, nacionalidad, titulo, isbn, grado;
    int ano, id_autor, id_libro, id_estudiante, id_prestamo;
    
    switch (opcion) {
        case 1:
            cout << "Nombre del autor: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Nacionalidad: ";
            getline(cin, nacionalidad);
            agregarAutor(nombre, nacionalidad);
            break;
            
        case 2:
            cout << "Título del libro: ";
            cin.ignore();
            getline(cin, titulo);
            cout << "ISBN: ";
            getline(cin, isbn);
            cout << "Año: ";
            cin >> ano;
            cout << "ID del autor: ";
            cin >> id_autor;
            agregarLibro(titulo, isbn, ano, id_autor);
            break;
            
        case 3:
            cout << "Nombre del estudiante: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Grado: ";
            getline(cin, grado);
            agregarEstudiante(nombre, grado);
            break;
            
        case 4:
            cout << "ID del libro: ";
            cin >> id_libro;
            cout << "ID del estudiante: ";
            cin >> id_estudiante;
            agregarPrestamo(id_libro, id_estudiante);
            break;
            
        case 5:
            cout << "ID del préstamo: ";
            cin >> id_prestamo;
            devolverLibro(id_prestamo);
            break;
            
        case 6:
            listarAutores();
            break;
            
        case 7:
            listarLibros();
            break;
            
        case 8:
            listarEstudiantes();
            break;
            
        case 9:
            listarPrestamos();
            break;
            
        case 10:
            cout << "ID del estudiante: ";
            cin >> id_estudiante;
            listarLibrosPrestadosPorEstudiante(id_estudiante);
            break;
            
        case 11:
            listarAutoresConMasLibros();
            break;
            
        case 12:
            guardarDatos();
            break;
            
        case 0:
            cout << "Guardando datos..." << endl;
            guardarDatos();
            cout << "¡Hasta luego!" << endl;
            break;
            
        default:
            cout << "Opción inválida." << endl;
    }
}