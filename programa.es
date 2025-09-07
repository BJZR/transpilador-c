#include <stdio.h>

entero principal() {
    entero x = 5;
    entero y = 10;         // ❌ ERROR: "si" es palabra reservada
    flotante numero = 3.14;

    // Ejemplo de condición
    si (x < numero) {
        x = x + 1;
    } sino {
        x = x - 1;
    }

    // Ejemplo de bucle
    mientras (x < 20) {
        x = x + 2;
    }

    // Ejemplo de función
    vacio imprimir() {
        caracter c = 'c';
        entero siete = 7;   // ❌ ERROR: "para" es palabra reservada
        printf("Valor: %d, Letra: %c\n", x, c);
    }

    imprimir();

    retornar 0;
}
