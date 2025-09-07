#include <stdio.h>

int main() {
    int x = 5;
    int y = 10;         // ❌ ERROR: "si" es palabra reservada
    float numero = 3.14;

    // Ejemplo de condición
    if (x < numero) {
        x = x + 1;
    } else {
        x = x - 1;
    }

    // Ejemplo de bucle
    while (x < 20) {
        x = x + 2;
    }

    // Ejemplo de función
    void imprimir() {
        char c = 'c';
        int siete = 7;   // ❌ ERROR: "para" es palabra reservada
        printf("Valor: %d, Letra: %c\n", x, c);
    }

    imprimir();

    return 0;
}
