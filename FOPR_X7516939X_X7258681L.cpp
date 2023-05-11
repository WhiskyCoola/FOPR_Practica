#include <iostream>
#include <vector>
using namespace std;

struct Carta{
//num&sim = numero y simbolo.
//color: 1 = rojo, 0 = negro.
    string num&sim;
    int color;
};
void Lectura_Dades(){
//LLenar Pila_Cartes y Columnes_Joc//
}

void Estat_Joc(){
//Muestra el estado actual del juego,
//tanto Pila_cartes, Magatzem_Pals y Columnes_Joc
}
void Menu_General(){
//Menu de cin: Introduccion de indicaciones; Aqui Empieza y termina todo.
//While(cin);
}

void Comandes_Moviments(){
//Apartado de movimiento de cartas entre 
//Columnes_Joc, Pila_cartes y Magatzem_Pals
}
void Pila_Cartes(){
//Vector de datos en strings/struct. Baraja de cartas(24).
//Posibles interacciones: Magatzem_Pals, 
}

void Magatzem_Pals(){
//Inicializados en 0.
//Sacar: Solamente 1 carta, para Columnes_Joc.
//Meter: Solamente 1 carta, Desde Columnes_Joc.
}

void Columnes_Joc(){
//Vectores(7). Tamaño estandar = 13. Ampliable con .push_back();
//Si se coge un valor en posición "i" del vector, se coge el resto tambien.
}

int main(){
    Lectura_Dades();
    Menu_General();
}