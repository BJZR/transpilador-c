#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estructura de mapeo ES -> C
typedef struct {
    const char *es;
    const char *c;
} Palabra;

Palabra mapa[] = {
    {"entero", "int"},
    {"principal", "main"},
    {"retornar", "return"},
    {"si", "if"},
    {"sino", "else"},
    {"mientras", "while"},
    {"para", "for"},
    {"hacer", "do"},
    {"vacio", "void"},
    {"caracter", "char"},
    {"flotante", "float"},
    {"doble", "double"},
    {"largo", "long"},
    {"corto", "short"},
    {"estructura", "struct"},
    {"union", "union"},
    {"estatico", "static"},
    {"constante", "const"},
    {"romper", "break"},
    {"continuar", "continue"},
    {"caso", "case"},
    {"por_defecto", "default"},
    {"segun", "switch"},
    {"externo", "extern"},
    {"registro", "register"},
    {"tamanio_de", "sizeof"},
    {"con_signo", "signed"},
    {"sin_signo", "unsigned"},
    {"volatil", "volatile"},
    {"tipo", "typedef"},
    {NULL, NULL}
};

// Revisa si la palabra es reservada
int es_reservada(const char *palabra) {
    for (int i = 0; mapa[i].es != NULL; i++) {
        if (strcmp(palabra, mapa[i].es) == 0) {
            return 1;
        }
    }
    return 0;
}

// Reemplazo de palabra completa (solo si es reservada)
const char* reemplazar(const char* palabra) {
    for (int i = 0; mapa[i].es != NULL; i++) {
        if (strcmp(palabra, mapa[i].es) == 0) {
            return mapa[i].c;
        }
    }
    return palabra; // si no coincide, se devuelve igual
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <entrada.es> <salida.c>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        perror("Error al abrir archivo de entrada");
        return 1;
    }

    FILE *fout = fopen(argv[2], "w");
    if (!fout) {
        perror("Error al abrir archivo de salida");
        fclose(fin);
        return 1;
    }

    char palabra[256];
    int c, i = 0;
    int estado = 0; // 0=normal, 1=//, 2=/* */, 3=string, 4=char
    int linea = 1;
    int error = 0;

    while ((c = fgetc(fin)) != EOF) {
        if (c == '\n') linea++; // contar líneas

        if (estado == 0) { // Normal
            if (c == '/' ) {
                int d = fgetc(fin);
                if (d == '/') {
                    fputs("//", fout);
                    estado = 1; // comentario de línea
                } else if (d == '*') {
                    fputs("/*", fout);
                    estado = 2; // comentario de bloque
                } else {
                    fputc(c, fout);
                    ungetc(d, fin);
                }
            }
            else if (c == '"') {
                fputc(c, fout);
                estado = 3; // string
            }
            else if (c == '\'') {
                fputc(c, fout);
                estado = 4; // char literal
            }
            else if (isalnum(c) || c == '_') {
                palabra[i++] = c;
            } else {
                if (i > 0) {
                    palabra[i] = '\0';

                    if (es_reservada(palabra)) {
                        // Mirar el siguiente caracter real (ignorando espacios)
                        int d;
                        do {
                            d = fgetc(fin);
                        } while (d == ' ' || d == '\t');

                        if (d == '=' || d == '(') {
                            // Si es '(' pero la palabra es una sentencia de control, no es error
                            if (d == '(' &&
                                (strcmp(palabra, "si") == 0 ||
                                strcmp(palabra, "mientras") == 0 ||
                                strcmp(palabra, "para") == 0 ||
                                strcmp(palabra, "segun") == 0)) {
                                // permitido, no marcar error
                                } else {
                                    fprintf(stderr,
                                            "Error [línea %d]: '%s' es una palabra reservada, "
                                            "no puedes usarla como nombre de variable o función.\n",
                                            linea, palabra);
                                    error = 1;
                                }
                        }

                        ungetc(d, fin);
                    }


                    fprintf(fout, "%s", reemplazar(palabra));
                    i = 0;
                }
                fputc(c, fout);
            }
        }
        else if (estado == 1) { // Comentario línea
            fputc(c, fout);
            if (c == '\n') estado = 0;
        }
        else if (estado == 2) { // Comentario bloque
            fputc(c, fout);
            if (c == '*' ) {
                int d = fgetc(fin);
                if (d == '/') {
                    fputc(d, fout);
                    estado = 0;
                } else {
                    ungetc(d, fin);
                }
            }
        }
        else if (estado == 3) { // String
            fputc(c, fout);
            if (c == '\\') { // escape
                int d = fgetc(fin);
                if (d != EOF) fputc(d, fout);
            } else if (c == '"') {
                estado = 0;
            }
        }
        else if (estado == 4) { // Char literal
            fputc(c, fout);
            if (c == '\\') { // escape
                int d = fgetc(fin);
                if (d != EOF) fputc(d, fout);
            } else if (c == '\'') {
                estado = 0;
            }
        }
    }

    if (i > 0) {
        palabra[i] = '\0';
        fprintf(fout, "%s", reemplazar(palabra));
    }

    fclose(fin);
    fclose(fout);

    if (error) {
        printf("Transpilación completada con errores. Revisa los mensajes.\n");
        return 1;
    } else {
        printf("Transpilación completada: %s -> %s\n", argv[1], argv[2]);
        return 0;
    }
}
