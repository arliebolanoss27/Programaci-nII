#include "biblioteca.h"

int main() {
    cout << "Sistema de Gestión de Biblioteca" << endl;
    
    BibliotecaDB biblioteca;
    
    int opcion;
    while (true) {
        biblioteca.mostrarMenu();
        cin >> opcion;
        
        if (opcion == 0) break;
        
        biblioteca.ejecutarOpcion(opcion);
        
        cout << "\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
    }
    
    return 0;
}